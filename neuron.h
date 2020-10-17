#ifndef NEURON_H
#define NEURON_H

typedef struct neuron_t
{

    float bias; // The bias of a neuron
    float *out_weights; // The array containing output weights

} neuron;

neuron create_neuron(int num_out_weights);

#endif
