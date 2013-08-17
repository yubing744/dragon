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

#include <dlfcn.h>
#include <mach/mach.h>
#include <mach-o/dyld.h>
#include <mach-o/nlist.h>
#include <mach-o/ldsyms.h>

#include <dragon/lang/internal/platform.h>

Import dragon::lang::internal;

//-------------------------------------------------------------------
// Resolve Libary
// 

typedef struct symbol_table_list_entry {
	union {
	   uint32_t n_strx;
	} n_un;
	uint8_t n_type;
	uint8_t n_sect;
	uint16_t n_desc;
} __attribute__ ((packed)) symbol_table_list_entry;

typedef struct segment_entry {
	uint32_t cmd;
	uint32_t cmdsize;
	char segname[0x10];
} __attribute__ ((packed)) segment_entry;

typedef struct seg32_data {
	uint32_t vmaddr;
	uint32_t vmsize;
	uint32_t fileoff;
} __attribute__ ((packed)) seg32_data;

typedef struct seg64_data {
	uint64_t vmaddr;
	uint64_t vmsize;
	uint64_t fileoff;
} __attribute__ ((packed)) seg64_data;

struct export_symbol {
	char* symbol;
	void* address;
} __attribute__ ((packed)) export_symbol;


const char* find_image_path_by_name(const char* name) {
	uint32_t count = _dyld_image_count();

	for (uint32_t i = 0x0; i < count; i++) {
		const char* image_path = _dyld_get_image_name(i);
		int ip_len = strlen(image_path);
		int name_len = strlen(name);

		const char* end_part = image_path + (ip_len - name_len);
		if (strcmp(end_part, name) == 0x0) {
			return image_path;
			break;
		}
	}

	return NULL;
}

size_t find_image_num(const char* path) {
	uint32_t count = _dyld_image_count();

	for (uint32_t i = 0x0; i < count; i++) {
		const char* image_path = _dyld_get_image_name(i);
		if (strcmp(image_path, path) == 0x0) {
			return i;
			break;
		}
	}

	return -1;
}

const struct mach_header* get_mach_header(const char* path) {
	size_t image_num = find_image_num(path);

	if (image_num != -1) {
		return _dyld_get_image_header(image_num);
	}

	return NULL;
}

bool is_64bit_image(const struct mach_header *image_header) {
	return ((image_header->cputype == CPU_TYPE_X86_64 || image_header->cputype == CPU_TYPE_POWERPC64) 
		&& (image_header->magic == MH_MAGIC_64 || image_header->magic == MH_CIGAM_64) ? true : false);
}

size_t find_symtab_cmds(const struct mach_header *image_header, struct symtab_command **addr_symtab_cmds) {
	bool is_64 = is_64bit_image(image_header);

	struct load_command *load_cmd = (struct load_command *)((char*)image_header + (is_64 ? sizeof(struct mach_header_64) : sizeof(struct mach_header)));
	struct symtab_command *symtab_cmds = (struct symtab_command *)calloc(0x1, sizeof(struct symtab_command));

	size_t symtab_count = 0x0;

	for (uint32_t i = 0x0; i < image_header->ncmds; i++) {
		if (load_cmd->cmd == LC_SYMTAB) {
			symtab_cmds = (struct symtab_command *)realloc(symtab_cmds, (symtab_count + 1)*sizeof(struct symtab_command));
			symtab_cmds[symtab_count] = *(struct symtab_command *)load_cmd;
			symtab_count++;
		}

		load_cmd = (struct load_command *)((char*)load_cmd + load_cmd->cmdsize);
	}

	*addr_symtab_cmds = symtab_cmds;
	return symtab_count;	
}

struct load_command* find_segment(const struct mach_header *image_header, const char* to_find_segname) {
	bool is_64 = is_64bit_image(image_header);

	struct load_command *load_cmd = (struct load_command *)((char*)image_header + (is_64 ? sizeof(struct mach_header_64) : sizeof(struct mach_header)));

	struct load_command *return_seg = NULL;

	for (uint32_t i = 0x0; i < image_header->ncmds; i++) {
		if (load_cmd->cmd == (is_64 ? LC_SEGMENT_64 : LC_SEGMENT)) {
			struct segment_entry *seg = (struct segment_entry*)load_cmd;

			if (!strncmp(to_find_segname, seg->segname, sizeof(seg->segname))) {
				return_seg = load_cmd;
				break;
			} 
		}

		load_cmd = (struct load_command *)((char*)load_cmd + load_cmd->cmdsize);
	}

	return return_seg;
}

struct export_symbol* find_symbol_export_table(const char* path, size_t* addr_export_table_size) {
	size_t image_num = find_image_num(path);
	const struct mach_header *image_header = get_mach_header(path);
	bool is_64 = is_64bit_image(image_header);

	struct symtab_command *symtab_cmds = null;
	size_t symtab_count = find_symtab_cmds(image_header, &symtab_cmds);

	struct load_command *text_seg = find_segment(image_header, SEG_TEXT);
	struct load_command *link_seg = find_segment(image_header, SEG_LINKEDIT);

	struct export_symbol* table = (struct export_symbol *)calloc(0x1, sizeof(struct export_symbol));

	void* symbol_address = 0x0;
	size_t symbol_count = 0x0;


	for (uint32_t i = 0x0; i < symtab_count; i++) {
		struct symtab_command *cmd = (struct symtab_command *)(&(symtab_cmds[i]));
		uint64_t fslide = 0x0, mslide = 0x0;

		if (is_64) {
			struct seg64_data *text_data = (struct seg64_data *)((char*)text_seg + sizeof(struct segment_entry));
			struct seg64_data *link_data = (struct seg64_data *)((char*)link_seg + sizeof(struct segment_entry));
			fslide = (uint64_t)(link_data->vmaddr - text_data->vmaddr) - link_data->fileoff;
			mslide = (uint64_t)((char*)image_header - text_data->vmaddr);
		} else {
			struct seg32_data *text_data = (struct seg32_data *)((char*)text_seg + sizeof(struct segment_entry));
			struct seg32_data *link_data = (struct seg32_data *)((char*)text_seg + sizeof(struct segment_entry));
			fslide = (uint64_t)(link_data->vmaddr - text_data->vmaddr) - link_data->fileoff;
			mslide = (uint64_t)((char*)image_header - text_data->vmaddr);
		}

		struct symbol_table_list_entry *entry = (struct symbol_table_list_entry *)((char*)image_header + cmd->symoff + fslide);

		for (uint32_t j = 0x0; j < cmd->nsyms; j++) {
			if (!(entry->n_type & N_STAB) && ((entry->n_type & N_TYPE) == N_SECT)) {
				char *str_table = (char*)image_header + cmd->stroff + fslide;
				if (is_64) {
					uint64_t *n_value = (uint64_t*)((char*)entry + sizeof(struct symbol_table_list_entry));
					symbol_address = (void*)*n_value;
				} else {
					uint32_t *n_value = (uint32_t*)((char*)entry + sizeof(struct symbol_table_list_entry));
					symbol_address = (void*)*n_value;
				}

				table = (struct export_symbol*)realloc(table, sizeof(struct export_symbol)*(symbol_count+0x1));

				table[symbol_count].address = (char*)symbol_address + _dyld_get_image_vmaddr_slide(image_num);
				table[symbol_count].symbol = ((char *)str_table + entry->n_un.n_strx);

				symbol_count++;
			}

			entry = (struct symbol_table_list_entry *)((char*)entry + (sizeof(struct symbol_table_list_entry) + (is_64 ? sizeof(uint64_t) : sizeof(uint32_t))));
		}
	}

	if (symtab_cmds != NULL) {
		free(symtab_cmds);
	}

	*addr_export_table_size = symbol_count;
	return table;
}

void free_export_symbol_table(struct export_symbol* table) {
	free(table);
}

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


Library::NameSpace* create_package(struct export_symbol * es, int offset, size_t len) {
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

void add_to_package(Library::NameSpace* parent, struct export_symbol * es, int offset) {
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
			space->symbols[symbol_count].symbol = es->symbol + 1; //__NS to _NS

			space->symbolCount++;
		}
	}

}

void add_to_tree(Library::ClassTree* tree, struct export_symbol * es, int offset) {
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

void Library::resolve() {
	if (!this->resolved) {
		size_t symbol_count = 0;
		struct export_symbol *table = find_symbol_export_table(this->libPath, &symbol_count);

		const char* prefix_symbol = "__ZN";
		size_t prefix_symbol_size = strlen(prefix_symbol);

		for(int i=0; i<symbol_count; i++) {
			struct export_symbol *es = table + i;
			if (memcmp(es->symbol, prefix_symbol, prefix_symbol_size)== 0x0 
				&& isdigit(es->symbol[prefix_symbol_size])) {
				//printf("address: 0x%x, symbol: %s\n", es->address, es->symbol);
				add_to_tree(this->classTree, es, prefix_symbol_size);
			}
		}

		free_export_symbol_table(table);

		this->resolved = dg_true;
	}
}

