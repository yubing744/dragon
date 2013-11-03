/*
* Copyright 2013 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef File_IO_LANG_H 
#define File_IO_LANG_H

#include <dragon/config.h>

#include <dragon/lang/Object.h>
#include <dragon/lang/String.h>

#include <dragon/io/FileFilter.h>
#include <dragon/io/FilenameFilter.h>

BeginPackage2(dragon, io)

Import dragon::io;
Import dragon::lang;

class _DragonExport File extends(Object)
{
public:
	static const dg_char separatorChar;
	static const dg_char pathSeparatorChar;
	static const String separator;

protected:
	static dg_char getNativePathSeparator();
	static dg_char getNativeSeparatorChar();
	static String getNativeSeparator();

public:
	File();
	File(const String& pathname);
	File(const File* parent, const String& name);
	File(const String& parent, const String& name);
	File(const File& other);
	~File();

public:
	File& operator=(const File& other);

public:
	/**
	 * Tests whether the application can execute the file denoted by this abstract pathname.
	 * 
	 * @return [description]
	 */
	virtual bool canExecute();

	/**
	 * Tests whether the application can read the file denoted by this abstract pathname.
	 * 
	 * @return [description]
	 */
	virtual bool canRead();

	/**
	 * Tests whether the application can modify the file denoted by this abstract pathname.
	 * 
	 * @return [description]
	 */
	virtual bool canWrite();

	/**
	 * Tests whether the file named by this abstract pathname is a hidden file.
	 * 
	 * @return [description]
	 */
	virtual bool isHidden();

	/**
	 * Creates the directory named by this abstract pathname.
	 * 
	 * @return [description]
	 */
	virtual bool mkdir();

	/**
	 * Creates the directory named by this abstract pathname, including any necessary but nonexistent parent directories.
	 * 
	 * @return [description]
	 */
	virtual bool mkdirs();

	/**
	 * Tests whether the file or directory denoted by this abstract pathname exists.
	 * 
	 * @return [description]
	 */
	virtual bool exists();

	/**
	 * Tests whether the file denoted by this abstract pathname is a directory.
	 * 
	 * @return [description]
	 */
	virtual bool isDirectory();

	/**
	 * Tests whether the file denoted by this abstract pathname is a normal file.
	 * 
	 * @return [description]
	 */
	virtual bool isFile();

	/**
	 * Deletes the file or directory denoted by this abstract pathname.
	 * 
	 * @return [description]
	 */
	virtual bool del();

	/**
	 * Returns the length of the file denoted by this abstract pathname. The return value is unspecified if this pathname denotes a directory. 
	 * 
	 * @return [description]
	 */
	virtual dg_long length();

	/*
	virtual void deleteOnExit();
	*/

	/**
	 * Atomically creates a new, empty file named by this abstract pathname if and only if a file with this name does not yet exist. The check for the existence of the file and the creation of the file if it does not exist are a single operation that is atomic with respect to all other filesystem activities that might affect the file. 
	 * 
	 * @return [description]
	 */
	virtual bool createNewFile();

	/**
	 * Renames the file denoted by this abstract pathname. 
	 * 
	 * @param  dest [description]
	 * @return      [description]
	 */
	virtual bool renameTo(const File* dest) const;

	/**
	 * Returns an array of strings naming the files and directories in the directory denoted by this abstract pathname.
	 */
	virtual const Array<String*> list() const;
	virtual const Array<String*> list(const FilenameFilter* filter) const;

	virtual const Array<File*> listFiles() const;
	virtual const Array<File*> listFiles(const FileFilter* filter) const;
	virtual const Array<File*> listFiles(const FilenameFilter* filter) const;

	/**
	 * Returns the name of the file or directory denoted by this abstract pathname. This is just the last name in the pathname's name sequence. If the pathname's name sequence is empty, then the empty string is returned. 
	 * 
	 * @return [description]
	 */
	virtual String* getName() const;

	/**
	 * Converts this abstract pathname into a pathname string.
	 * 
	 * @return [description]
	 */
	virtual String* getPath() const;

	/** 
	 * Returns the pathname string of this abstract pathname's parent, or
     * <code>null</code> if this pathname does not name a parent directory.
     */
	virtual String* getParent() const;

	/**
	 * Returns the abstract pathname of this abstract pathname's parent, or null if this pathname does not name a parent directory.
	 * 
	 * @return [description]
	 */
	virtual File* getParentFile() const;

	/**
	 *  Tests whether this abstract pathname is absolute.
	 *  
	 * @return [description]
	 */
	virtual bool isAbsolute() const;

	/**
	 * Returns the absolute pathname string of this abstract pathname.
	 * 
	 * @return [description]
	 */
	virtual String* getAbsolutePath() const;

	/**
	 * Returns the absolute form of this abstract pathname.
	 * 
	 * @return [description]
	 */
	virtual File* getAbsoluteFile() const;

	/*
	virtual String getCanonicalPath() throw(IOException);
	*/

private:
	String* path;
};

EndPackage2// (dragon, io)

#endif// File_IO_LANG_H