#ifndef _PREPROCESSING_H_
#define _PREPROCESSING_H_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

void applyConvol(int convolMat[], int max, SDL_Surface* image_surface);

SDL_Surface medianFilter(SDL_Surface* image_surface, int max);

#endif
