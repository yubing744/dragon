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


#include <dragon/lang/internal/Library_posix.h>

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


const char* find_image_path_by_name(const char* name) {
	uint32_t count = _dyld_image_count();

	for (uint32_t i = 0x0; i < count; i++) {
		const char* image_path = _dyld_get_image_name(i);
		int ip_len = strlen(image_path);
		int name_len = strlen(name);

		const char* end_part = image_path + (ip_len - name_len);
		if (strcmp(end_part, name) == 0x0) {
			return image_path;
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

export_symbol* find_symbol_export_table(const char* path, size_t* addr_export_table_size) {
	void *handle = dlopen(path, RTLD_LAZY);

	size_t image_num = find_image_num(path);
	const struct mach_header *image_header = get_mach_header(path);
	bool is_64 = is_64bit_image(image_header);

	struct symtab_command *symtab_cmds = null;
	size_t symtab_count = find_symtab_cmds(image_header, &symtab_cmds);

	struct load_command *text_seg = find_segment(image_header, SEG_TEXT);
	struct load_command *link_seg = find_segment(image_header, SEG_LINKEDIT);

	export_symbol* table = (export_symbol *)calloc(0x1, sizeof(export_symbol));

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
			struct seg32_data *link_data = (struct seg32_data *)((char*)link_seg + sizeof(struct segment_entry));

			fslide = (uint64_t)(link_data->vmaddr - text_data->vmaddr) - link_data->fileoff;
			mslide = (uint64_t)((char*)image_header - text_data->vmaddr);
		}

		char *str_table = (char*)image_header + cmd->stroff + fslide;
		symbol_table_list_entry *entry = (symbol_table_list_entry *)((char*)image_header + cmd->symoff + fslide);

		for (uint32_t j = 0x0; j < cmd->nsyms; j++) {
			// https://developer.apple.com/library/mac/documentation/DeveloperTools/Conceptual/MachORuntime/Reference/reference.html#//apple_ref/c/tag/nlist
			if (!(entry->n_type & N_STAB) && ((entry->n_type & N_TYPE) == N_SECT)) {
				if (is_64) {
					uint64_t *n_value = (uint64_t*)((char*)entry + sizeof(struct symbol_table_list_entry));
					symbol_address = (void*)*n_value;
				} else {
					uint32_t *n_value = (uint32_t*)((char*)entry + sizeof(struct symbol_table_list_entry));
					symbol_address = (void*)*n_value;
				}

				table = (export_symbol*)realloc(table, sizeof(export_symbol)*(symbol_count+0x1));

				uint32_t vmaddr_slide = (uint32_t)_dyld_get_image_vmaddr_slide(image_num);
				void* address = (char*)symbol_address + vmaddr_slide;
				table[symbol_count].address = address;

				char* symbol = ((char *)str_table + entry->n_un.n_strx) + 1;
				table[symbol_count].symbol = symbol;

				symbol_count++;
			} else if (entry->n_type & N_STAB && entry->n_sect == 0x0) {
				char* symbol = ((char *)str_table + entry->n_un.n_strx) + 1;

				if (memcmp(symbol, "_ZN", 3)== 0x0) {
					table = (export_symbol*)realloc(table, sizeof(export_symbol)*(symbol_count+0x1));

					void* symbol_address = dlsym(handle, symbol);

					table[symbol_count].symbol = symbol;
					table[symbol_count].address = symbol_address;

					printf("address: 0x%x, symbol: %s\n", symbol_address, symbol);

					symbol_count++;
				}
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

void free_export_symbol_table(export_symbol* table) {
	free(table);
}


void Library::resolve() {
	if (!this->resolved && this->libPath!=null) {
		size_t symbol_count = 0;
		export_symbol *table = find_symbol_export_table(this->libPath, &symbol_count);

		const char* prefix_symbol = "_ZN";
		size_t prefix_symbol_size = strlen(prefix_symbol);

		for(int i=0; i<symbol_count; i++) {
			export_symbol *es = table + i;
            
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

