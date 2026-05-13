#include "nm.h"

static void print_ulint_in_hex(const unsigned long int n)
{
    char	*str;
    str = "0123456789abcdef";

    if (n <= 15){
        write(1, &str[n], 1);
    } else {
        print_ulint_in_hex(n / 16);
        print_ulint_in_hex(n % 16);
    }
}

static int ulint_in_hex_len(const unsigned long int n)
{
    int count = 0;

    if (n <= 15){
        count += 1;
    } else {
        count += ulint_in_hex_len(n / 16);
        count += ulint_in_hex_len(n % 16);
    }

    return count;
}

static int is_printable_64(const t_my_symbol_64 current_symbol) {
    return current_symbol.name != 0
        && (current_symbol.name[0] != '\0' || (current_symbol.type == 'N' && current_symbol.value != 0))
        && current_symbol.name[0] != '.'
        && ELF64_ST_TYPE(current_symbol.info) != STT_FILE;
}

static int is_printable_32(const t_my_symbol_32 current_symbol) {
    return current_symbol.name != 0
        && (current_symbol.name[0] != '\0' || (current_symbol.type == 'N' && current_symbol.value != 0))
        && current_symbol.name[0] != '.'
        && ELF64_ST_TYPE(current_symbol.info) != STT_FILE;
}

void print_my_symbols_64(t_my_symbol_64 *symbols_array, const long unsigned int symbols_amount, t_opts* opts) {
    if (!symbols_array) {
        return;
    }

    for (long unsigned int i = 0; i < symbols_amount; i++) {
        if (opts->display_only_undefined_symbols && symbols_array[i].type != 'U' && symbols_array[i].type != 'w' ) {
            continue;
        }

        if (opts->display_only_external_symbols && symbols_array[i].type != ft_toupper(symbols_array[i].type) && symbols_array[i].type != 'w') {
            continue;
        }

        if (is_printable_64(symbols_array[i])) {
            if (symbols_array[i].value == 0 && (symbols_array[i].type == 'U' || symbols_array[i].type == 'w' || symbols_array[i].type == 'v')) {
                write(1, "                ", 16);
            } else {
            for (int j = 0; j < 16 - ulint_in_hex_len(symbols_array[i].value) ; j++) {
                write(1, "0", 1);
                }
                print_ulint_in_hex(symbols_array[i].value);
                }
                write(1, " ", 1);
                write(1, &symbols_array[i].type, 1);
                write(1, " ", 1);
                write(1, symbols_array[i].name, ft_strlen(symbols_array[i].name));
                write(1, "\n", 1);
        }
    }
}

void print_my_symbols_32(t_my_symbol_32 *symbols_array, const long unsigned int symbols_amount, t_opts* opts) {
    if (!symbols_array) {
        return;
    }

    for (long unsigned int i = 0; i < symbols_amount; i++) {
        if (opts->display_only_undefined_symbols && symbols_array[i].type != 'U' && symbols_array[i].type != 'w' ) {
            continue;
        }

        if (opts->display_only_external_symbols && symbols_array[i].type != ft_toupper(symbols_array[i].type) && symbols_array[i].type != 'w') {
            continue;
        }

        if (is_printable_32(symbols_array[i])) {
            if (symbols_array[i].value == 0 && (symbols_array[i].type == 'U' || symbols_array[i].type == 'w' || symbols_array[i].type == 'v')) {
                write(1, "                ", 8);
            } else {
                for (int j = 0; j < 8 - ulint_in_hex_len(symbols_array[i].value) ; j++) {
                    write(1, "0", 1);
                }
                print_ulint_in_hex(symbols_array[i].value);
            }
            write(1, " ", 1);
            write(1, &symbols_array[i].type, 1);
            write(1, " ", 1);
            write(1, symbols_array[i].name, ft_strlen(symbols_array[i].name));
            write(1, "\n", 1);
        }
    }
}

void print_invalid_option(const char *c) {
    write(STDERR_FILENO, MSG_ILLEGAL_OPTION, ft_strlen(MSG_ILLEGAL_OPTION));
    write(STDERR_FILENO, " '", 2);
    write(STDERR_FILENO, c, 1);
    write(STDERR_FILENO, "'\n", 2);
}

void print_usage(void){
    write(STDOUT_FILENO, MSG_USAGE, ft_strlen(MSG_USAGE));
    write(STDOUT_FILENO, "\n", 1);
}
