cmake_minimum_required(VERSION 3.16)
project(CText C)

set(CMAKE_C_STANDARD 99)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

include_directories(
        ${SDL_INCLUDE_DIRS}
        ${SDL_IMAGE_INCLUDE_DIRS}
)

add_executable(
        CText
        src/main.c
        src/libs/list/list.c
        src/libs/list/list.h
        src/libs/neural_network/neuralnetwork.c
        src/libs/neural_network/neuralnetwork.h
        src/libs/neural_network/neuron.c
        src/libs/neural_network/neuron.h
)

target_link_libraries(CText m ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARIES})

if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wdouble-promotion -Wformat=2 -Wformat-truncation -Wformat-overflow -Wundef -fno-common -Wconversion")
endif ()
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif ()