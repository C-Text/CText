#include "train.h"
#include <stdio.h>
#include <stdlib.h>
#include "neuralnetwork.h"
#include "../image_manipulation/pixel_operations.h"
#include <SDL/SDL.h>

char result_elements[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
    'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
    'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
    's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '.', ';', ':', '!', '?',
    '\'', '(', ')', '[', ']', '-', '%'
};

double *get_matrix(SDL_Surface *image) {
  // Create the new array
  int length = 32;
  double *array = calloc(length * length, sizeof(double));

  // convert the image into matrix
  Uint8 r, g, b;
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length; j++) {
      if (i >= image->w || j >= image->h) {
        array[i * length + j] = 0;
        printf("%d", 0);
      } else {
        Uint32 pixel = (get_pixel(image, i, j));
        SDL_GetRGB(pixel, image->format, &r, &b, &g);

        // if the pixel is black ->1 else -> 0
        if (r < 240 && g < 240 && b < 240)
          array[i * length + j] = 1;
        else
          array[i * length + j] = 0;
        printf("%d", r < 240 ? 1 : 0);
      }
    }
    printf("\n");
  }
  printf("\n");
  return array;
}

void training() {
  // Save all images into an array
  double **models = malloc(sizeof(char *) * 74);

  char paths[] = "src/assets/font-01/letter001.bmp";

  int index_in = 0;
  //for (int m = 0; m < 74; m++) {
      SDL_Surface *image = SDL_LoadBMP(paths);
      models[index_in] = get_matrix(image);
      index_in++;
      if (paths[27] == '9') {
        paths[27] = '0';
        paths[26]++;
      }
  //}

}
