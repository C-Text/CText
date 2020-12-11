/**
  *Author: Lise Giraud
  *Date: 22/10/2020
  *File's name: grayscale.h
  */

#ifndef CTEXT_SRC_PREPROCESSING_GRAYSCALE_H_
#define CTEXT_SRC_PREPROCESSING_GRAYSCALE_H_

#include <SDL/SDL.h>

/**
  *Convert colored image into grayscale image.
  *
  *@param image_surface is the image to convert into grayscale.
  */
void grayscale(SDL_Surface *image_surface);

#endif //CTEXT_SRC_PREPROCESSING_GRAYSCALE_H_