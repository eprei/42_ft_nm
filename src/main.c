#include "nm.h"

int main(int argc, char **argv) {

    if (argc == 1) {
        nm(DEFAULT_FILE);
    }

    for (int i = 1; i < argc; i++) {
        nm(argv[i]);
    }

    return 0;
}

void nm(char *file_path) {
    struct stat sb;
    char *file_in_memory;
    int fd;

    fd = open_file(file_path);
    if (fd < 0) {
        return;
    }

    if (fstat(fd, &sb) == -1) {
        perror("Couldn't get file size\n");
        return;
    }

    file_in_memory = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (file_in_memory == MAP_FAILED) {
        perror("Couldn't map file to memory\n");
        close(fd);
        return;
    }

    // TODO : Implement the actual nm functionality here
    // Find binary type reading the magic numbers at the start of the file
    // Then parse the file accordingly to extract symbols
    // ELF Header → Section Headers → serach .symtab and .strtab → read symbols

    // For now, just printing the file content
    for (int i = 0; i < sb.st_size; i++) {
        ft_printf("%c", file_in_memory[i]);
    }

    munmap(file_in_memory, sb.st_size);
    close(fd);
}

int open_file(char * file_path) {
    const int fd = open(file_path, O_RDONLY);

    if (fd < 0) {
        ft_printf("%s: '%s': %s\n", BINARY_NAME, file_path, strerror(errno));
    }

    return fd;
}
