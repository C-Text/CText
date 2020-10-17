#include <stdio.h>
#include "network.h"
#include "layer.h"
#include "neuron.h"
#include "method.h"

#define EPOCHS 1000
#define LEARNING_RATE 0.1



int main(void) 
{
    // Input
    int inputs[4][2] =
    {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}
    };
    int outputs[4] = {0, 1, 1, 0};
    // Train    

    // Test
    return 0;
}
