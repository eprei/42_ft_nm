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
# define MSG_ILLEGAL_OPTION "ft_nm: invalid option --"
# define MSG_USAGE "Usage: ft_nm [option(s)] [file(s)]      \n\
 List symbols in [file(s)] (a.out by default).              \n\
 The options are:                                           \n\
  -g    Display only external symbols                       \n\
  -p    Do not sort the symbols                             \n\
  -r    Reverse the sense of the sort                       \n\
  -u    Display only undefined symbols"

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

typedef struct s_opts {
    bool display_only_external_symbols;                 // -g
    bool dont_sort_symbols;                             // -p
    bool reverse_sort;                                  // -r
    bool display_only_undefined_symbols;                // -u
} t_opts;

int handle_32(const Elf32_Ehdr *elf_header, unsigned long file_size, const char *file_path, t_opts *opts);
int handle_64(const Elf64_Ehdr *elf_header, unsigned long file_size, const char *file_path, t_opts *opts);

void print_my_symbols_32(t_my_symbol_32 *symbols_array, long unsigned int symbols_amount, t_opts* opts);
void print_my_symbols_64(t_my_symbol_64 *symbols_array, long unsigned int symbols_amount, t_opts *opts);
void print_invalid_option(const char *c);
void print_usage(void);
void print_stderr_file_format_not_recognized(const char *file_path);

bool validate_args(int argc, char **argv, t_opts* opts, unsigned int *number_of_commands);

#endif
