/**
  *Author: Lise Giraud and Valentin Chassignol 
  *Date: 24/10/2020
  *File's name : otsu.c 
  */

#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "display.h"
#include "grayscale.h"



/**
  *Calculation of the median in the histogram between start and end values.
  *
  *@param histo is the histogram of grayscale in a given image.
  *@param start is where to start to calculate the median.
  *@param end is where to end to calculate the median.
  *
  *@return the median value between start and end in the histogram.
  */
int mean(unsigned int *histo, int start, int end) {
  return histo[end - start];
}



/**
  *Calculate the sum between start and end (end excluded) of the histogram.
  *
  *@param *histo is the histogram of grayscale in a given image.
  *@param start is where to start the calculus.
  *@param end is where to end the calculus (end is excluded).
  *
  *@return the sum of all the values between start and end.
  */
int sum(unsigned int *histo, int start, int end) {
  int sum = 0;
  for (int i = start; i < end; i++)
    sum += (int) histo[i];
  return sum;
}


/**
  *Make the grayscale histogram of a given image.
  *
  *@param histo is the histogram to complete.
  *@param w is the weight of the image.
  *@param h is the height of the image.
  *@param image_surface is the given image to make histogram.
  */
void histo(unsigned int histo[256], unsigned w, unsigned h,
		SDL_Surface* image_surface)
{
	Uint8 gray;

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			Uint32 pixel = get_pixel(image_surface, i, j);
			SDL_GetRGB(pixel, image_surface->format,
					&gray, &gray, &gray);
			hist[gray] += 1;
		}
	}
}



/**
  *Use the otsu's method to calculate the optimal threshold of a grayscale image.
  *
  *@param histo is the histogram of grayscale of the image.
  *@param w is the weight of the image.
  *@param h is the height of the image.
  *
  *@return the optimal threshold.
  */
int otsu(unsigned int histo[256], unsigned w, unsigned h)
{
  double final_thresh = -1.0;
  int final_t = -1;
  double mean_weight = 1.0 / (w * h);
  for (int t = 1; t < 255; t++)
  {
	  double wb = (double) sum(histo, 0, t) * mean_weight;
	  double wf = (double) sum(histo, t, 255) * mean_weight;

	  int mub = mean(histo, 0, t);
	  int muf = mean(histo, t, 255);

	  double value = wb * wf * (mub - muf);
	  value *= value;
	  if (value > final_thresh)
	  {
		  final_thresh = value;
		  final_t = t;
	  }
  }
  return final_t;
}



/**
  *Complete the binarization matrice (matrice of 1 and 0).
  *
  *@param w is the weight of the image to binarize.
  *@param h is the height of the image to binarize.
  *@param binarization is the binarization matrice of the image. Must contain only 0 and 1.
  *@param final_t is the optimal threshold of the image to binarize.
  *@param image_surface is the image to binarize.
  */
void binarization(unsigned int w, unsigned int h, char binarization[w][h],
		int final_t, SDL_Surface* image_surface)
{
	Uint8 average;
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			Uint32 pixel = get_pixel(image_surface, i, j);
			SDL_GetRGB(pixel, image_surface->format, &average,
					&average, &average);
			if (average > final_t)
				binarization[i][j] = 1;
			else 
				binarization[i][j] = 0;
		}
	}
}
