/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_MISC_OMEMORYPOOL_H__
#define __DOROTHY_MISC_OMEMORYPOOL_H__

#include "Dorothy/const/oDefine.h"
#include <utility>
#include <new>

NS_DOROTHY_BEGIN

template<class Item, int CHUNK_CAPACITY = 4096, int WARNING_SIZE = 1024>// 4KB 1024KB
class oMemoryPool
{
#define ITEM_SIZE sizeof(Item)
public:
	oMemoryPool() :
		_chunk(new Chunk()),
		_freeList(nullptr)
	{ }
	~oMemoryPool()
	{
		oMemoryPool::deleteChunk(_chunk);
	}
	void* alloc()
	{
		if (_freeList)
		{
			FreeList* head = _freeList;
			_freeList = _freeList->next;
			return (void*)head;
		}
		else
		{
			if (_chunk->size + ITEM_SIZE > CHUNK_CAPACITY)
			{
				_chunk = new Chunk(_chunk);
				int consumption = oMemoryPool::capacity();
				if (consumption >= WARNING_SIZE * 1024)
				{
					CCLOG("[WARNING] oMemoryPool consumes %d KB memory larger than %d KB for type %s", consumption / 1024, WARNING_SIZE, typeid(Item).name());
				}
			}
			char* addr = _chunk->buffer + _chunk->size;
			_chunk->size += ITEM_SIZE;
			return (void*)addr;
		}
	}
	void free(void* addr)
	{
		FreeList* freeItem = (FreeList*)addr;
		freeItem->next = _freeList;
		_freeList = freeItem;
	}
	template<class... Args>
	Item* newItem(Args&&... args)
	{
		Item* mem = (Item*)oMemoryPool<Item, CHUNK_CAPACITY>::alloc();
		return new (mem)Item(std::forward<Args>(args)...);
	}
	void deleteItem(Item* item)
	{
		item->~Item();
		oMemoryPool<Item, CHUNK_CAPACITY>::free((void*)item);
	}
	int capacity()
	{
		int chunkCount = 0;
		for (Chunk* chunk = _chunk; chunk; chunk = chunk->next)
		{
			++chunkCount;
		}
		return chunkCount * CHUNK_CAPACITY;
	}
	void shrink()
	{
		Chunk* prevChunk = nullptr;
		FreeList* sortedChunkList = nullptr;
		FreeList* sortedChunkListTail = nullptr;
		FreeList* prev = nullptr;
		/* root chunk to be reserved */
		for (Chunk* chunk = _chunk->next; chunk;)
		{
			size_t begin = (size_t)chunk->buffer;
			size_t end = begin + CHUNK_CAPACITY;
			int count = 0;
			FreeList* chunkList = nullptr;
			FreeList* chunkListTail = nullptr;
			prev = nullptr;
			for (FreeList* list = _freeList; list;)
			{
				size_t loc = (size_t)list;
				if (begin <= loc && loc < end)
				{
					++count;
					FreeList* temp = list;
					if (prev) prev->next = list->next;
					else _freeList = list->next;
					list = list->next;
					temp->next = chunkList;
					chunkList = temp;
					if (!chunkList) chunkListTail = chunkList;
				}
				else
				{
					prev = list;
					list = list->next;
				}
			}
			if (count == (size_t)(CHUNK_CAPACITY / ITEM_SIZE))
			{
				Chunk* temp = chunk;
				if (prevChunk) prevChunk->next = chunk->next;
				else _chunk->next = chunk->next;
				chunk = chunk->next;
				delete temp;
			}
			else
			{
				if (sortedChunkListTail)
				{
					sortedChunkListTail->next = chunkList;
				}
				else sortedChunkList = chunkList;
				sortedChunkListTail = chunkListTail;
				prevChunk = chunk;
				chunk = chunk->next;
			}
		}
		if (prev) prev->next = sortedChunkList;
		else _freeList = sortedChunkList;
	}
private:
	struct FreeList
	{
		FreeList* next;
	};
	struct Chunk
	{
		Chunk(Chunk* next = nullptr) :
			buffer(new char[CHUNK_CAPACITY]),
			size(0),
			next(next)
		{ }
		~Chunk() { delete[] buffer; }
		int size;
		char* buffer;
		Chunk* next;
	};
	FreeList* _freeList;
	Chunk* _chunk;
	void deleteChunk(Chunk* chunk)
	{
		if (chunk)
		{
			oMemoryPool::deleteChunk(chunk->next);
			delete chunk;
		}
	}
};

#define USE_MEMORY_POOL(type) \
public:\
	inline void* operator new(size_t size){ return _memory.alloc(); }\
	inline void operator delete(void* ptr, size_t size) { _memory.free(ptr); }\
	static int poolCollect()\
	{\
		int oldSize = _memory.capacity();\
		_memory.shrink();\
		int newSize = _memory.capacity();\
		return oldSize - newSize;\
	}\
	static int poolSize()\
	{\
		return _memory.capacity();\
	}\
private:\
	static oMemoryPool<type> _memory;

#define MEMORY_POOL(type) \
oMemoryPool<type> type::_memory;

NS_DOROTHY_END

#endif // __DOROTHY_MISC_OMEMORYPOOL_H__