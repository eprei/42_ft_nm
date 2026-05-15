#include "nm.h"

static int open_file(char * file_path) {
    const int fd = open(file_path, O_RDONLY);

    if (fd < 0) {
        ft_printf("%s: %s: %s\n", BINARY_NAME, file_path, strerror(errno));
    }

    return fd;
}

static bool check_elf(char* file_path, const char* file){
    if (file[EI_MAG0] != ELFMAG0 &&
        file[EI_MAG1] != ELFMAG1 &&
        file[EI_MAG2] != ELFMAG2 &&
        file[EI_MAG3] != ELFMAG3) {
        ft_printf("%s: %s: file format not recognized\n", BINARY_NAME, file_path);
        return false;
    }
    return true;
}

static int ft_nm(char *file_path, t_opts *opts) {
    struct stat buf;
    char *file;
    int fd, ret;

    fd = open_file(file_path);
    if (fd < 0) {
        return EXIT_FAILURE;
    }

    if (fstat(fd, &buf) == -1) {
        perror("fstat");
        return EXIT_FAILURE;
    }

    file = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (file == MAP_FAILED) {
        perror("mmap");
        return EXIT_FAILURE;
    }

    if (!check_elf(file_path, file)){
        return EXIT_FAILURE;
    }

    switch (file[EI_CLASS]) {
        case ELFCLASS32:
            ret = handle_32((Elf32_Ehdr *) file, buf.st_size, file_path, opts);
            break;
        case ELFCLASS64:
            ret = handle_64((Elf64_Ehdr *) file, buf.st_size, file_path, opts);
            break;
        default:
            ft_printf("%s: %s: This class is invalid\n", BINARY_NAME, file_path);
            ret = EXIT_FAILURE;
    }

    if (munmap(file, buf.st_size) < 0){
        perror("munmap");
        return EXIT_FAILURE;
    }

    return ret;
}

int main(const int argc, char **argv) {
    int exit_status = EXIT_SUCCESS;
    unsigned int number_of_commands = 0;
    t_opts opts = {0};

    if (!validate_args(argc, argv, &opts, &number_of_commands)){
        return EXIT_FAILURE;
    }

    if (number_of_commands == 0) {
        exit_status = ft_nm(DEFAULT_FILE, &opts);
    } else {
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] == '-') {
                continue;
            }

            if (number_of_commands > 1) {
                ft_printf("\n%s:\n", argv[i]);
            }
            const int ret_nm = ft_nm(argv[i], &opts);
            exit_status = ret_nm > exit_status ? ret_nm : exit_status;
        }
    }
    return exit_status;
}
