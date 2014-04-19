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
static Logger* logger = Logger::getLogger(ObjMTLLoader::TYPE, INFO);

ObjMTLLoader::ObjMTLLoader() {

}

ObjMTLLoader::~ObjMTLLoader() {

}

List<Material>* ObjMTLLoader::load(Resource* res) throw(ModelLoadException*) {
    if (res == null) {
        return null;
    }

    String* uri = res->getURI();
    const Array<byte> utf8 = uri->getBytes("UTF-8");
    logger->info("the mtl uri: %s", utf8.raw());
    SafeRelease(uri);

    Ref<InputStream> stream = res->getInputStream();
    Ref<Reader> reader = new InputStreamReader(stream.raw());
    Ref<Scanner> scanner = new Scanner(reader.raw());

    List<Material>* materials = new ArrayList<Material>();

    Material* cm = null;

    while(scanner->hasNext()) {
        String* token = scanner->next();

        if (token->equals("newmtl")) {
            if (cm != null) {
                materials->add(cm);
            } 
            
            cm = new Material();
            cm->setName(scanner->next());
        } else if (token->equals("#")) {
            ;
        } else if (token->equals("Ka")) {
            float kaRed = scanner->nextFloat();
            float kaGreen = scanner->nextFloat();
            float kaBlue = scanner->nextFloat();

            cm->setColor("_AmbientColor", Color(kaRed, kaGreen, kaBlue));
        } else if (token->equals("Kd")) {
            float kdRed = scanner->nextFloat();
            float kdGreen = scanner->nextFloat();
            float kdBlue = scanner->nextFloat();

            cm->setColor("_DiffuseColor", Color(kdRed, kdGreen, kdBlue));
        } else if (token->equals("Ks")) {
            float ksRed = scanner->nextFloat();
            float ksGreen = scanner->nextFloat();
            float ksBlue = scanner->nextFloat();

            cm->setColor("_SpecularColor", Color(ksRed, ksGreen, ksBlue));
        } else if (token->equals("d") || token->equals("Tr")) {
            float alpha = scanner->nextFloat();
            cm->setFloat("_Alpha", alpha);
        } else if (token->equals("Ns")) {
            float shininess = scanner->nextFloat();
            cm->setFloat("_Shininess", shininess);
        } else if (token->equals("illum")) {
            int illum = scanner->nextInt();
            cm->setInt("_Illum", illum);
        } else if (token->equals("map_Ka")) {
            ;
        }
        
        scanner->skip("\n");

        SafeRelease(token);
    }

    if (cm != null) {
        materials->add(cm);
    } 
   
    return materials;
}