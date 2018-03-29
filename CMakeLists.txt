cmake_minimum_required(VERSION 3.10)

project(cpp-playground)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_compile_options(
        -Wall
        -Wextra
        -Wstrict-prototypes
        -Wmissing-prototypes
        -Wmissing-declarations
        -Wunused-macros
        -O3
        -flto)

add_subdirectory(constructors)
add_subdirectory(copy-elision)
add_subdirectory(delete-bst-node)
add_subdirectory(effective-modern)
add_subdirectory(overload-resolution)
add_subdirectory(references)
add_subdirectory(variadic-templates)
