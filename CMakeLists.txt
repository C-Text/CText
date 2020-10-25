cmake_minimum_required(VERSION 3.17)
project(CText C)

set(CMAKE_C_STANDARD 99)

add_executable(
        CText src/main.c
        src/util.c src/util.h src/neuralnetwork/neuron.c src/neuralnetwork/neuron.h src/neuralnetwork/function.c src/neuralnetwork/function.h src/neuralnetwork/layer.c src/neuralnetwork/layer.h)

add_executable(
        CText-tests src/main.c
        src/util.c src/util.h src/neuralnetwork/neuron.c src/neuralnetwork/neuron.h src/neuralnetwork/function.c src/neuralnetwork/function.h src/neuralnetwork/layer.c src/neuralnetwork/layer.h)

target_link_libraries(CText m)
target_link_libraries(CText-tests m)