#ifndef LAYER_H
#define LAYER_H

#include "neuron.h"

typedef struct layer_t
{
    int num_neu;// Number of neurons in this layer
    struct neuron_t *neu;// The neurons
} layer;

layer create_layer(long unsigned int num_neu);

#endif
