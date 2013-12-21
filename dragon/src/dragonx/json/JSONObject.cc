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
 * Created:     2013/12/15
 **********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <locale.h>
#include <getopt.h>
#include <errno.h>

#include <json.h>

#include <dragon/lang/Null.h>
#include <dragon/lang/Boolean.h>
#include <dragon/lang/Integer.h>
#include <dragon/lang/Float.h>
#include <dragon/lang/Double.h>

#include <dragon/util/HashMap.h>
#include <dragon/util/logging/Logger.h>
#include <dragonx/json/JSONObject.h>
#include <dragonx/json/JSONArray.h>
#include <dragonx/json/JSONException.h>


Import dragon::lang;
Import dragonx::json;
Import dragon::util::logging;

static Logger* logger = Logger::getLogger("dragonx::json::JSONObject", ERROR);

char *indent_string = NULL;

char *string_of_errors[] = {
    "",
    "out of memory",
    "bad character",
    "stack empty",
    "pop unexpected mode",
    "nesting limit",
    "data limit",
    "comment not allowed by config",
    "unexpected char",
    "missing unicode low surrogate",
    "unexpected unicode low surrogate",
    "error comma out of structure",
    "error in a callback",
    "utf8 validation error"
};

int process_file(json_parser *parser, const String& json, int *retlines, int *retcols) {
    int ret = 0;
    int32_t read;
    int lines, col, i;

    lines = 1;
    col = 0;

    const Array<byte> data = json.getBytes("UTF-8");
    const char* buffer = data.raw();
    read = data.size();

    uint32_t processed;

    ret = json_parser_string(parser, buffer, read, &processed);

    for (i = 0; i < processed; i++) {
        if (buffer[i] == '\n') { col = 0; lines++; } else col++;
    }
  
    if (retlines) *retlines = lines;
    if (retcols) *retcols = col;

    return ret;
}

static void* tree_create_structure(int nesting, int is_object) {
    if (is_object) {
        return new JSONObject();
    } else {
        return new JSONArray();
    }
}

static void *tree_create_data(int type, const char *data, uint32_t length) {
    Object* val = null;

    String* str = new String(data, length);

    switch (type) {
    case JSON_FALSE:
        val = new Boolean(false);
        break;
    case JSON_TRUE:
        val = new Boolean(true);
        break;
    case JSON_NULL:
        val = new Null();
        break;
    case JSON_INT:
        val = Integer::parseInt(str);
        break;
    case JSON_STRING:
        val = new String(str);
        break;
    case JSON_FLOAT:
        val = Float::parseFloat(str);
        break;
    default:
        break;
    }

    SafeDelete(str);

    return val;
}

static int tree_append(void *structure, char *key, uint32_t key_length, void *obj) {
    Object *parent = (Object*)structure;
    Object* value = (Object*)obj;

    if (key) {
        String* strKey = new String(key, key_length);

        JSONObject* node = (JSONObject*)parent;
        node->put(strKey, value);
    } else {
        JSONArray* array = (JSONArray*)parent;
        JSONObject* obj = (JSONObject*)value;

        array->add(obj);   
    }

    return 0;
}

static int do_tree(json_config *config, const String& json, JSONObject **root_structure) {
    json_parser parser;
    json_parser_dom dom;
    int ret;
    int col, lines;

    ret = json_parser_dom_init(&dom, tree_create_structure, tree_create_data, tree_append);
    if (ret) {
        logger->error("error: initializing helper failed: [code=%d] %s\n", ret, string_of_errors[ret]);
        return ret;
    }

    ret = json_parser_init(&parser, config, json_parser_dom_callback, &dom);
    if (ret) {
        logger->error("error: initializing parser failed: [code=%d] %s\n", ret, string_of_errors[ret]);
        return ret;
    }

    ret = process_file(&parser, json, &lines, &col);
    if (ret) {
        logger->error("line %d, col %d: [code=%d] %s\n",
                lines, col, ret, string_of_errors[ret]);

        return 1;
    }

    ret = json_parser_is_done(&parser);
    if (!ret) {
        logger->error("syntax error\n");
        return 1;
    }

    if (root_structure)
        *root_structure = (JSONObject*)dom.root_structure;

    /* cleanup */
    json_parser_free(&parser);

    return 0;
}

JSONObject* JSONObject::parse(const String& json) {
    json_config config;

    memset(&config, 0, sizeof(json_config));

    config.max_nesting = 0;
    config.max_data = 0;
    config.allow_c_comments = 1;
    config.allow_yaml_comments = 1;

    JSONObject* jsonObj = new JSONObject();

    int ret = do_tree(&config, json, &jsonObj);

    if (ret) {
        const Array<byte> data = json.getBytes("UTF-8");
        logger->error("error in parse json: %s", data.raw());
    }

    return jsonObj;
}

JSONObject::JSONObject() {

}

JSONObject::~JSONObject() {

}

Object* JSONObject::getObject(const String& key) {
    Object* val = (Object*)this->get(key);

    if (val == null) {
        throw new JSONException("not found value with key!");
    }

    return val;
}

String* JSONObject::getString(const String& key) {
    return (String*)this->getObject(key);
}

int JSONObject::getInt(const String& key) {
    Integer* val = (Integer*)this->getObject(key);
    return val->intValue();
}

float JSONObject::getFloat(const String& key) {
    Float* val = (Float*)this->getObject(key);
    return val->floatValue();
}

double JSONObject::getDouble(const String& key) {
    Double* val = (Double*)this->getObject(key);
    return val->doubleValue();
}

bool JSONObject::getBoolean(const String& key) {
    Boolean* val = (Boolean*)this->getObject(key);
    return val->boolValue();
}

JSONObject* JSONObject::getJSONObject(const String& key) {
    JSONObject* val = (JSONObject*)this->getObject(key);
    return val;    
}
