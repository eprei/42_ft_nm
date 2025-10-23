SHELL := /bin/bash
NAME = ft_nm

SRCS = src/main.c
OBJ = $(SRCS:.c=.o)

SRCS_TEST = test/test_1.c test/test_2.c test/test_3.c
OBJ_TEST = $(SRCS_TEST:.c=.o)
TEST_FOLDER = test/
TEST_1 = test1
TEST_2 = test2
TEST_2_32BIT = test2_32-bit
TEST_3 = test3
LIB = /usr/lib/x86_64-linux-gnu/bfd-plugins/libdep.so
UNIVERSAL_BIN = /usr/bin/python3

CC = gcc
CFLAGS = -Wall -Wextra -Werror

BOLD = \033[1m
RESET = \033[0m
GREEN = \033[0;32m
RED = \033[0;31m

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

test: $(NAME) $(OBJ_TEST)
	$(CC) $(TEST_FOLDER)test_1.o -o $(TEST_FOLDER)$(TEST_1)
	$(CC) $(TEST_FOLDER)test_2.o -o $(TEST_FOLDER)$(TEST_2)
	$(CC) -m32 $(TEST_FOLDER)test_2.c -o $(TEST_FOLDER)$(TEST_2_32BIT)
	$(CC) $(TEST_FOLDER)test_3.o -o $(TEST_FOLDER)$(TEST_3)

	@echo -e "\n\t$(BOLD)Testing ft_nm against system nm$(RESET)"

	@echo -e "\n$(BOLD)Simple file$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)$(TEST_1)) <(./$(NAME) $(TEST_FOLDER)$(TEST_1))

	@echo -e "\n$(BOLD)Complex file$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)$(TEST_2)) <(./$(NAME) $(TEST_FOLDER)$(TEST_2))

	@echo -e "\n$(BOLD)Complex file 32-bit$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)$(TEST_2_32BIT)) <(./$(NAME) $(TEST_FOLDER)$(TEST_2_32BIT))

	@echo -e "\n$(BOLD)Multiple arguments$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)$(TEST_2) $(TEST_FOLDER)$(TEST_3)) <(./$(NAME) $(TEST_FOLDER)$(TEST_2) $(TEST_FOLDER)$(TEST_3))

	@echo -e "\n$(BOLD)Object file$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test_1.o) <(./$(NAME) $(TEST_FOLDER)test_1.o)

	@echo -e "\n$(BOLD)Dynamic librairy$(RESET)"
	- diff -u <(nm $(LIB)) <(./$(NAME) $(LIB))

	@echo -e "\n$(BOLD)Universal Binary$(RESET)"
	- diff -u <(nm $(UNIVERSAL_BIN)) <(./$(NAME) $(UNIVERSAL_BIN))

clean:
	rm -rf $(OBJ) $(OBJ_TEST)

fclean: clean
	rm -rf $(NAME) $(TEST_FOLDER)$(TEST_1) $(TEST_FOLDER)$(TEST_2) $(TEST_FOLDER)$(TEST_2_32BIT) $(TEST_FOLDER)$(TEST_3)

re: fclean all

.PHONY: all clean fclean re test
