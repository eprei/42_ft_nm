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

void print_my_symbols_64(t_my_symbol_64 *symbols_array, const long unsigned int symbols_amount) {
    if (!symbols_array) {
        return;
    }

    for (long unsigned int i = 0; i < symbols_amount; i++) {
        if (is_printable_64(symbols_array[i])) {
            if (symbols_array[i].value == 0 && symbols_array[i].type != 'T') {
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

void print_my_symbols_32(t_my_symbol_32 *symbols_array, const long unsigned int symbols_amount) {
    if (!symbols_array) {
        return;
    }

    for (long unsigned int i = 0; i < symbols_amount; i++) {
        if (is_printable_32(symbols_array[i])) {
            if (symbols_array[i].value == 0 && symbols_array[i].type != 'T') {
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
