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

#include <dragon/lang/internal/Library_Posix.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include <dlfcn.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

Import dragon::lang::internal;

//-------------------------------------------------------------------------------------
//Blow Code from  https://github.com/shoumikhin/ELF-Hook.git
//
//Method of patching the import table in ELF shared libraries.
//Read more info at CodeProject (http://www.codeproject.com/KB/library/elf-redirect.aspx).
//

//rename standart types for convenience
#ifdef __x86_64
    #define Elf_Ehdr Elf64_Ehdr
    #define Elf_Shdr Elf64_Shdr
    #define Elf_Sym Elf64_Sym
    #define Elf_Rel Elf64_Rela
    #define ELF_R_SYM ELF64_R_SYM
    #define REL_DYN ".rela.dyn"
    #define REL_PLT ".rela.plt"
#else
    #define Elf_Ehdr Elf32_Ehdr
    #define Elf_Shdr Elf32_Shdr
    #define Elf_Sym Elf32_Sym
    #define Elf_Rel Elf32_Rel
    #define ELF_R_SYM ELF32_R_SYM
    #define REL_DYN ".rel.dyn"
    #define REL_PLT ".rel.plt"
#endif


//==================================================================================================
static int read_header(int d, Elf_Ehdr **header)
{
    *header = (Elf_Ehdr *)malloc(sizeof(Elf_Ehdr));

    if (lseek(d, 0, SEEK_SET) < 0)
    {
        free(*header);

        return errno;
    }

    if (read(d, *header, sizeof(Elf_Ehdr)) <= 0)
    {
        free(*header);

        return errno = EINVAL;
    }

    return 0;
}

//--------------------------------------------------------------------------------------------------
static int read_section_table(int d, Elf_Ehdr const *header, Elf_Shdr **table)
{
    size_t size;

    if (NULL == header)
        return EINVAL;

    size = header->e_shnum * sizeof(Elf_Shdr);
    *table = (Elf_Shdr *)malloc(size);

    if (lseek(d, header->e_shoff, SEEK_SET) < 0)
    {
        free(*table);

        return errno;
    }

    if (read(d, *table, size) <= 0)
    {
        free(*table);

        return errno = EINVAL;
    }

    return 0;
}

//--------------------------------------------------------------------------------------------------
static int read_string_table(int d, Elf_Shdr const *section, char const **strings)
{
    if (NULL == section)
        return EINVAL;

    *strings = (char const *)malloc(section->sh_size);

    if (lseek(d, section->sh_offset, SEEK_SET) < 0)
    {
        free((void *)*strings);

        return errno;
    }

    if (read(d, (char *)*strings, section->sh_size) <= 0)
    {
        free((void *)*strings);

        return errno = EINVAL;
    }

    return 0;
}

//--------------------------------------------------------------------------------------------------
static int read_symbol_table(int d, Elf_Shdr const *section, Elf_Sym **table)
{
    if (NULL == section)
        return EINVAL;

    *table = (Elf_Sym *)malloc(section->sh_size);

    if (lseek(d, section->sh_offset, SEEK_SET) < 0)
    {
        free(*table);

        return errno;
    }

    if (read(d, *table, section->sh_size) <= 0)
    {
        free(*table);

        return errno = EINVAL;
    }

    return 0;
}

//--------------------------------------------------------------------------------------------------
static int read_relocation_table(int d, Elf_Shdr const *section, Elf_Rel **table)
{
    if (NULL == section)
        return EINVAL;

    *table = (Elf_Rel *)malloc(section->sh_size);

    if (lseek(d, section->sh_offset, SEEK_SET) < 0)
    {
        free(*table);

        return errno;
    }

    if (read(d, *table, section->sh_size) <= 0)
    {
        free(*table);

        return errno = EINVAL;
    }

    return 0;
}

//--------------------------------------------------------------------------------------------------
static int section_by_index(int d, size_t const index, Elf_Shdr **section)
{
    Elf_Ehdr *header = NULL;
    Elf_Shdr *sections = NULL;

    *section = NULL;

    if (
        read_header(d, &header) ||
        read_section_table(d, header, &sections)
    ) {
        return errno;
    }

    if (index < header->e_shnum)
    {
        *section = (Elf_Shdr *)malloc(sizeof(Elf_Shdr));

        if (NULL == *section)
        {
            free(header);
            free(sections);

            return errno;
        }

        memcpy(*section, sections + index, sizeof(Elf_Shdr));
    }
    else
        return EINVAL;

    free(header);
    free(sections);

    return 0;
}

//--------------------------------------------------------------------------------------------------
static int section_by_type(int d, size_t const section_type, Elf_Shdr **section)
{
    Elf_Ehdr *header = NULL;
    Elf_Shdr *sections = NULL;
    size_t i;

    *section = NULL;

    if (
        read_header(d, &header) ||
        read_section_table(d, header, &sections)
        )
        return errno;

    for (i = 0; i < header->e_shnum; ++i)
        if (section_type == sections[i].sh_type)
        {
            *section = (Elf_Shdr *)malloc(sizeof(Elf_Shdr));

            if (NULL == *section)
            {
                free(header);
                free(sections);

                return errno;
            }

            memcpy(*section, sections + i, sizeof(Elf_Shdr));

            break;
        }

    free(header);
    free(sections);

    return 0;
}

//--------------------------------------------------------------------------------------------------
static int section_by_name(int d, char const *section_name, Elf_Shdr **section)
{
    Elf_Ehdr *header = NULL;
    Elf_Shdr *sections = NULL;
    char const *strings = NULL;
    size_t i;

    *section = NULL;

    if (
        read_header(d, &header) ||
        read_section_table(d, header, &sections) ||
        read_string_table(d, &sections[header->e_shstrndx], &strings)
        )
        return errno;

    for (i = 0; i < header->e_shnum; ++i)
        if (!strcmp(section_name, &strings[sections[i].sh_name]))
        {
            *section = (Elf_Shdr *)malloc(sizeof(Elf_Shdr));

            if (NULL == *section)
            {
                free(header);
                free(sections);
                free((void *)strings);

                return errno;
            }

            memcpy(*section, sections + i, sizeof(Elf_Shdr));

            break;
        }

    free(header);
    free(sections);
    free((void *)strings);

    return 0;
}

//--------------------------------------------------------------------------------------------------
static int symbol_by_name(int d, Elf_Shdr *section, char const *name, Elf_Sym **symbol, size_t *index)
{
    Elf_Shdr *strings_section = NULL;
    char const *strings = NULL;
    Elf_Sym *symbols = NULL;
    size_t i, amount;

    *symbol = NULL;
    *index = 0;

    if (
        section_by_index(d, section->sh_link, &strings_section) ||
        read_string_table(d, strings_section, &strings) ||
        read_symbol_table(d, section, &symbols)
        )
        return errno;

    amount = section->sh_size / sizeof(Elf_Sym);

    for (i = 0; i < amount; ++i)
        if (!strcmp(name, &strings[symbols[i].st_name]))
        {
            *symbol = (Elf_Sym *)malloc(sizeof(Elf_Sym));

            if (NULL == *symbol)
            {
                free(strings_section);
                free((void *)strings);
                free(symbols);

                return errno;
            }

            memcpy(*symbol, symbols + i, sizeof(Elf_Sym));
            *index = i;

            break;
        }

    free(strings_section);
    free((void *)strings);
    free(symbols);

    return 0;
}

//--------------------------------------------------------------------------------------------------
int get_module_base_address(char const *module_filename, void *handle, void **base)
{
    int descriptor;  //file descriptor of shared module
    Elf_Shdr *dynsym = NULL, *strings_section = NULL;
    char const *strings = NULL;
    Elf_Sym *symbols = NULL;
    size_t i, amount;
    Elf_Sym *found = NULL;

    *base = NULL;

    descriptor = open(module_filename, O_RDONLY);

    if (descriptor < 0)
        return errno;

    if (section_by_type(descriptor, SHT_DYNSYM, &dynsym) ||  //get ".dynsym" section
        section_by_index(descriptor, dynsym->sh_link, &strings_section) ||
        read_string_table(descriptor, strings_section, &strings) ||
        read_symbol_table(descriptor, dynsym, &symbols))
    {
        free(strings_section);
        free((void *)strings);
        free(symbols);
        free(dynsym);
        close(descriptor);

        return errno;
    }

    amount = dynsym->sh_size / sizeof(Elf_Sym);

    /* Trick to get the module base address in a portable way:
     *   Find the first GLOBAL or WEAK symbol in the symbol table,
     *   look this up with dlsym, then return the difference as the base address
     */
    for (i = 0; i < amount; ++i)
    {
        switch(ELF32_ST_BIND(symbols[i].st_info)) {
        case STB_GLOBAL:
        case STB_WEAK:
            found = &symbols[i];
            break;
        default: // Not interested in this symbol
            break;
        }
    }

    if(found != NULL)
    {
        const char *name = &strings[found->st_name];
        void *sym = dlsym(handle, name); 
        if(sym != NULL)
            *base = (void*)((size_t)sym - found->st_value);
    }

    free(strings_section);
    free((void *)strings);
    free(symbols);
    free(dynsym);
    close(descriptor);

    return *base == NULL;
}
//--------------------------------------------------------------------------------------------------


// find the elf file export table

size_t find_symbol_offset(void* module_address, Elf_Shdr *rel_plt, Elf_Shdr *rel_dyn, size_t name_index) {
    Elf_Rel* rel_plt_table = (Elf_Rel *)(((size_t)module_address) + rel_plt->sh_addr);  //init the ".rel.plt" array
    size_t rel_plt_amount = rel_plt->sh_size / sizeof(Elf_Rel);  //and get its size

    Elf_Rel* rel_dyn_table = (Elf_Rel *)(((size_t)module_address) + rel_dyn->sh_addr);  //init the ".rel.dyn" array
    size_t rel_dyn_amount = rel_dyn->sh_size / sizeof(Elf_Rel);  //and get its size

    size_t offset = -1;

    bool found = false;

    for (int i = 0; i < rel_plt_amount; ++i) { //lookup the ".rel.plt" table
        if (ELF_R_SYM(rel_plt_table[i].r_info) == name_index) { //if we found the symbol to substitute in ".rel.plt"
            offset = rel_plt_table[i].r_offset;  //save the original function address
            found = true;
            break;  //the target symbol appears in ".rel.plt" only once
        }
    }

    if (!found) {
        for (int i = 0; i < rel_dyn_amount; ++i) { //lookup the ".rel.dyn" table
            if (ELF_R_SYM(rel_dyn_table[i].r_info) == name_index) { //if we found the symbol to substitute in ".rel.dyn"
                offset =  rel_dyn_table[i].r_offset;  //get the relocation address (address of a relative CALL (0xE8) instruction's argument)
                found = true;
                break;  //the target symbol appears in ".rel.plt" only once
            }
        }
    }

    return offset;
}

void* find_lib_base_address(const char* path) {
    assert(path != NULL && "path is null");

    void *handle = dlopen(path, RTLD_LAZY);
    void *module_address = NULL;

    if(get_module_base_address(path, handle, &module_address)) {
        return NULL;
    }

    dlclose(handle);

    return module_address;
}

export_symbol* find_symbol_export_table(const char* path, size_t* addr_export_table_size) {
	void *handle = dlopen(path, RTLD_LAZY);

    void *module_address = find_lib_base_address(path);
    if (module_address == NULL) {
        fprintf(stderr, "Failed to get module base addresses\n");
        return NULL;
    }

    int descriptor = open(path, O_RDONLY);
    if (descriptor < 0) {
        fprintf(stderr, "Failed to open the lib file\n");
        return NULL;
    }

    Elf_Ehdr* header = (Elf_Ehdr*)module_address;
    if (memcmp(header->e_ident, ELFMAG, SELFMAG) != 0x0) {
        fprintf(stderr, "Invalidate ELF file\n");
    	return NULL;
    }

    Elf_Shdr *rel_plt = NULL;  // ".rel.plt" section header
    Elf_Shdr *rel_dyn = NULL;  // ".rel.dyn" section header
    Elf_Shdr *dynsym = NULL; // ".dynsym" section header
    Elf_Shdr *strings_section = NULL;
    const char *strings = NULL;
    Elf_Sym *symbols = NULL;


    if (section_by_name(descriptor, REL_PLT, &rel_plt) ||  //get ".rel.plt" (for 32-bit) or ".rela.plt" (for 64-bit) section
        section_by_name(descriptor, REL_DYN, &rel_dyn) || //get ".rel.dyn" (for 32-bit) or ".rela.dyn" (for 64-bit) section

        section_by_type(descriptor, SHT_DYNSYM, &dynsym) ||
        section_by_index(descriptor, dynsym->sh_link, &strings_section) ||
        read_string_table(descriptor, strings_section, &strings) ||
        read_symbol_table(descriptor, dynsym, &symbols)) {

        SafeFree(rel_plt);
        SafeFree(rel_dyn);

        SafeFree(dynsym);
        SafeFree(strings_section);
        free((void *)strings);
        SafeFree(symbols);

        close(descriptor);

        return NULL;
    }

    void* symbol_address = NULL;
    char* symbol = NULL;

    size_t amount = dynsym->sh_size / sizeof(Elf_Sym);
    size_t symbol_count = 0x0;

    export_symbol* table = (export_symbol *)calloc(0x1, sizeof(export_symbol));

    for (size_t i = 0; i < amount; ++i) {
        Elf_Sym* elf_sym = &symbols[i];

        symbol = const_cast<char*>(&strings[elf_sym->st_name]);
        void* symbol_address_1 =  module_address + find_symbol_offset(module_address, rel_plt, rel_dyn, i);
        void* symbol_address_2 =  dlsym(handle, symbol);

        if (strlen(symbol) > 0) {
            table = (export_symbol*)realloc(table, sizeof(export_symbol)*(symbol_count+0x1));

            table[symbol_count].address = symbol_address_2;
            table[symbol_count].symbol = symbol;

            symbol_count++;
        }
    }


    SafeFree(rel_plt);
    SafeFree(rel_dyn);

    SafeFree(dynsym);
    SafeFree(strings_section);
    //free((void *)strings);
    SafeFree(symbols);

    close(descriptor);

	*addr_export_table_size = symbol_count;
	return table;
}

void free_export_symbol_table(export_symbol* table) {
    free(table);
}

void Library::resolve() {
	if (!this->resolved) {
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