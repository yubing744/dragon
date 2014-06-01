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

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2014/02/11
 **********************************************************************/

#include <dragon/lang/gc/Reference.h>

#include <dragon/lang/String.h>
#include <dragon/lang/System.h>
#include <dragon/lang/StringBuffer.h>

#include <dragon/io/File.h>
#include <dragon/io/FileInputStream.h>
#include <dragon/io/InputStream.h>
#include <dragon/io/IOException.h>
#include <dragon/io/FileNotFoundException.h>

#include <dragon/util/logging/Logger.h>

#include <com/dragon3d/util/assets/Resource.h>
#include <com/dragon3d/util/assets/AssetsManager.h>
#include <com/dragon3d/util/assets/ResourceNotFoundException.h>

Import dragon::lang::gc;
Import dragon::lang;
Import dragon::io;

Import dragon::util::logging;
Import com::dragon3d::util::assets;

static Logger* logger = Logger::getLogger("Resource#android", ERROR);

#include "jni/Resource_jni.cc"

/**
 * the Assets input Stream
 * 
 * @param  InputStream [description]
 * @return             [description]
 */
class_ AssetsInputStream extends(InputStream) {
public:
    AssetsInputStream(const String& path) throw(FileNotFoundException*) {
        this->path = new String(path);
        this->open();
    }

    virtual ~AssetsInputStream() {
        this->close();
        SafeRelease(this->path);
    }

public:
    virtual void open() {
        const Array<char> utf8Path = this->path->toUTF8CharArray();

        AAsset* asset = NULL;

        if ((asset = AAssetManager_open(AAsetsMgr, utf8Path, AASSET_MODE_UNKNOWN)) == NULL) {
            Ref<String> msg = String::format("asset not found with path %s", utf8Path);
            throw new ResourceNotFoundException(msg);
        }

        this->asset = asset;
    }

    virtual wlong_u skip(wlong_u n) throw(IOException*) {
        if (this->asset != NULL) {
            off_t sc = AAsset_seek(this->asset, n, SEEK_SET);
            this->pos += sc;

            return sc;
        }

        return -1;
    }

    virtual int read(byte* b, int num, int off, int len) throw(IOException*) {
        int result = 0;

        if (this->asset != NULL) {
            result = AAsset_read(this->asset, b + off, len);
            this->pos += result;
        }

        return (int) result;
    }

    virtual void close() throw(IOException*) {
        if (this->asset != NULL) {
            AAsset_close(this->asset);
        }
    }

public:
    virtual bool markSupported() const {
        return true;
    }

    virtual void mark(int readlimit) {
        AAsset* f = (AAsset*)this->asset;

        if (f != NULL) {
            long pos = this->pos;

            this->marklimit = readlimit;
            this->markpos = pos;
        } 
    }

    virtual void reset() throw(IOException*) {
        AAsset* f = (AAsset*)this->asset;

        if (f != NULL) {
            AAsset_seek(f, this->markpos, SEEK_SET);
            this->pos = this->markpos;
        }   
    }

    virtual int available() const {
        AAsset* f = (AAsset*)this->asset;

        if (f != NULL) {
            return AAsset_getRemainingLength(f);
        }   

        return 0;
    }

protected:
    String* path;
    AAsset* asset;
    size_t pos;

    int markpos;
    int marklimit;
};

InputStream* Resource::getInputStream() {
    return new AssetsInputStream(this->uri);
}

bool Resource::exists() {
    const Array<char> utf8Path = this->uri->toUTF8CharArray();

    AAsset* asset = NULL;

    if ((asset = AAssetManager_open(AAsetsMgr, utf8Path, AASSET_MODE_UNKNOWN)) != NULL) {
        AAsset_close(asset);
        return true;
    }

    return false;
}

List<Resource>* Resource::getSubResources() {
    List<Resource>* results = new ArrayList<Resource>();

    const Array<char> baseURI = this->uri->toUTF8CharArray();

    AAssetDir* baseDir = AAssetManager_openDir(AAsetsMgr, baseURI);

    if (baseDir != null) {
        AAssetDir_rewind(baseDir);

        const char* name;

        while((name = AAssetDir_getNextFileName(baseDir)) != NULL) {
            Ref<Resource> subRes = this->getResource(name);
            results->add(subRes);
        }

        AAssetDir_close(baseDir);
    }

    return results;
}

bool Resource::hasSubs() {
    const Array<char> baseURI = this->uri->toUTF8CharArray();

    AAssetDir* baseDir = AAssetManager_openDir(AAsetsMgr, baseURI);

    if (baseDir != null) {
        AAssetDir_rewind(baseDir);
        
        if(AAssetDir_getNextFileName(baseDir) != NULL) {
            return true;
        }
    }

    return false;
}