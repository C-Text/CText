cmake_minimum_required(VERSION 3.17)
project(CText C)

set(CMAKE_C_STANDARD 99)

add_executable(
        CText src/main.c
        src/neuralnetwork/neuron.c src/neuralnetwork/neuron.h
        src/neuralnetwork/function.c src/neuralnetwork/function.h
        src/neuralnetwork/layer.c src/neuralnetwork/layer.h
        src/util.c src/util.h
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

target_link_libraries(CText m)
target_link_libraries(CText-tests m)

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wdouble-promotion -Wformat=2 -Wformat-truncation -Wformat-overflow -Wundef -fno-common -Wconversion")
endif()
if ( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()