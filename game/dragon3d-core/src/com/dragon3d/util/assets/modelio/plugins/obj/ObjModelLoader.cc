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

#include <vector>
#include <Delaunay.h>

#include <dragon/lang/Integer.h>

#include <dragon/lang/gc/Reference.h>
#include <dragon/util/logging/Logger.h>
#include <dragon/io/InputStreamReader.h>
#include <com/dragon3d/util/math/Vector3.h>
#include <com/dragon3d/util/assets/modelio/plugins/obj/ObjModelLoader.h>

Import std;

Import dragon::io;
Import dragon::util;
Import dragon::lang;
Import dragon::lang::gc;
Import dragon::util::logging;
Import com::dragon3d::util::math;
Import com::dragon3d::util::assets::modelio::plugins::obj;

const Type* ObjModelLoader::TYPE = TypeOf<ObjModelLoader>();
static Logger* logger = Logger::getLogger(ObjModelLoader::TYPE, ERROR);

ObjModelLoader::ObjModelLoader() {
    this->mtlLoader = new ObjMTLLoader();
}

ObjModelLoader::~ObjModelLoader() {
    SafeRelease(this->mtlLoader);
}

Model* ObjModelLoader::load(Resource* res) throw(ModelLoadException*) {
    Ref<InputStream> stream = res->getInputStream();
    this->load(res, stream.raw());
}

Model* ObjModelLoader::load(Resource* res, InputStream* stream) throw(ModelLoadException*) {
    Ref<Model> model = new Model();

    Ref<Reader> reader = new InputStreamReader(stream);
    loadFromReader(model.raw(), res, reader.raw());

    model->retain();
    return model.raw();  
}

void ObjModelLoader::loadFromReader(Model* model, Resource* res, Reader* reader) throw(ModelLoadException*) {
    Ref<Scanner> scanner = new Scanner(reader);
    loadFromScanner(model, res, scanner.raw());
}

void ObjModelLoader::loadFromScanner(Model* model, Resource* res, Scanner* scanner) throw(ModelLoadException*) {
    Mesh* mesh = new Mesh();

    int vi = 0;
    int vti = 0;
    int vni = 0;
    int ti = 0;

    Vector3* vertices = null;
    Vector2* uvs = null;
    Vector3* normals = null;

    while(scanner->hasNext()) {
        String* token = scanner->next();

        if (token->equals("o")) {
            this->parseModelName(scanner, model);
        } else if (token->equals("#")) {
            ;
        } else if (token->equals("v")) {
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
   
    // filter mesh
    this->filterMesh(mesh);

    model->setMesh(mesh);
    SafeRelease(mesh);
}

void ObjModelLoader::parseModelName(Scanner* scanner, Model* model) throw(ModelLoadException*) {
    String* name = scanner->next();
    model->setName(name);
    SafeRelease(name);
}

void ObjModelLoader::parseMeshVertices(Scanner* scanner, Vector3** pVertices, int n) throw(ModelLoadException*) {
    Vector3* vertices = *pVertices;

    vertices = (Vector3*)realloc(vertices, sizeof(Vector3) * (n + 1));

    if(!vertices) {
        logger->error("Couldn't (re)allocate memory. \n");
        throw new ModelLoadException("Couldn't (re)allocate memory for verteces!");
    }

    vertices[n].x = scanner->nextFloat();
    vertices[n].y = scanner->nextFloat();
    vertices[n].z = scanner->nextFloat();

    *pVertices = vertices;
}

void ObjModelLoader::parseMeshTextureVertices(Scanner* scanner, Vector2** puvs, int n) throw(ModelLoadException*) {
    Vector2* uvs = *puvs;

    uvs = (Vector2*)realloc(uvs, sizeof(Vector2) * (n + 1));

    if(!uvs) {
        logger->error("Couldn't (re)allocate memory. \n");
        throw new ModelLoadException("Couldn't (re)allocate memory for texture vertices!");
    }

    uvs[n].x = scanner->nextFloat();
    uvs[n].y = scanner->nextFloat();

    *puvs = uvs;
}

void ObjModelLoader::parseMeshVertexNormals(Scanner* scanner, Vector3** pnormals, int n) throw(ModelLoadException*) {
    Vector3* normals = *pnormals;

    normals = (Vector3*)realloc(normals, sizeof(Vector3) * (n + 1));

    if(!normals) {
        logger->error("Couldn't (re)allocate memory. \n");
        throw new ModelLoadException("Couldn't (re)allocate memory for vertex normals!");
    }

    normals[n].x = scanner->nextFloat();
    normals[n].y = scanner->nextFloat();
    normals[n].z = scanner->nextFloat();

    *pnormals = normals;
}

void ObjModelLoader_triangulate(vector<Vector3>& points, vector<int>& outTriangles) {
    vector<XYZ> vertices;
    vector<ITRIANGLE> triangles;

    for(int i = 0; i < points.size(); i++){
        Vector3 p = points[i];

        XYZ v;

        v.x = p.x;
        v.y = p.y;
        v.z = p.z;

        vertices.push_back(v);
    }

    int nv = vertices.size();
    //add 3 emptly slots, required by the Triangulate call
    vertices.push_back(XYZ());
    vertices.push_back(XYZ());
    vertices.push_back(XYZ());
    
    //allocate space for triangle indices
    triangles.resize(3*nv);
    
    int ntri;
    qsort(&vertices[0], vertices.size()-3, sizeof(XYZ), XYZCompare);
    Triangulate(nv, &vertices[0], &triangles[0], ntri);

    //copy triagles
    for(int i = 0; i < ntri; i++){
        outTriangles.push_back(triangles[i].p1);
        outTriangles.push_back(triangles[i].p2);
        outTriangles.push_back(triangles[i].p3);
    }
}

void ObjModelLoader_appendToMesh(Mesh* mesh, vector<Vector3>& vertices, vector<Vector2>& uvs, 
    vector<Vector3>& normals, vector<int>& triangles) {
    int vcount = vertices.size();

    mesh->vertices = (Vector3*)realloc(mesh->vertices, sizeof(Vector3) * (mesh->vertexCount + vcount));
    mesh->uv = (Vector2*)realloc(mesh->uv, sizeof(Vector2) * (mesh->vertexCount + vcount));
    mesh->normals = (Vector3*)realloc(mesh->normals, sizeof(Vector3) * (mesh->vertexCount + vcount));

    Array<int> indices = mesh->getTriangles();
    const int* data = indices.raw();
    int size = indices.length();

    int newSize = size + triangles.size();
    int* newData = (int*)malloc(sizeof(int) * newSize);
    memcpy(newData, data, sizeof(int) * size);

    // copy vertices
    for(int i = 0; i < vertices.size(); i++){
        Vector3 v = vertices[i];
        mesh->vertices[mesh->vertexCount + i] = v;
    }

    // copy uvs
    for(int i = 0; i < uvs.size(); i++){
        Vector2 uv = uvs[i];
        mesh->uv[mesh->vertexCount + i] = uv;
    }

    // copy normals
    for(int i = 0; i < normals.size(); i++){
        Vector3 normal = normals[i];
        mesh->normals[mesh->vertexCount + i] = normal;
    }

    mesh->vertexCount = mesh->vertexCount + vcount;

    // copy triangles
    for(int i = 0; i < triangles.size(); i++){
        int index = triangles[i];
        newData[size + i] = size + index;
    }

    mesh->setTriangles(Array<int>(newData, newSize, false));
}

void ObjModelLoader::parseMeshTriangleFace(Scanner* scanner, Mesh* mesh, 
        Vector3* tmpVertices, Vector2* tmpUVs, Vector3* tmpNormals) throw(ModelLoadException*) {
    vector<Vector3> vertices;
    vector<Vector2> uvs;
    vector<Vector3> normals;
    vector<int> triangles;

    while(scanner->hasNext("\\d+(/(\\d+)?(/(\\d+)?)?)?")) {
        String* tokenStr = scanner->next();

        Array<String*> vals = tokenStr->split("/");

        if (tmpVertices && vals.length() >= 1 
                && !vals[0]->equals("")) {
            Integer* vIndex = Integer::parseInt(vals[0]);
            Vector3 point = tmpVertices[vIndex->intValue() - 1];
            vertices.push_back(point);
            SafeRelease(vIndex);
        }

        if (tmpUVs && vals.length() >= 2 
                && !vals[1]->equals("")) {
            Integer* uvIndex = Integer::parseInt(vals[1]);
            Vector2 uv = tmpUVs[uvIndex->intValue() - 1];
            uvs.push_back(uv);
            SafeRelease(uvIndex);
        }

        if (tmpNormals && vals.length() >= 3 
                && !vals[2]->equals("")) {
            Integer* nIndex = Integer::parseInt(vals[2]);
            Vector3 normal = tmpNormals[nIndex->intValue() - 1];
            normals.push_back(normal);
            SafeRelease(nIndex);
        }

        SafeRelease(tokenStr);
    }

    if (vertices.size() > 3) {
        ObjModelLoader_triangulate(vertices, triangles);
    } else {
        for(int i = 0; i < vertices.size(); i++){
            triangles.push_back(i);
        }
    }

    ObjModelLoader_appendToMesh(mesh, vertices, uvs, normals, triangles);
}

void ObjModelLoader::parseMaterialLib(Model* model, Resource* baseRes, Scanner* scanner) throw(ModelLoadException*) {
    Ref<String> mtlPath = scanner->next();
    Ref<Resource> mtlRes = baseRes->getResource(mtlPath.raw());
    Ref<List<Material> > materials = mtlLoader->load(mtlRes.raw());

    model->setMaterials(materials.raw());
}

void ObjModelLoader::filterMesh(Mesh* mesh) {

}
