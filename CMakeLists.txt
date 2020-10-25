cmake_minimum_required(VERSION 3.17)
project(CText C)

set(CMAKE_C_STANDARD 99)

add_executable(
        CText src/main.c
)

add_executable(
        CText-tests src/main.c
)

target_link_libraries(CText m)
target_link_libraries(CText-tests m)