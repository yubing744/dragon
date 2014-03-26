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


#ifndef ObjModelLoader_Obj_Plugins_Modelio_Assets_Util_Dragon3d_Com_H
#define ObjModelLoader_Obj_Plugins_Modelio_Assets_Util_Dragon3d_Com_H

#include <dragon/config.h>
#include <dragon/lang/Object.h>
#include <dragon/io/Reader.h>
#include <dragon/util/Scanner.h>
#include <com/dragon3d/util/assets/modelio/ModelLoader.h>
#include <com/dragon3d/util/assets/modelio/plugins/obj/ObjMTLLoader.h>

BeginPackage7(com, dragon3d, util, assets, modelio, plugins, obj)

Import dragon::util;
Import dragon::lang;
Import com::dragon3d::util::assets::modelio;
Import com::dragon3d::util::assets::modelio::plugins::obj;

class_ ObjModelLoader extends(Object) 
    implements1(ModelLoader) {
public:
    static const Type* TYPE;
    
public:
    ObjModelLoader();
    virtual ~ObjModelLoader();

public:
    virtual Model* load(Resource* res) throw(ModelLoadException*);
    
protected:
    virtual Model* load(Resource* res, InputStream* stream) throw(ModelLoadException*);
    virtual void loadFromReader(Model* model, Resource* res, Reader* reader) throw(ModelLoadException*);
    virtual void loadFromScanner(Model* model, Resource* res, Scanner* scanner) throw(ModelLoadException*);

    virtual void parseModelName(Scanner* scanner, Model* model) throw(ModelLoadException*);
    virtual void parseMeshVertices(Scanner* scanner, Vector3** pVertices, int n) throw(ModelLoadException*);
    virtual void parseMeshTextureVertices(Scanner* scanner, Vector2** pTextures, int n) throw(ModelLoadException*);
    virtual void parseMeshVertexNormals(Scanner* scanner, Vector3** pNormals, int n) throw(ModelLoadException*);
    virtual void parseMeshTriangleFace(Scanner* scanner, Mesh* mesh, Vector3* vertices, Vector2* uvs, Vector3* normals) throw(ModelLoadException*);

    virtual void parseMaterialLib(Model* model, Resource* baseRes, Scanner* scanner) throw(ModelLoadException*);

    virtual void filterMesh(Mesh* mesh);

protected:
    ObjMTLLoader* mtlLoader;
};//ObjModelLoader

EndPackage7 //(com, dragon3d, util, assets, modelio, plugins, obj)

#endif //ObjModelLoader_Obj_Plugins_Modelio_Assets_Util_Dragon3d_Com_H
