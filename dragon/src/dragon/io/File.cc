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

#include <dragon/io/File.h>
#include <dragon/util/ArrayList.h>

Import dragon::lang;
Import dragon::io;
Import dragon::util;

const dg_char File::separatorChar = getNativeSeparatorChar();
const dg_char File::pathSeparatorChar = getNativePathSeparator();
const String File::separator = getNativeSeparator();

String File::getNativeSeparator() {
	dg_char sep[] = {getNativeSeparatorChar(), L'\0'};
    return String(sep);
}

File::File() {
	this->path = new String("");
}

File::File(const String& pathname){
	this->path = new String(pathname);
}

File::File(const File& other){
	this->path = new String(other.path);
}

File::File(const File* parent, const String& name) {
	ASSERT(parent != null);

	String* tmp01 = parent->getPath();

	String* tmp02 = tmp01->concat(separator);
	SafeDelete(tmp01);

	this->path = tmp02->concat(name);
	SafeDelete(tmp02);
}

File::File(const String& parent, const String& name) {
	String* tmp01 = parent.concat(separator);
	this->path = tmp01->concat(name);
	SafeDelete(tmp01);
}

File::~File(){
	SafeDelete(this->path);
}

bool FileMkdirInternal(const String* path);

bool File::mkdir() {
    return FileMkdirInternal(this->path);
}

bool File::mkdirs() {
    int index = -1;

	bool isBackslash = false;

	index = this->path->indexOf(L'/', index);

	if(index >= 0) {
		isBackslash = true;
	}

	index = 0;

	String* sep = new String(L"\\");

    while(true) {
		if(isBackslash) {
			index = this->path->indexOf(L'/', index);
		} else {
			index = this->path->indexOf(sep, index);
		}

		if(index > 0) {
			String* subDir = this->path->substring(0, index);

			if (!FileMkdirInternal(subDir)) {
				SafeDelete(subDir);
				return false;
			} else {
				SafeDelete(subDir);
			}
		} else if (index == 0) {
			;
		} else {
			if (!FileMkdirInternal(this->path)) {
				return false;
			}

			break;
		}

		index++;
    }

    SafeDelete(sep);

	return true;
}

bool File::isFile() {
	if(exists() && !isDirectory()) {
		return true;
	}

	return false;
}

bool File::createNewFile() {
    if (exists())
        return true;

    /*
    const File parentDir (getParentDirectory());

    if (parentDir == *this)
        return Result::fail ("Cannot create parent directory");

    Result r (parentDir.createDirectory());

    if (r.wasOk())
    {
        FileOutputStream fo (*this, 8);
        r = fo.getStatus();
    }

    return r;
    */
   
   return false;
}

String* File::getName() const {
	dg_int index = path->lastIndexOf(File::separatorChar);
	return path->substring(index + 1);
}

String* File::getPath() const {
	return new String(this->path);
}

String* File::getParent() const {
	dg_int index = path->lastIndexOf(separatorChar);
	return path->substring(0, index);
}

File* File::getParentFile() const {
	return new File(this->getParent());
}

bool File::isAbsolute() const {
    return path->startsWith(separator)
            || (path->length() > 0 && path->charAt(1) == ':')
            || path->startsWith("~");
}

File* File::getAbsoluteFile() const {
	return new File(this->getAbsolutePath());
}

// --------------------travle files----------------------------
// native const Array<String> File::list() const;

const Array<String*> File::list(const FilenameFilter* filter) const {
	Array<String*> names = list();

	if ((names.length() == 0) || (filter == null)) {
	    return names;
	}

	ArrayList<String>* v = new ArrayList<String>();

	for (int i = 0 ; i < names.length() ; i++) {
	    if (filter->accept(this, names[i])) {
			v->add(new String(names[i]));
	    } 
	    
	    SafeDelete(names[i]);
	}

	Array<String*> result = v->toArray();
	
	SafeDelete(v);
	names.release();

	return result;
}

const Array<File*> File::listFiles() const {
	Array<String*> ss = list();

	if (ss.length() == 0) 
		return Array<File*>();

	int n = ss.length();

	Array<File*> fs(n);

	for (int i = 0; i < n; i++) {
	    fs[i] = new File(this, ss[i]);
	    SafeDelete(ss[i]);
	}

	ss.release();

	return fs;
}

const Array<File*> File::listFiles(const FileFilter* filter) const {
	Array<String*> ss = list();

	if (ss.length() == 0) 
		return Array<File*>();

	int n = ss.length();

	ArrayList<File>* v = new ArrayList<File>();

	for (int i = 0 ; i < n; i++) {
		File* file = new File(this, ss[i]);

	    if ((filter == null) || filter->accept(file)) {
			v->add(new File(this, ss[i]));
	    } 
	    
	    SafeDelete(ss[i]);
	    SafeDelete(file);
	}

	Array<File*> result = v->toArray();
	
	SafeDelete(v);
	ss.release();

	return result;
}

const Array<File*> File::listFiles(const FilenameFilter* filter) const {
	Array<String*> ss = list();

	if (ss.length() == 0) 
		return Array<File*>();

	int n = ss.length();

	ArrayList<File>* v = new ArrayList<File>();

	for (int i = 0 ; i < n; i++) {
	    if ((filter == null) || filter->accept(this, ss[i])) {
			v->add(new File(this, ss[i]));
	    } 

	    SafeDelete(ss[i]);
	}

	Array<File*> result = v->toArray();

	SafeDelete(v);
	ss.release();

	return result;
}
