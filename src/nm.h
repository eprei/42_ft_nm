#ifndef NM_H
# define NM_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/mman.h>

# define DEFAULT_FILE "a.out"
# define BINARY_NAME "ft_nm"

void nm(char *file_path);
int open_file(char * file_path);

#endif
