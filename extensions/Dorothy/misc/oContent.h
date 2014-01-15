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
	 Returning the new file`s full pathname.
	 Extracting files with same name but different extensions causes errors.
	*/
	string extractGameFile(const char* filename);
	/** Get the full path name of the file if it was extracted. */
	string getExtractedFullName(const char* filename);
	
	bool removeExtractedFile(const char* filename);
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