#ifndef NETWORK_H
#define NETWORK_H

#include "layer.h"

typedef struct network_t
{
    int num_layer; // Numbers of layer in this netork
    struct layer_t *layers; // All layers in the network
} network;

network create_network(long unsigned int num_layers);


#endif
