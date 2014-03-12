#ifndef __DOROTHY_MISC_OMEMORYPOOL_H__
#define __DOROTHY_MISC_OMEMORYPOOL_H__

#include "Dorothy/const/oDefine.h"
#include <utility>
#include <new>

NS_DOROTHY_BEGIN

template<class Item, int CHUNK_CAPACITY = 4096>
class oMemoryPool
{
#define ITEM_SIZE sizeof(Item)
public:
	oMemoryPool():
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
		return new (mem) Item(std::forward<Args>(args)...);
	}
	void deleteItem(Item* item)
	{
		item->~Item();
		oMemoryPool<Item, CHUNK_CAPACITY>::free((void*)item);
	}
private:
	struct FreeList
	{
		FreeList* next;
	};
	struct Chunk
	{
		Chunk(Chunk* next = nullptr):
		buffer(new char[CHUNK_CAPACITY - CHUNK_CAPACITY % ITEM_SIZE]),
		size(0),
		next(next)
		{ }
		~Chunk() { delete [] buffer; }
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

NS_DOROTHY_END

#endif // __DOROTHY_MISC_OMEMORYPOOL_H__