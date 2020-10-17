#include <stdlib.h>
#include "neuron.h"

neuron create_neuron(long unsigned int num_out_weights)
{
    neuron neu;
    neu.out_weights = (float*) malloc(num_out_weights * sizeof(float));
    neu.bias = 0.0;
    return neu;
}
