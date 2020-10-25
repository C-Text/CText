#include "neuralnetwork/layer.h"
#include <stdio.h>

void prints(layer *l1, layer *l2) {
  lprint(l1, true);
  printf("\n");
  lprint(l2, true);
  printf("\n");
}

void test(int ** arr) {
  for (int i = 0; i < 5; ++i) {
    printf("%d", arr[i][i]);
  }
}

int main(void) {
  const unsigned int EPOCHS = 100;
  // XOR table
  double inputs[4][2] = {
      {0.0, 0.0},
      {0.0, 1.0},
      {1.0, 0},
      {1.0, 1.0}
  };
  double outputs[4] = {0.0, 1.0, 1.0, 0.0};
  // Creating layers
  layer l = create_layer(2, 1);
  layer l2 = create_layer(1, 1);

  // Input
  feed(&l, inputs[1]);
  printf("================== INPUT ==================\n");
  prints(&l,&l2);

  // Activate the layer
  activate(&l);
  printf("================== ACTIV ==================\n");
  prints(&l,&l2);

  //Feed forward
  feedforward(&l,&l2);
  printf("================== FEEDF ==================\n");
  prints(&l,&l2);

  double out = sum(&l2, 0);
  printf("OUTPUT: %lf", out);

  return 0;
}
