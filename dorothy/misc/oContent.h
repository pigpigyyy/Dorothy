/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_MISC_OCONTENT_H__
#define __DOROTHY_MISC_OCONTENT_H__

NS_DOROTHY_BEGIN

/** @brief Manager of game resource. Game resource can be loaded from a certain directory or a .game file.
 .game file is a zip pack with game stuff. Encryption for .game file is provided later.
*/
class oContent
{
public:
	~oContent();
	/** Set the .game file to use. */
	bool setGameFile(const string& filename);
	/** Set password for encrypted .game file. */
	void setPassword(const string& password);
	const string& getPassword() const;
	/** Set whether game resource should be load from .game file.
	 This method will affect behaviors of the following load function.
	*/
	void setUsingGameFile(bool use);
	bool isUsingGameFile() const;
	/** Load a texture from either a certain folder or a .game pack with only filename. */
	CCTexture2D* loadTexture(const char* filename);
	/** Get file data content and size from either a certain folder or a .game pack with only filename. */
	oOwnArray<char> loadFile(const char* filename, unsigned long& size);
	/** Extract file from .game file to certain place.
	 Extracting files with same name but different extensions causes errors.
	*/
	void extractGameFile(const char* filename, const char* targetFullName);
	void extractGameFileAsync(const char* filename, const char* targetFullName, const function<void(const char* filename)>& callback);
	
	void copyFile(const char* src, const char* dst);
	void copyFileAsync(const char* src, const char* dst, const function<void()>& callback);
	
	/** Get the full path name of the file if it was extracted. */
	string getExtractedFullName(const char* filename);
	bool isFileExist(const char* filename);
	bool removeFile(const char* filename);
	void saveToFile(const string& filename, const string& content);
	vector<string> getDirEntries(const char* path, bool isFolder);
	bool mkdir(const char* path);
    bool isdir(const char* path);

    /* from CCFileUtils */
	PROPERTY_READONLY(string, WritablePath);
	PROPERTY_BOOL_NAME(PopupNotify);

	string getFullPath(const char *pszFileName);
	const char* getRelativeFullPath(const char *pszFilename, const char *pszRelativeFile);
	void loadFileLookupInfo(const char* filename);

	void addSearchPath(const char* path);
	void removeSearchPath(const char* path);
	void setSearchPaths(const vector<string>& searchPaths);
	void addSearchResolutionsOrder(const char* order);
	void setSearchResolutionsOrder(const vector<string>& searchPaths);
	void purgeCachedEntries();

	void loadFileAsync(const char* filename, const function<void(oOwnArray<char>,unsigned long)>& callback);

	char* loadFileUnsafe(const char* filename, unsigned long& size);
	void loadFileAsyncUnsafe(const char* filename, const function<void(char*,unsigned long)>& callback);
	/** Singleton method. */
	SHARED_FUNC(oContent);
protected:
	oContent();
	string _password;
	string _gameFileName;
	string _writablePath;
private:
	bool _isUsingGameFile;
};

#define oSharedContent (*oContent::shared())

NS_DOROTHY_END

#endif // __DOROTHY_MISC_OCONTENT_H__