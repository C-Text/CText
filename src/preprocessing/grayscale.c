#include "SDL/SDL.h"
#include "../display/pixel_operations.h"

/**
  *Author: Lise Giraud
  *Date: 22/10/2020
  *File's name: grayscale.c
  */

/**
  *Convert colored image into grayscale image.
  *
  *@param image_surface is the image to convert into grayscale.
  */
void grayscale(SDL_Surface *image_surface) {
  int w = image_surface->w;
  int h = image_surface->h;
  Uint8 r, g, b;

  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      Uint32 pixel = get_pixel(image_surface, i, j);
      SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
      float average = 0.3 * r + 0.59 * g + 0.11 * b;
      r = average;
      g = average;
      b = average;
      pixel = SDL_MapRGB(image_surface->format, r, g, b);
      put_pixel(image_surface, i, j, pixel);
    }
  }
}
