#ifndef METHOD_H
#define METHOD_H

float softmax(float x);

float softmax_prime(float x);

float mse(float expected, float prediction);

float mse_prime(float expected, float prediction);

#endif
