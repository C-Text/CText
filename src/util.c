#include "util.h"

/**
 *
 * Returns the minimum in an unsorted array. This will test the whole array.
 *
 * @date    24/10/2020
 * @version 0.0.1
 * @author  Valentin (Vinetos) Chassignol
 * @package base
 *
 * @throw error if size is null of size > array's size
 * @param inputs the array
 * @param size   the size of the array
 *
 * @return the minimum of the array.
 */
double find_min(double *inputs, size_t size) {
  if (size <= 0 || size <= (sizeof(inputs) / sizeof(double)))
    return -INFINITY;

  double min;
  for (size_t i = 1; i < size; i++)
    if (inputs[i] < min)
      min = inputs[i];

  return min;
}

/**
 *
 * Format and print the given array in the console.
 *
 * @date    24/10/2020
 * @version 0.0.1
 * @author  Valentin (Vinetos) Chassignol
 * @package base
 *
 * @throw error if size is null of size > array's size
 * @param inputs the array
 * @param size   the size of the array (or the max index to print excluded)
 */
void print_array(double *arr, size_t size) {
  if (size == 0) {
    printf("[]");
    return;
  }
  printf("[");
  for (size_t i = 0; i < size - 1; i++)
    printf("%lf, ", arr[i]);
  printf("%lf]\n", arr[size - 1]);
}