#include <stdlib.h>
#include "network.h"
#include "neuron.h" 

network create_network(long unsigned int number_of_layers)
{
    network net;
    net.num_layer = -1;
    net.layers = (struct layer_t *) malloc(number_of_layers * sizeof(struct layer_t));

    return net;
}
