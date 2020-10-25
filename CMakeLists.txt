cmake_minimum_required(VERSION 3.16)
project(CText C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


find_package(SDL2 REQUIRED)
find_package(SDL REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
)

add_executable(
        CText src/neuralnetwork/main.c
        src/neuralnetwork/neuron.c src/neuralnetwork/neuron.h
        src/neuralnetwork/function.c src/neuralnetwork/function.h
        src/neuralnetwork/layer.c src/neuralnetwork/layer.h
        src/util.c src/util.h
        src/display/pixel_operations.c src/display/pixel_operations.h
        src/display/display.c src/display/display.h
        src/preprocessing/grayscale.c src/preprocessing/grayscale.h
        src/preprocessing/otsu.c src/preprocessing/otsu.h
)

add_executable(
        CText-tests src/test/main.c
        src/neuralnetwork/neuron.c src/neuralnetwork/neuron.h
        src/neuralnetwork/function.c src/neuralnetwork/function.h
        src/neuralnetwork/layer.c src/neuralnetwork/layer.h
        src/util.c src/util.h
        src/test/test.c src/test/test.h
        src/test/test_method.c src/test/test_method.h
)

add_executable(
        CText-display src/preprocessing/main.c
        src/display/pixel_operations.c src/display/pixel_operations.h
        src/display/display.c src/display/display.h
        src/preprocessing/grayscale.c src/preprocessing/grayscale.h
        src/preprocessing/otsu.c src/preprocessing/otsu.h
)

add_executable(
        CText-seg
        src/segmentation/segmentation.c src/segmentation/segmentation.h
)

target_link_libraries(CText m ${SDL_LIBRARY} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(CText-display m ${SDL_LIBRARY} ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(CText-tests m)

if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wdouble-promotion -Wformat=2 -Wformat-truncation -Wformat-overflow -Wundef -fno-common -Wconversion")
endif ()
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif ()