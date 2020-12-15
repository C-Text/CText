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

double *get_matrix(SDL_Surface *image_surface) {
  // Create the new array
  int length = 32;
  double *array = calloc(length * length, sizeof(double));

  // convert the image into matrix
  for (int j = 0; j < image_surface->h; j++) {
    for (int i = 0; i < image_surface->w; i++) {
      Uint8 r, g, b;
      Uint32 pixel = get_pixel(image_surface, i, j);
      SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
      // if the pixel is black ->1 else -> 0
      array[j * length + i] = ((r + b + g) / 3 < 240) ? 1 : 0;
    }

  }

  /*for (int i = 0; i < 1024; i++) {
    if (i % 32 == 0)
      printf("\n");
    printf("%d", (int) array[i]);
  }

  printf("\n");*/
  return array;
}

int * to_nn_sized(GdkPixbuf *pixbuf) {
  int *intput = malloc(sizeof(int) * 32*32);

  int width = gdk_pixbuf_get_width(pixbuf);
  int height = gdk_pixbuf_get_height(pixbuf);
  int n_channels = gdk_pixbuf_get_n_channels(pixbuf);

  g_assert (gdk_pixbuf_get_colorspace(pixbuf) == GDK_COLORSPACE_RGB);
  g_assert (gdk_pixbuf_get_bits_per_sample(pixbuf) == 8);
  g_assert (gdk_pixbuf_get_has_alpha(pixbuf));
  g_assert (n_channels == 4);

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      int rowstride = gdk_pixbuf_get_rowstride(pixbuf);
      guchar *pixels = gdk_pixbuf_get_pixels(pixbuf);

      guchar *p = pixels + y * rowstride + x * n_channels;
      intput[x * height + y] = p[0];
    }
  }
  return intput;
}

void training() {
  // Save all images into an array
  double **models = malloc(sizeof(char *) * 74);
  double *expected = malloc(sizeof(double) * 74);

  char paths[] = "src/assets/font-01/letter000.bmp";

  int index_in = 0;
  for (int m = 0; m < 74; m++) {
    SDL_Surface *image = SDL_LoadBMP(paths);
    models[index_in] = get_matrix(image);
    index_in++;
    if (paths[27] == '9') {
      paths[27] = '0';
      paths[26]++;
    } else
      paths[27]++;
  }

  size_t nb_neurons_per_layer[4] = {
      1024, 100, 100, 74
  };
  NeuralNetwork network;

  init(&network, 4, nb_neurons_per_layer);
  for (int i = 0; i < 10000; i++) {
    if (i % 100 == 0) {
      printf("%d\n", i);
      save_neural_network(&network, "src/assets/trained-network.txt");
    }

    for (int c = 0; c < 74; c++) {
      propagation(&network, models[c]);
      expected[c] = 1;
      backpropagation(&network, expected, 0.1);
      expected[c] = 0;
    }
  }
  for (int c = 0; c < 74; c++) {
    printf("%c -> %c\n", result_elements[c], result_elements[predict(&network,
                                                                 models[c])]);
  }
}