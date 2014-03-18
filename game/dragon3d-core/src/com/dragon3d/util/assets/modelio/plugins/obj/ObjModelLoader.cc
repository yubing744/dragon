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
 * Created:     2014/03/16
 **********************************************************************/

#include <dragon/lang/gc/Reference.h>
#include <dragon/util/logging/Logger.h>
#include <com/dragon3d/util/assets/modelio/plugins/obj/ObjModelLoader.h>
#include <dragon/io/InputStreamReader.h>
#include <com/dragon3d/util/math/Vector3.h>

Import dragon::io;
Import dragon::util;
Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::util::math;
Import com::dragon3d::util::assets::modelio::plugins::obj;

const Type* ObjModelLoader::TYPE = TypeOf<ObjModelLoader>();
static Logger* logger = Logger::getLogger(ObjModelLoader::TYPE, ERROR);

ObjModelLoader::ObjModelLoader() {

}

ObjModelLoader::~ObjModelLoader() {

}

Model* ObjModelLoader::load(InputStream* stream) throw(ModelLoadException*) {
    Ref<Model> model = new Model();

    Ref<Reader> reader = new InputStreamReader(stream);
    loadFromReader(model.raw(), reader.raw());

    model->retain();
    return model.raw();  
}

void ObjModelLoader::loadFromReader(Model* model, Reader* reader) throw(ModelLoadException*) {
    Ref<Scanner> scanner = new Scanner(reader);
    loadFromScanner(model, scanner.raw());
}

void ObjModelLoader::loadFromScanner(Model* model, Scanner* scanner) throw(ModelLoadException*) {
    Mesh* mesh = new Mesh();
    String* name = null;

    while(scanner->hasNextChar()) {
        wchar_u ch = scanner->nextChar();

        switch(ch) {
            case 'o': //Object name 
                 // If format is not "%SIZE-1s" overflow is possible 
                name = scanner->next();
                model->setName(name);
                SafeRelease(name);
                break;
            case 'v':  
                mesh->vertices = (Vector3*)realloc(mesh->vertices,
                        sizeof(Vector3) * (mesh->vertexCount + 1));
                if(!mesh->vertices) {
                    logger->error("Couldn't (re)allocate memory. \n");
                    SafeRelease(mesh);
                    throw new ModelLoadException("Couldn't (re)allocate memory for verteces!");
                }

                mesh->vertices[mesh->vertexCount].x = scanner->nextFloat();
                mesh->vertices[mesh->vertexCount].y = scanner->nextFloat();
                mesh->vertices[mesh->vertexCount].z = scanner->nextFloat();

                mesh->vertexCount++;
                break;

            default: // Unknown param. skipping the line 
                scanner->skip("\n");
                break;

        };
    }

    model->setMesh(mesh);
    SafeRelease(mesh);
}
