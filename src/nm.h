#ifndef NM_H
# define NM_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/mman.h>
# include <elf.h>
# include <stdbool.h>

# define DEFAULT_FILE "a.out"
# define BINARY_NAME "ft_nm"
# define SYMBOL_TABLE ".symtab"
# define STRING_TABLE ".strtab"

typedef struct s_my_symbol_32 {
    Elf32_Addr value;
    char type;
    char *name;
    unsigned char info;
} t_my_symbol_32;

typedef struct s_my_symbol_64 {
    Elf64_Addr value;
    char type;
    char *name;
    unsigned char info;
} t_my_symbol_64;

int handle_32(const Elf32_Ehdr *elf_header, unsigned long file_size, const char *file_path);
int handle_64(const Elf64_Ehdr *elf_header, unsigned long file_size, const char *file_path);

void print_my_symbols_32(t_my_symbol_32 *symbols_array, long unsigned int symbols_amount);
void print_my_symbols_64(t_my_symbol_64 *symbols_array, long unsigned int symbols_amount);

#endif
