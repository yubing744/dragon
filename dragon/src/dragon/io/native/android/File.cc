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

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <linux/stat.h>

#define S_ISTXT     S_ISVTX     /* sticky bit: not supported */
#define S_IREAD     S_IRUSR     /* backward compatability */
#define S_IWRITE    S_IWUSR     /* backward compatability */
#define S_IEXEC     S_IXUSR     /* backward compatability */

#include <dragon/io/File.h>
#include <dragon/util/ArrayList.h>
#include <dragon/util/logging/Logger.h>

Import dragon::lang;
Import dragon::io;
Import dragon::util;
Import dragon::util::logging;

static Logger* logger = Logger::getLogger("dragon::io::File#android", INFO);

dg_char File::getNativePathSeparator() {
    return L':';
}

dg_char File::getNativeSeparatorChar() {
    return L'/';
}

bool File::isHidden() {
    String* fileName = this->getName();
    bool result = fileName->startsWith(".");
    SafeDelete(fileName);
    return result;
}

bool File::exists() {
    struct stat s;
    int result;

    Array<char> utf8Path = this->path->getBytes("UTF-8");
    return access(utf8Path.raw(), F_OK) == 0;
}

bool File::isDirectory() {
    struct stat s;
    int result;

    Array<char> utf8Path = this->path->getBytes("UTF-8");
    result = stat(utf8Path.raw(), &s);

    if(result != 0){
        return false;
    }

    return ((s.st_mode & S_IFDIR) != 0);
}

bool FileMkdirInternal(const String* path) {
    struct stat s;
    int result;

    Array<char> utf8Path = path->getBytes("UTF-8");

    // if the dir already exists and return true
    if(access(utf8Path.raw(), F_OK) == 0){
        return true;
    }

    if(mkdir(utf8Path.raw(), 0777) == -1) {
        logger->debug(strerror(errno));
        return false;
    }

    return true;
}


bool File::canExecute() {
    struct stat s;
    int result;

    Array<char> utf8Path = this->path->getBytes("UTF-8");
    result = stat(utf8Path.raw(), &s);

    if(result != 0){
        return false;
    }

    return ((s.st_mode & S_IEXEC) != 0);
}

bool File::canRead() {
    struct stat s;
    int result;

    Array<char> utf8Path = this->path->getBytes("UTF-8");
    result = stat(utf8Path.raw(), &s);

    if(result != 0){
        return false;
    }

    return ((s.st_mode & S_IREAD) != 0);
}

bool File::canWrite() {
    struct stat s;
    int result;

    Array<char> utf8Path = this->path->getBytes("UTF-8");
    result = stat(utf8Path.raw(), &s);

    if(result != 0){
        return false;
    }

    return ((s.st_mode & S_IWRITE) != 0);
}

bool File::del() {
    if (!exists())
        return true;

    const Array<char> utf8Path = this->path->getBytes("UTF-8");

    if (isDirectory())
        return rmdir(utf8Path.raw()) == 0;

    return remove(utf8Path.raw()) == 0;
}

dg_long File::length() {
    struct stat s;
    int result;

    Array<char> utf8Path = this->path->getBytes("UTF-8");
    result = stat(utf8Path.raw(), &s);

    if(result != 0){
        return 0ll;
    }

    return s.st_size;
}

bool File::renameTo(const File* dest) const {
    return false;
}


String* File::getAbsolutePath() const {
    if(isAbsolute()) {
        return new String(this->path);
    }

    char* pwd = getcwd(NULL, 0);

    if(pwd != null) {
        String* path01 = new String(pwd);

        String* path02 = path01->concat(File::separator);
        SafeDelete(path01);

        path01 = path02->concat(this->path);
        SafeDelete(path02);

        return path01;
    }

    return new String(this->path);
}

// -----------------------travel files----------------------------------
void FileListFilesInternal(ArrayList<String>* outFileNames, const char* path) {
    struct stat s;
    DIR *dir;
    struct dirent *dt;

    if (stat(path, &s) < 0) {
        logger->error(strerror(errno));
        return;
    }

    if (S_ISDIR(s.st_mode)) {
        if ((dir = opendir(path)) == NULL) {
            logger->error("opendir error\n");
            return;
        }

        if (chdir(path) < 0) {
            logger->error("chdir error\n");
            return;
        }

        while ((dt = readdir(dir)) != NULL) {
            if (dt->d_name[0] == '.') {
                continue;
            }

            logger->debug("find fileName: %s\n", dt->d_name);

            outFileNames->add(new String(dt->d_name));
        }

        if (chdir("..") < 0) {
            logger->error("chdir error\n");
        }

        if (closedir(dir) < 0) {
            logger->error("closedir error\n");
        }
    } else {
        logger->error("the path is file\n");
    }
}

const Array<String*> File::list() const {
    Array<char> utf8Path = path->getBytes("UTF-8");

    ArrayList<String>* fileNames = new ArrayList<String>();

    FileListFilesInternal(fileNames, utf8Path);

    Array<String*> result = fileNames->toArray();
    SafeDelete(fileNames);
    return result;
}