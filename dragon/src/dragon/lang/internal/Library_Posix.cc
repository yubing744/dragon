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


#include <dragon/lang/internal/Library.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include <dragon/lang/internal/Library_Posix.h>

Import dragon::lang::internal;

//---------------------------
//---------------------------
// resole package
size_t next_offset(const char* symbol, size_t* out_len) {
	size_t num = 0;

	size_t len = 0;
	while(isdigit(symbol[len])) {
		num =  num * 10 + (symbol[len] - '0');
		len++;
	}

	if (len > 0) {
		*out_len = len;
		return num;
	}

	return 0;
}

Library::NameSpace* find_package(Library::NameSpace* head, const char* symbol, int offset, size_t len) {
	Library::NameSpace* p = head;

	while(p != NULL && (strlen(p->name)!=len || 
		memcmp(symbol + offset, p->name, len)!=0x0)) {
		p = p->next;
	}

	return p;
}


Library::NameSpace* create_package(export_symbol * es, int offset, size_t len) {
	Library::NameSpace* space = (Library::NameSpace*)calloc(0x1, sizeof(Library::NameSpace));

	if (space != NULL) {
		space->spaces = NULL;
		space->symbols = NULL;
		space->symbolCount = 0;

		if (len > 0) {
			char* token = (char*)malloc(len + 1);
			memcpy(token, es->symbol + offset, len);
			token[len] = '\0';
			space->name = token;
		} else {
			space->name = NULL;
		}
	}

	return space;
}

void add_to_package(Library::NameSpace* parent, export_symbol * es, int offset) {
	if (parent != NULL) {
		size_t num_offset = 0;
		size_t num = next_offset(es->symbol + offset, &num_offset);
		if (num > 0) {
			Library::NameSpace* space = find_package(parent->spaces, es->symbol, offset + num_offset, num);

			if (space == NULL) {
				space = create_package(es, offset + num_offset, num);

				space->next = parent->spaces;
				parent->spaces = space;
			}

			add_to_package(space, es, offset + num_offset + num);
		} else {
			Library::NameSpace* space = parent;

			size_t symbol_count = space->symbolCount;

			if (space->symbols == NULL) {
				space->symbols = (Library::ExportSymbol*)malloc(sizeof(Library::ExportSymbol)*(symbol_count + 0x1));
			} else {
				space->symbols = (Library::ExportSymbol*)realloc(space->symbols, sizeof(Library::ExportSymbol)*(symbol_count+0x1));
			}

			space->symbols[symbol_count].address = es->address;
			space->symbols[symbol_count].symbol = es->symbol;

			space->symbolCount++;
		}
	}

}

void add_to_tree(Library::ClassTree* tree,export_symbol * es, int offset) {
	size_t num_offset;
	int num = next_offset(es->symbol + offset, &num_offset);
	if (num > 0) {
		Library::NameSpace* space = find_package(tree->spaces, es->symbol, offset + num_offset, num);

		if (space == NULL) {
			space = create_package(es, offset + num_offset, num);

			space->next = tree->spaces;
			tree->spaces = space;
		}

		add_to_package(space, es, offset + num_offset + num);
	}
}