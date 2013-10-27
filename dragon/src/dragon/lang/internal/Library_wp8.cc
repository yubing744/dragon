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

#include <windows.h>

#if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
	#include <libloaderapi.h>
	#include <synchapi.h>
	#include <processthreadsapi.h>
#else
	#include <process.h>
	#include <Dbghelp.h>
	#pragma comment(lib,"Dbghelp.lib")
#endif

// ----------------------------------------------------------------
// Private API 
#if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP

WINBASEAPI
_Ret_maybenull_
HMODULE
WINAPI
LoadLibraryA(
    _In_ LPCSTR lpLibFileName
    );

#endif


#include <dragon/lang/internal/Library.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include <dragon/lang/internal/platform.h>

Import dragon::lang::internal;

//-------------------------------------------------------------------
// Resolve Libary
// 

struct export_symbol {
	char* symbol;
	void* address;
};

// Process DLL Library
struct export_symbol* find_symbol_export_table(const char* path, size_t* addr_export_table_size) {
	HMODULE hModule = LoadLibraryA(path);

	if(hModule == NULL) {
		return NULL;
	}

	LONG pModuleBase = (LONG)hModule;

	IMAGE_DOS_HEADER* pDosHead = (IMAGE_DOS_HEADER*)pModuleBase;
	if(pDosHead->e_magic != IMAGE_DOS_SIGNATURE) {
		return NULL;
	}

	IMAGE_NT_HEADERS* pImageNTHead = (IMAGE_NT_HEADERS*)(pModuleBase + pDosHead->e_lfanew);
	if(pImageNTHead->Signature!=IMAGE_NT_SIGNATURE) {
		return NULL;
	}

	IMAGE_FILE_HEADER imageFileHead = pImageNTHead->FileHeader;
	if(imageFileHead.Machine != IMAGE_FILE_MACHINE_I386){
		return NULL;
	}

	IMAGE_DATA_DIRECTORY exportItem = pImageNTHead->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
	IMAGE_EXPORT_DIRECTORY* pImageExportDirectory = (IMAGE_EXPORT_DIRECTORY*)(pModuleBase + exportItem.VirtualAddress);

	DWORD OffsetStart = exportItem.VirtualAddress;
	DWORD Size = exportItem.Size;

	int numFuncs = pImageExportDirectory->NumberOfFunctions;
	int numNames = pImageExportDirectory->NumberOfNames;

	LPDWORD pAddressOfFunctions = (LPDWORD)(pImageExportDirectory->AddressOfFunctions + pModuleBase);
	LPDWORD pAddressOfNames = (LPDWORD)(pImageExportDirectory->AddressOfNames + pModuleBase);

	*addr_export_table_size = numNames;
	struct export_symbol* table = (struct export_symbol *)calloc(numFuncs, sizeof(struct export_symbol));

	for(int i=0; i<numFuncs; i++) {
		char* pName= (char*)(pAddressOfNames[i] + pModuleBase);
		FARPROC pfn = (FARPROC)(pAddressOfFunctions[i] + pModuleBase);
		
		table[i].address = (void*)pfn;
		table[i].symbol = pName;
	}

	return table;
}

Library::NameSpace* find_package(Library::NameSpace* head, const char* str, size_t len) {
	Library::NameSpace* p = head;

	while(p != NULL && (strlen(p->name)!=len || 
		memcmp(str, p->name, len)!=0x0)) {
		p = p->next;
	}

	return p;
}

const char* prev_token(const char* str, size_t len, char sep_char) {
	int i = len - 1;

	while(i >= 0) {
		char ch = str[i];

		if (ch == sep_char) {
			return str + i;
		}

		i--;
	}
	 
	return NULL;
}

Library::NameSpace* create_package(const char* str, size_t len) {
	Library::NameSpace* space = (Library::NameSpace*)calloc(0x1, sizeof(Library::NameSpace));

	if (space != NULL) {
		space->spaces = NULL;
		space->symbols = NULL;
		space->symbolCount = 0;

		if (len > 0) {
			char* token = (char*)malloc(len + 1);
			memcpy(token, str, len);
			token[len] = '\0';
			space->name = token;
		} else {
			space->name = NULL;
		}
	}

	return space;
}

size_t skip_template_param(const char* str, size_t len) {
	if (len > 2 && str[len - 1]=='@' && str[len - 2] == '@') {
		const char* sep = strstr(str, "@V");
		return sep - str;
	}

	return len;
}

void add_to_package(Library::NameSpace* parent, struct export_symbol * es, int offset, size_t len) {
	if (parent != NULL) {
		len = skip_template_param(es->symbol + offset, len);
		const char* token = prev_token(es->symbol + offset, len, '@');

		if (token) {
			Library::NameSpace* space = find_package(parent->spaces, token + 1, es->symbol + offset + len - token - 1);

			if (space == NULL) {
				space = create_package(token + 1, es->symbol + offset + len - token - 1);

				space->next = parent->spaces;
				parent->spaces = space;
			}

			add_to_package(space, es, offset,  token - es->symbol - offset);
		} else if ((es->symbol + offset)[0] == '?' && len > 2) { //for Operators, constructors, and destructors
			// ?0 ?1 ?2 ?3 ?4 ?H ?E
			offset+=2;
			len-=2;

			//for ?$
			if ((es->symbol + offset)[0] == '?') {
				offset += 2;
				len-=2;
			} else if((es->symbol + offset)[0] == '7') { //vtable
				offset += 1;
				len-=1;
			}

			Library::NameSpace* space = find_package(parent->spaces, es->symbol + offset, len);

			if (space == NULL) {
				space = create_package(es->symbol + offset, len);

				space->next = parent->spaces;
				parent->spaces = space;
			}

			add_to_package(space, es, offset,  0);
		} else if (len > 0) {
			Library::NameSpace* space = find_package(parent->spaces, es->symbol + offset, len);

			if (space == NULL) {
				space = create_package(es->symbol + offset, len);

				space->next = parent->spaces;
				parent->spaces = space;
			}

			add_to_package(space, es, offset,  0);
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

const char* find_param_sep(const char* str) {
	const char* sep = strstr(str, "@@");

	while (sep && sep[2] == '@') {
		sep = strstr(sep + 2, "@@");
	}

	return sep;
}

void add_to_tree(Library::ClassTree* tree, struct export_symbol * es, int offset) {
	const char* sep = find_param_sep(es->symbol + offset);
	const char* token = prev_token(es->symbol + offset, sep - es->symbol - offset, '@');

	if (token) {
		Library::NameSpace* space = find_package(tree->spaces, token + 1, sep - token - 1);

		if (space == NULL) {
			space = create_package(token + 1, sep - token - 1);

			space->next = tree->spaces;
			tree->spaces = space;
		}

		add_to_package(space, es, offset, token - es->symbol - offset);
	}
}

void free_export_symbol_table(struct export_symbol* table) {
	free(table);
}

void Library::resolve() {
	if (!this->resolved) {
		size_t symbol_count = 0;
		struct export_symbol *table = find_symbol_export_table(this->libPath, &symbol_count);

		const char* prefix_symbol = "?";
		size_t prefix_symbol_size = strlen(prefix_symbol);

		for(int i=0; i<symbol_count; i++) {
			struct export_symbol *es = table + i;
			if (memcmp(es->symbol, prefix_symbol, prefix_symbol_size)== 0x0) {
				add_to_tree(this->classTree, es, prefix_symbol_size);
			}
		}

		free_export_symbol_table(table);

		this->resolved = dg_true;
	}
}