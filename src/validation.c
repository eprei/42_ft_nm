#include "nm.h"

static bool get_options(const char *str, t_opts *opts) {
    if (!str){
        return false;
    }

    for (size_t i = 0; i < ft_strlen(str); i++){
        const bool is_valid_char = str[i] == 'g' || str[i] == 'p' || str[i] == 'r' || str[i] == 'u';

        if (!is_valid_char) {
            print_invalid_option(&str[i]);
            print_usage();
            return false;
        }

        switch (str[i]) {
            case 'g':
                opts->display_only_external_symbols = true;
                break;
            case 'p':
                opts->dont_sort_symbols = true;
                break;
            case 'r':
                opts->reverse_sort = true;
                break;
            case 'u':
                opts->display_only_undefined_symbols = true;
                break;
            default: ;
        }
    }
    return true;
}

bool validate_args(const int argc, char **argv, t_opts* opts, unsigned int *number_of_commands) {
    for (int i = 1; i < argc; i++){
        if (argv[i][0] == '-') {
            if (!get_options(argv[i] + 1, opts)){
                return false;
            }
        } else {
            *number_of_commands += 1;
        }
    }

    return true;
}
