cmake_minimum_required(VERSION 3.22.1)
project(42_ft_nm C)

set(CMAKE_C_STANDARD 99)

set(LIBFT_DIR ${CMAKE_SOURCE_DIR}/libft)

add_custom_target(
        libft_build
        COMMAND make -C ${LIBFT_DIR}
        COMMENT "Building libft..."
)

add_executable(42_ft_nm src/main.c
        src/nm.h
        src/print.c
        src/handle_64.c
        src/handle_32.c)

add_dependencies(42_ft_nm libft_build)

target_include_directories(42_ft_nm PRIVATE $(LIBFT_DIR))

target_link_libraries(42_ft_nm ${LIBFT_DIR}/libft.a)