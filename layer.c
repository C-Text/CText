#include <stdlib.h>
#include "layer.h"

/**
 * Initialize a layer with the given size
 */
layer create_layer(long unsigned int num_neu) {
    layer lay;
    lay.num_neu = -1;
    lay.neu = (struct neuron_t *) malloc(num_neu * sizeof(struct neuron_t));
    return lay;
}
