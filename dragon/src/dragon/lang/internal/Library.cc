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
 * Created:     2013/07/25
 **********************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
 
#include <dragon/lang/internal/platform.h>
#include <dragon/lang/internal/Library.h>

Import dragon::lang::internal;

Library::Library(const char* libPath) 
	:resolved(dg_false) {
	if (libPath != null) {
		char* buf = (char*)malloc(strlen(libPath) + 1);
		strcpy(buf, libPath);
		this->libPath = buf;
	}

	this->classTree = (ClassTree*)malloc(sizeof(ClassTree));
	this->classTree->spaces = NULL;
}

const char* Library::getPath() const {
	return this->libPath;
}

// -------------------------------------------------
// free class tree
// 

void free_export_symbol(Library::ExportSymbol* es) {
	if (es != NULL) {
		free(es);
	}
}

void free_name_space(Library::NameSpace* space) {
	if (space != NULL) {
		free_name_space(space->spaces);
		space->spaces = NULL;

		free_name_space(space->next);
		space->next = NULL;

		SafeFree(space->symbols);
		SafeFree(space->name);

		SafeFree(space);
	}
}

void free_class_tree(Library::ClassTree* tree) {
	if (tree != NULL) {
		free_name_space(tree->spaces);
		free(tree);
	}
}

Library::~Library() {
	SafeFree(this->libPath);

	free_class_tree(this->classTree);
	this->classTree = NULL;
}


// -------------------------------------------------
// findClassDefine
//
Library::NameSpace* find_namespace(Library::NameSpace* head, const char* symbol, int offset, size_t len) {
	Library::NameSpace* p = head;

	while(p != NULL && (strlen(p->name)!=len || 
		memcmp(symbol + offset, p->name, len)!=0x0)) {
		p = p->next;
	}

	return p;
}

Library::NameSpace* Library::findClassDefine(const char* name) {
	Library::NameSpace* ret = NULL;
	Library::NameSpace* spaces = this->classTree->spaces;

	int offset = 0;
	size_t len = 0;

	const char* pch = NULL;
	do {
		pch = strstr(name + offset, "::");
		if (pch != NULL) {
			len = pch - name - offset;
		} else {
			len = strlen(name) - offset;
		}

		ret = find_namespace(spaces, name, offset, len);
		if (ret != NULL) {
			spaces = ret->spaces;
		}

		offset=pch - name + 2;
	} while(pch != NULL);

	return ret;
}