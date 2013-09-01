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

#include <link.h>
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


/* bionic is currently only 32-bit. */
#ifdef __x86_64
    #define ElfW(type) Elf64_##type
#else
    #define ElfW(type) Elf32_##type
#endif

#define SOINFO_NAME_LEN 128

#ifdef __ANDROID__

/*
    the header part of the soinfo
 */
typedef struct {
    char name[SOINFO_NAME_LEN];
    const Elf32_Phdr* phdr;
    size_t phnum;
    Elf32_Addr entry;
    Elf32_Addr base;
    unsigned size;
} android_soinfo;

#endif // #ifdef __ANDROID__


#ifndef __arm__

int dl_iterate_callback(struct dl_phdr_info *info, size_t size, void *data) {
    int j;

    struct dl_phdr_info* tolookup = (dl_phdr_info*)data; 

    for (j = 0; j < info->dlpi_phnum; j++) {
        if (strcmp(info->dlpi_name, tolookup->dlpi_name) == 0x0) {
            tolookup->dlpi_addr = info->dlpi_addr;
            tolookup->dlpi_phdr = info->dlpi_phdr;
            tolookup->dlpi_phnum = info->dlpi_phnum;

            return j;
        }
    }
         
    return 0;
}

#endif //__arm__


void* find_lib_base_address(const char* path) {
    assert(path != NULL && "path is null");

    void *handle = dlopen(path, RTLD_LAZY);

#ifdef __USE_GNU
    const struct link_map * link_map = 0;
    const int ret = dlinfo(handle, RTLD_DI_LINKMAP, &link_map);
    return (void*)link_map->l_addr;
#endif//__USE_GNU

#ifndef __arm__
    struct dl_phdr_info to_lookup;
    to_lookup.dlpi_addr = NULL;
    to_lookup.dlpi_name = path;

    dl_iterate_phdr(dl_iterate_callback, &to_lookup);
    if (to_lookup.dlpi_addr != NULL) {
        return (void*)to_lookup.dlpi_addr;
    }
#endif

#ifdef __ANDROID__
    android_soinfo* libdl_info = (android_soinfo*)handle;
    return (void*)libdl_info->base;
#endif

    return NULL;
}

int elf_check_addr(ElfW(Ehdr)* header, const void *addr) {
    void* dlpi_addr = (void*)header;

    ElfW(Phdr)* start_phdr = (ElfW(Phdr)*)((void*)header + header->e_phoff);
    ElfW(Half) e_phnum = header->e_phnum;

    for (size_t i=0; i<e_phnum; i++) {
        ElfW(Phdr)* phdr = start_phdr + i;

        if (phdr->p_type == PT_LOAD) {
            if ((addr < phdr->p_memsz + phdr->p_vaddr + dlpi_addr) &&
                (addr >= phdr->p_vaddr + dlpi_addr)) {
                return 0;  
            }
        }
    }

    return 1;
}

ElfW(Phdr)* find_segment(ElfW(Ehdr)* header, int tag) {
    ElfW(Phdr)* start_phdr = (ElfW(Phdr)*)((void*)header + header->e_phoff);
    ElfW(Half) e_phnum = header->e_phnum;

    for (size_t i=0; i<e_phnum; i++) {
        ElfW(Phdr)* phdr = start_phdr + i;

        if (phdr->p_type == tag) {
            return phdr;
        }
    }

    return NULL;
}

ElfW(Dyn)* find_dyn(ElfW(Ehdr)* header, ElfW(Phdr)* p_seg, int tag) {
    ElfW(Dyn)* dyn = (ElfW(Dyn)*)((void*)header + p_seg->p_vaddr);

    for (; dyn->d_tag != DT_NULL; ++dyn) {
        if (dyn->d_tag == tag) {
            return dyn;
        }
    }

    return 0;
}

char* find_strtab(ElfW(Ehdr)* header) {
    void* dlpi_addr = (void*)header;

    ElfW(Phdr)* dyn_seg = find_segment(header, PT_DYNAMIC);

    if (dyn_seg) {
        ElfW(Dyn)* str_dyn = find_dyn(header, dyn_seg, DT_STRTAB);

        if (str_dyn) {
            void* str_sec_addr = (void*)str_dyn->d_un.d_ptr;

            if (elf_check_addr(header, str_sec_addr)) {
                str_sec_addr = dlpi_addr + str_dyn->d_un.d_ptr;
            }

            return (char*)str_sec_addr;
        }
    }

    return NULL;
}

ElfW(Sym)* find_sym_base(ElfW(Ehdr)* header) {
    void* dlpi_addr = (void*)header;

    ElfW(Phdr)* dyn_seg = find_segment(header, PT_DYNAMIC);
    if (dyn_seg) {
        ElfW(Dyn)* sym_dyn = find_dyn(header, dyn_seg, DT_SYMTAB);

        if (sym_dyn) {
            void* sym_sec_addr = (void*)sym_dyn->d_un.d_ptr;

            if (elf_check_addr(header, sym_sec_addr)) {
                sym_sec_addr = dlpi_addr + sym_dyn->d_un.d_ptr;
            }

            return (ElfW(Sym)*)sym_sec_addr;
        }
    }

    return NULL;
}

size_t find_symbol_count_by_dt_hash(ElfW(Ehdr)* header) {
    void* dlpi_addr = (void*)header;

    ElfW(Phdr)* dyn_seg = find_segment(header, PT_DYNAMIC);

    if (dyn_seg) {
        ElfW(Dyn)* hash_dyn = find_dyn(header, dyn_seg, DT_HASH);

        if (hash_dyn) {
            ElfW(Word)* hash = (ElfW(Word)*)(hash_dyn->d_un.d_ptr);

            if (elf_check_addr(header, hash)) {
                hash = (ElfW(Word)*)(dlpi_addr + hash_dyn->d_un.d_ptr);
            }

            return hash[1];
        } 
    }

    return 0;
}


#ifdef DT_GNU_HASH

size_t find_symbol_count_by_dt_gnu_hash(ElfW(Ehdr)* header) {
    void* dlpi_addr = (void*)header;

    Elf32_Word *buckets, *chains, *hasharr;
    ElfW(Addr) *bitmask, bitmask_word;
    Elf32_Word symbias, bitmask_nwords, bucket,
    nbuckets, bitmask_idxbits, shift;
    Elf32_Word hash, hashbit1, hashbit2;
    ElfW(Sym) *esym;

    ElfW(Phdr)* dyn_seg = find_segment(header, PT_DYNAMIC);

    if (dyn_seg) {
        ElfW(Dyn)* gnu_hash_dyn = find_dyn(header, dyn_seg, DT_GNU_HASH);

        if (gnu_hash_dyn) {
            ElfW(Word)* gnu_hash = (ElfW(Word)*)gnu_hash_dyn->d_un.d_ptr;

            if (elf_check_addr(header, gnu_hash)) {
                gnu_hash = (ElfW(Word)*)dlpi_addr + gnu_hash_dyn->d_un.d_ptr;
            }

            nbuckets = gnu_hash[0];
            symbias = gnu_hash[1];
            bitmask_nwords = gnu_hash[2]; /* must be power of two */
            bitmask_idxbits = bitmask_nwords - 1;
            shift = gnu_hash[3];

            bitmask = (ElfW(Addr) *) &gnu_hash[4];
            buckets = &gnu_hash[4 + (__ELF_NATIVE_CLASS / 32) * bitmask_nwords];
            chains = &buckets[nbuckets] - symbias;

            unsigned int last_sym = 0;

            for (size_t index = 0; index < nbuckets; index++) {
                if (buckets[index] > last_sym) {
                    last_sym = buckets[index]; 
                }
            }

            last_sym++;

            while (!(chains[last_sym] & 1)) {
                last_sym++;
            }

            return last_sym;
        } 
    }

    return 0;
}

#endif//DT_GNU_HASH


size_t find_symbol_count(ElfW(Ehdr)* header) {
    size_t size = find_symbol_count_by_dt_hash(header);

#ifdef DT_GNU_HASH
    if (size == 0) {
       size = find_symbol_count_by_dt_gnu_hash(header);
    }
#endif//DT_GNU_HASH

    return size;   
}

/* e_ident */
#define __IS_ELF(ehdr) ((ehdr).e_ident[EI_MAG0] == ELFMAG0 && \
                      (ehdr).e_ident[EI_MAG1] == ELFMAG1 && \
                      (ehdr).e_ident[EI_MAG2] == ELFMAG2 && \
                      (ehdr).e_ident[EI_MAG3] == ELFMAG3)

export_symbol* find_symbol_export_table(const char* path, size_t* addr_export_table_size) {
    void *handle = dlopen(path, RTLD_LAZY);

    void *dlpi_addr = find_lib_base_address(path);
    if (dlpi_addr == NULL) {
        fprintf(stderr, "Failed to get module base addresses\n");
        return NULL;
    }

    ElfW(Ehdr)* header = (ElfW(Ehdr)*)dlpi_addr;
    if (!__IS_ELF(*header)) {
        fprintf(stderr, "Invalidate ELF file\n");
        return NULL;
    }   

    char* strtab = find_strtab(header);

    size_t sym_max_count = find_symbol_count(header);
    ElfW(Sym)* sym_base = find_sym_base(header);

    size_t symbol_count = 0;
    export_symbol* table = (export_symbol *)calloc(0x1, sizeof(export_symbol));

    for (size_t i=0; i<sym_max_count; i++) {
        ElfW(Sym)* sym = sym_base + i;

        char* symbol = &strtab[sym->st_name];

        void* symbol_address = dlsym(handle, symbol);

        if (strlen(symbol) > 0 && symbol_address) {
            table = (export_symbol*)realloc(table, sizeof(export_symbol)*(symbol_count+0x1));

            table[symbol_count].address = symbol_address;
            table[symbol_count].symbol = symbol;

            //printf("address: 0x%x, symbol: %s\n", symbol_address, symbol);
            symbol_count++;
        }
    }

    *addr_export_table_size = symbol_count;

    return table;
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

        free(table);

        this->resolved = dg_true;
    }
}
