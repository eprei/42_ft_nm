SHELL := /bin/bash
NAME = ft_nm

SRCS = src/main.c src/handle_32.c src/handle_64.c src/print.c src/validation.c
OBJ = $(SRCS:.c=.o)

SRCS_TEST = test/test_1.c test/test_2.c test/test_3.c
OBJ_TEST = $(SRCS_TEST:.c=.o)
TEST_FOLDER = test/
TEST_1 = test1
TEST_2 = test2
TEST_2_32BIT = test2_32-bit
TEST_3 = test3
LIB = /usr/lib/x86_64-linux-gnu/bfd-plugins/libdep.so

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

LIBFTPATH = ./libft

BOLD = \033[1m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFTPATH)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFTPATH) -lft -o $(NAME)

test: $(NAME) $(OBJ_TEST)
	$(CC) $(CFLAGS) $(TEST_FOLDER)test_1.o -o $(TEST_FOLDER)$(TEST_1)
	$(CC) $(CFLAGS) $(TEST_FOLDER)test_2.o -o $(TEST_FOLDER)$(TEST_2)
	$(CC) $(CFLAGS) -m32 $(TEST_FOLDER)test_2.c -o $(TEST_FOLDER)$(TEST_2_32BIT)
	$(CC) $(CFLAGS) $(TEST_FOLDER)test_3.o -o $(TEST_FOLDER)$(TEST_3)

	@echo -e "\n\t$(BOLD)Testing ft_nm against system nm$(RESET)"

	@echo -e "\n$(BOLD)(64-bit) Simple file$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)$(TEST_1)) <(./$(NAME) $(TEST_FOLDER)$(TEST_1))

	@echo -e "\n$(BOLD)(64-bit) Complex file$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)$(TEST_2)) <(./$(NAME) $(TEST_FOLDER)$(TEST_2))

	@echo -e "\n$(BOLD)(32-bit) Complex file 32-bit$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)$(TEST_2_32BIT)) <(./$(NAME) $(TEST_FOLDER)$(TEST_2_32BIT))

	@echo -e "\n$(BOLD)(64-bit) Multiple arguments$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)$(TEST_2) $(TEST_FOLDER)$(TEST_3)) <(./$(NAME) $(TEST_FOLDER)$(TEST_2) $(TEST_FOLDER)$(TEST_3))

	@echo -e "\n$(BOLD)(64-bit) Object file 1$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test_1.o) <(./$(NAME) $(TEST_FOLDER)test_1.o)

	@echo -e "\n$(BOLD)(64-bit) Object file 2$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test_2.o) <(./$(NAME) $(TEST_FOLDER)test_2.o)

	@echo -e "\n$(BOLD)(64-bit) Object file 3$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test_3.o) <(./$(NAME) $(TEST_FOLDER)test_3.o)

	@echo -e "\n$(BOLD)(64-bit) Object file 4$(RESET)"
	- diff -u <(nm src/handle_32.o) <(./$(NAME) src/handle_32.o)

	@echo -e "\n$(BOLD)(64-bit) Object file 5$(RESET)"
	- diff -u <(nm src/handle_64.o) <(./$(NAME) src/handle_64.o)

	@echo -e "\n$(BOLD)(64-bit) Object file 6$(RESET)"
	- diff -u <(nm src/main.o) <(./$(NAME) src/main.o)

	@echo -e "\n$(BOLD)(64-bit) Object file 7$(RESET)"
	- diff -u <(nm src/print.o) <(./$(NAME) src/print.o)

	@echo -e "\n$(BOLD)(64-bit) Dynamic librairy$(RESET)"
	- diff -u <(nm $(LIB)) <(./$(NAME) $(LIB))

	@echo -e "\n$(BOLD)(64-bit) Option -p : Dont sort symbols$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2 -p) <(./$(NAME) $(TEST_FOLDER)test2 -p)

	@echo -e "\n$(BOLD)(32-bit) Option -p : Dont sort symbols$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2_32-bit -p) <(./$(NAME) $(TEST_FOLDER)test2_32-bit -p)

	@echo -e "\n$(BOLD)(64-bit) Option -r : Reverse the sense of the sort$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2 -r) <(./$(NAME) $(TEST_FOLDER)test2 -r)

	@echo -e "\n$(BOLD)(32-bit) Option -r : Reverse the sense of the sort$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2_32-bit -r) <(./$(NAME) $(TEST_FOLDER)test2_32-bit -r)

	@echo -e "\n$(BOLD)(64-bit) Option -pr : Dont sort symbols and reverse the sense of the sort$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2 -pr) <(./$(NAME) $(TEST_FOLDER)test2 -pr)

	@echo -e "\n$(BOLD)(32-bit) Option -pr : Dont sort symbols and reverse the sense of the sort$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2_32-bit -pr) <(./$(NAME) $(TEST_FOLDER)test2_32-bit -pr)

	@echo -e "\n$(BOLD)(64-bit) Option -u : Display only undefined symbols$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2 -u) <(./$(NAME) $(TEST_FOLDER)test2 -u)

	@echo -e "\n$(BOLD)(32-bit) Option -u : Display only undefined symbols$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2_32-bit -u) <(./$(NAME) $(TEST_FOLDER)test2_32-bit -u)

	@echo -e "\n$(BOLD)(64-bit) Option -ur : Display only undefined symbols and reverse order$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2 -ur) <(./$(NAME) $(TEST_FOLDER)test2 -ur)

	@echo -e "\n$(BOLD)(32-bit) Option -ur : Display only undefined symbols and reverse order$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2_32-bit -ur) <(./$(NAME) $(TEST_FOLDER)test2_32-bit -ur)

	@echo -e "\n$(BOLD)(64-bit) Option -urp : Display only undefined symbols and reverse order and dont sort symbols$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2 -urp) <(./$(NAME) $(TEST_FOLDER)test2 -urp)

	@echo -e "\n$(BOLD)(32-bit) Option -urp : Display only undefined symbols and reverse order and dont sort symbols$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2_32-bit -urp) <(./$(NAME) $(TEST_FOLDER)test2_32-bit -urp)

	@echo -e "\n$(BOLD)(64-bit) Option -g : Display only external symbols$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2 -g) <(./$(NAME) $(TEST_FOLDER)test2 -g)

	@echo -e "\n$(BOLD)(32-bit) Option -g : Display only external symbols$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2_32-bit -g) <(./$(NAME) $(TEST_FOLDER)test2_32-bit -g)

	@echo -e "\n$(BOLD)(64-bit) Option -gr : Display only external symbols and reverse sort$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2 -gr) <(./$(NAME) $(TEST_FOLDER)test2 -gr)

	@echo -e "\n$(BOLD)(32-bit) Option -gr : Display only external symbols and reverse sort$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2_32-bit -gr) <(./$(NAME) $(TEST_FOLDER)test2_32-bit -gr)

	@echo -e "\n$(BOLD)(64-bit) Option -gru : Display only external symbols and reverse sort and display only undefined symbols$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2 -gru) <(./$(NAME) $(TEST_FOLDER)test2 -gru)

	@echo -e "\n$(BOLD)(32-bit) Option -gru : Display only external symbols and reverse sort and display only undefined symbols$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2_32-bit -gru) <(./$(NAME) $(TEST_FOLDER)test2_32-bit -gru)

	@echo -e "\n$(BOLD)(64-bit) Option -grup : Display only external symbols and reverse sort and display only undefined symbols and dont sort$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2 -grup) <(./$(NAME) $(TEST_FOLDER)test2 -grup)

	@echo -e "\n$(BOLD)(32-bit) Option -grup : Display only external symbols and reverse sort and display only undefined symbols and dont sort$(RESET)"
	- diff -u <(nm $(TEST_FOLDER)test2_32-bit -grup) <(./$(NAME) $(TEST_FOLDER)test2_32-bit -grup)

clean:
	rm -rf $(OBJ) $(OBJ_TEST)
	make clean -C $(LIBFTPATH)

fclean: clean
	rm -rf $(NAME) $(TEST_FOLDER)$(TEST_1) $(TEST_FOLDER)$(TEST_2) $(TEST_FOLDER)$(TEST_2_32BIT) $(TEST_FOLDER)$(TEST_3)
	make fclean -C $(LIBFTPATH)

re: fclean all

.PHONY: all clean fclean re test
