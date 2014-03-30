#ifndef __DOROTHY_MISC_OXMLITEMCACHE_H__
#define __DOROTHY_MISC_OXMLITEMCACHE_H__

#include "Dorothy/const/oDefine.h"
#include "Dorothy/misc/oContent.h"

NS_DOROTHY_BEGIN

/** @brief Useful for reading xml files and cache them in memory.
 T is the class to store every parsed xml file.
*/
template<class T = CCObject>
class oXmlItemCache: public CCSAXDelegator
{
	typedef typename hash_strmap<oRef<T>> dict;
	typedef typename dict::iterator dict_iter;
public:
	/** Load a new xml file or get its data for cache. */
	T* load( const char* filename )
	{
		dict_iter it = _dict.find(filename);
		if (it != _dict.end())
		{
			return it->second;
		}
		else
		{
			this->beforeParse(filename);
			unsigned long size;
			auto data = oSharedContent.loadFile(filename, size);
			_parser.parse(data, size);
			this->afterParse(filename);
			_dict[filename] = _item;
			T* item = _item;
			_item = nullptr;
			return item;
		}
	}
	T* update(const char* name, const char* content)
	{
		this->beforeParse(name);
		_parser.parse(content, 0);
		this->afterParse(name);
		_dict[name] = _item;
		T* item = _item;
		_item = nullptr;
		return item;
	}
	T* update(const char* name, T* item)
	{
		_dict[name] = item;
		return item;
	}
	/** Purge the cached file. */
	bool unload( const char* filename )
	{
		dict_iter it = _dict.find(filename);
		if (it != _dict.end())
		{
			_dict.erase(it);
			return true;
		}
		return false;
	}
	/** Purge all cached files. */
	bool unload()
	{
		if (_dict.empty())
		{
			return false;
		}
		else
		{
			_dict.clear();
			return true;
		}
	}
protected:
	oXmlItemCache():_item(nullptr)
	{
		_parser.setDelegator(this);
	}
	dict _dict;
	oRef<T> _item;//Use reference in case that do the loading in another thread
private:
	CCSAXParser _parser;
	/** Implement it to get prepare for specific xml parse. */
	virtual void beforeParse( const char* filename ) = 0;
	/** Implement it to do something after xml is parsed. */
	virtual void afterParse( const char* filename ) = 0;
	/** Implement it to parse xml. */
	virtual void textHandler( void *ctx, const char *s, int len ) = 0;
	/** Implement it to parse xml. */
	virtual void startElement( void *ctx, const char *name, const char **atts ) = 0;
	/** Implement it to parse xml. */
	virtual void endElement( void *ctx, const char *name ) = 0;
};

NS_DOROTHY_END

#endif // __DOROTHY_MISC_OXMLITEMCACHE_H__