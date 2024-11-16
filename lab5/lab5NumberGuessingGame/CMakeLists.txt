cmake_minimum_required(VERSION 3.0.0)
project(numberGuessing VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add_compile_options(-lm -Wall -Werror -Wextra -Wpedantic -O2)
add_compile_options(-lm -Wall -Wextra -Wpedantic)

add_executable(numberGuessing main.c Game.c utils.c terminal.c)

target_link_libraries(numberGuessing m)
