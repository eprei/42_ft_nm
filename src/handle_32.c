#include "nm.h"

static char decode_section_type (const Elf32_Xword *section_flags, const Elf32_Word *section_type){
    if (*section_flags & SHF_EXECINSTR) {
        return 't';
    }

    if (*section_type == SHT_NOBITS && *section_flags & SHF_ALLOC){
        return 'b';
    }

    if (*section_flags & SHF_WRITE && *section_flags & SHF_ALLOC){
        return 'd';
    }

    if (*section_flags & SHF_ALLOC){
            return 'r';
    }

    if (*section_type == SHT_NOBITS){
        return 'b';
    }

    if (*section_type == SHT_PROGBITS && !(*section_flags & SHF_ALLOC)) {
        return 'N';
    }

    return '?';
}

static char decode_symbol_type(const Elf32_Sym *symbol, const Elf32_Shdr* section_of_symbol) {
    const unsigned char symbol_bind = ELF32_ST_BIND(symbol->st_info);
    const unsigned char symbol_type = ELF32_ST_TYPE(symbol->st_info);
    const Elf32_Word	section_type = section_of_symbol == NULL ? 0 : section_of_symbol->sh_type;
    const Elf32_Xword	section_flags = section_of_symbol == NULL ? 0 : section_of_symbol->sh_flags;
    char type;

    if (symbol == NULL || section_of_symbol == NULL){
        return '?';
    }

    if (symbol_type == STT_COMMON){
        return 'C';
    }

    if (symbol->st_shndx == SHN_UNDEF){
        if (symbol_bind == STB_WEAK){
            if (symbol_type == STT_OBJECT){
                return 'v';
            }
            return 'w';
        }
        return 'U';
    }

    if (symbol_type == STT_GNU_IFUNC){ return 'i'; }
    if (symbol_bind == STB_WEAK){
        if (symbol_type == STT_OBJECT){
            return 'V';
        }
        return 'W';
    }
    if (symbol_bind == STB_GNU_UNIQUE){ return 'u'; }
    if (!(symbol_bind == STB_LOCAL || symbol_bind == STB_GLOBAL)){ return '?'; }
    if (symbol_type == STT_FILE){ return 'F'; }
    if (symbol_type == STT_TLS ){ return 'T'; }

    if (symbol->st_shndx == SHN_ABS){
        type = 'a';
    } else {
        type = decode_section_type(&section_flags, &section_type);
    }

    if (symbol_bind == STB_GLOBAL){ type =  ft_toupper(type); }

    return type;
}

static void fill_my_symbol(const Elf32_Sym *symbol, t_my_symbol_32 *new_symbol, const Elf32_Shdr* section_of_symbol, char *name){
    new_symbol->value = symbol->st_value;
    new_symbol->name = name;
    new_symbol->type = decode_symbol_type(symbol, section_of_symbol);
    new_symbol->info = symbol->st_info;
}

static void swap_symbols(t_my_symbol_32 *first, t_my_symbol_32 *second) {
    t_my_symbol_32 tmp;

    tmp.value = first->value;
    tmp.type = first->type;
    tmp.name = first->name;
    tmp.info = first->info;

    first->value = second->value;
    first->type = second->type;
    first->name = second->name;
    first->info = second->info;

    second->value = tmp.value;
    second->type = tmp.type;
    second->name = tmp.name;
    second->info = tmp.info;
}

static void sort_my_symbols(t_my_symbol_32 *symbols_array, long unsigned int symbols_amount) {
    bool is_swapped = true;
    while (is_swapped){
        is_swapped = false;

        for (long unsigned int i = 0; i < symbols_amount - 1; i++) {
            if (ft_strcmp(symbols_array[i].name, symbols_array[i+1].name) > 0) {
                swap_symbols(&symbols_array[i], &symbols_array[i+1]);
                is_swapped = true;
            }
        }
    }
}

static Elf32_Shdr *get_section(const Elf32_Ehdr* elf_header, Elf32_Shdr* section_header, const char *table){
    const int shstrtab_index = elf_header->e_shstrndx;
    Elf32_Shdr *shstrtab_hdr = &section_header[shstrtab_index];
    char *shstrtab = (char *) elf_header + shstrtab_hdr->sh_offset;
    Elf32_Shdr *section = NULL;

    for (int i = 0; i < elf_header->e_shnum; i++) {
        const unsigned int name_index = section_header[i].sh_name;
        const char *section_name = shstrtab + name_index;
        section = ft_strncmp(section_name, table, ft_strlen(table)) == 0 ? &section_header[i] : section;
    }
    return section;
}

int handle_32(const Elf32_Ehdr *elf_header, const unsigned long file_size, const char *file_path) {
    Elf32_Shdr *symtab_section, *strtab_section, *section_header;
    Elf32_Sym *symbols_array;
    unsigned int symbols_amount;
    t_my_symbol_32 *my_symbols_array;

    if (elf_header->e_shoff == 0 || elf_header->e_shnum == 0) {
        ft_printf("%s: %s: no symbols\n", BINARY_NAME, file_path);
        return EXIT_FAILURE;
    }

    if (elf_header->e_shoff > file_size) {
        ft_printf("%s: %s: file too short\n", BINARY_NAME, file_path);
        return EXIT_FAILURE;
    }

    if (elf_header->e_shoff != 0 && elf_header->e_shnum == SHN_UNDEF) {
        ft_printf("%s: %s: file format not recognized\n", BINARY_NAME, file_path);
        return EXIT_FAILURE;
    }

    section_header = (Elf32_Shdr *) ((char *)elf_header + elf_header->e_shoff);

    symtab_section = get_section(elf_header, section_header, SYMBOL_TABLE);
    if (!symtab_section){
        ft_printf("%s: %s: no symbols\n", BINARY_NAME, file_path);
        return EXIT_FAILURE;
    }

    strtab_section = get_section(elf_header, section_header, STRING_TABLE);
    if (!strtab_section){
        ft_printf("%s: %s: no string table\n", BINARY_NAME, file_path);
        return EXIT_FAILURE;
    }

    symbols_amount = symtab_section->sh_size / symtab_section->sh_entsize;
    my_symbols_array = calloc(sizeof(t_my_symbol_32), symbols_amount);
    if (my_symbols_array == NULL) {
        ft_printf("Error in handle_32: calloc error\n");
        return EXIT_FAILURE;
    }

    // Fill all my symbols
    symbols_array = (Elf32_Sym *)((char *) elf_header + symtab_section->sh_offset);
    char *strtab = (char *) elf_header + strtab_section->sh_offset + 1;
    for (unsigned int i = 0; i < symbols_amount; i++) {
        const Elf32_Sym *symbol = (Elf32_Sym *) (char *) &symbols_array[i];
        const Elf32_Shdr* section_of_symbol = symbol->st_shndx >= elf_header->e_shnum ? 0 : &section_header[symbol->st_shndx];
        char *name = strtab + symbol->st_name - 1;

        fill_my_symbol(symbol, &my_symbols_array[i], section_of_symbol, name);
    }

    sort_my_symbols(my_symbols_array, symbols_amount);
    print_my_symbols_32(my_symbols_array, symbols_amount);
    free(my_symbols_array);

    return EXIT_SUCCESS;
}
