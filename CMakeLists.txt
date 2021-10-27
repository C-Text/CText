cmake_minimum_required(VERSION 3.16)
project(CText C)

set(CMAKE_C_STANDARD 99)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(SDL REQUIRED sdl)
pkg_check_modules(SDL_IMAGE REQUIRED SDL_image)

include_directories(
        ${SDL_INCLUDE_DIRS}
        ${SDL_IMAGE_INCLUDE_DIRS}
        ${GTK3_INCLUDE_DIRS}
)

link_directories(
        ${SDL_LIBRARY_DIRS}
        ${SDL_IMAGE_LIBRARY_DIRS}
        ${GTK3_LIBRARY_DIRS}
)

add_definitions(
        ${SDL_CFLAGS_OTHER}
        ${SDL_IMAGE_CFLAGS_OTHER}
        ${GTK3_CFLAGS_OTHER}
)

add_executable(
        CText
        src/main.c
        src/libs/list/list.c
        src/libs/list/list.h
        src/libs/string/string.c
        src/libs/string/string.h
        src/libs/application/application.c
        src/libs/application/application.h
        src/libs/application/app.h
        src/libs/neural_network/neuralnetwork.c
        src/libs/neural_network/neuralnetwork.h
        src/libs/neural_network/neuron.c
        src/libs/neural_network/neuron.h
        src/libs/neural_network/train.c
        src/libs/neural_network/train.h
        src/libs/image_manipulation/pixel_operations.c
        src/libs/image_manipulation/pixel_operations.h
        src/libs/image_manipulation/otsu.c
        src/libs/image_manipulation/otsu.h
        src/libs/image_manipulation/grayscale.c
        src/libs/image_manipulation/grayscale.h
        src/libs/image_manipulation/segmentation.c
        src/libs/image_manipulation/segmentation.h
        src/libs/image_manipulation/bradley.c
        src/libs/image_manipulation/bradley.h
        src/libs/image_manipulation/filter.c
        src/libs/image_manipulation/filter.h
        src/libs/image_manipulation/rotation.c
        src/libs/image_manipulation/rotation.h)

target_link_libraries(CText m ${SDL_LIBRARY} ${SDL_IMAGE_LIBRARIES} ${GTK3_LIBRARIES})

if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wdouble-promotion -Wformat=2 -Wformat-truncation -Wformat-overflow -Wundef -fno-common -Wconversion -rdynamic")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -rdynamic -O0")
endif ()
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif ()