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
 * Created:     2014/03/26
 **********************************************************************/

#include <dragon/io/InputStream.h>
#include <dragon/io/InputStreamReader.h>
#include <dragon/util/ArrayList.h>
#include <dragon/util/Scanner.h>
#include <dragon/util/logging/Logger.h>
#include <dragon/lang/gc/Reference.h>
#include <com/dragon3d/util/assets/modelio/plugins/obj/ObjMTLLoader.h>

Import dragon::io;
Import dragon::util;
Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::util::assets::modelio::plugins::obj;

const Type* ObjMTLLoader::TYPE = TypeOf<ObjMTLLoader>();
static Logger* logger = Logger::getLogger(ObjMTLLoader::TYPE, ERROR);

ObjMTLLoader::ObjMTLLoader() {

}

ObjMTLLoader::~ObjMTLLoader() {

}

List<Material>* ObjMTLLoader::load(Resource* res) throw(ModelLoadException*) {
    Ref<InputStream> stream = res->getInputStream();
    Ref<Reader> reader = new InputStreamReader(stream.raw());
    Ref<Scanner> scanner = new Scanner(reader.raw());

    List<Material>* materials = new ArrayList<Material>();

    /*
    Material* cm = null;

    while(scanner->hasNext()) {
        String* token = scanner->next();

        if (token->equals("newmtl")) {
            if (cm != null) {
                materials->add(cm);
            } 

            cm = new Material();
            cm->setName(scanner.next());
        } else if (token->equals("#")) {
            ;
        } else if (token->equals("Ka")) {
            this->parseMeshVertices(scanner, &vertices, vi++);
        } else if (token->equals("vt")) {
            this->parseMeshTextureVertices(scanner, &uvs, vti++);
        } else if (token->equals("vn")) {
            this->parseMeshVertexNormals(scanner, &normals, vni++);
        } else if (token->equals("f")) {
            this->parseMeshTriangleFace(scanner, mesh, vertices, uvs, normals);
        } else if (token->equals("mtllib")) {
            this->parseMaterialLib(model, res, scanner);
        } else if (token->equals("usemtl")) {
            ;
        } else if (token->equals("g")) {
            ;
        }
        
        scanner->skip("\n");

        SafeRelease(token);
    }
    */
   
    return materials;
}