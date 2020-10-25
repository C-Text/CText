#include <stdio.h>
#include <math.h>
#include "display.h"
#include <err.h>
#include "SDL/SDL.h"
#include "pixel_operations.h"


void otsu_threshold(SDL_Surface* image_surface, int w, int h, char binarization[w][h])
{
	int hist[256];
	Uint8 average;
	
	Uint8 gray; 
	
	//Histogram
	for (int i = 0; i < 256; i++)
		hist[i]=0;

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
	
	//Probability density
	double prob[256];
	for (int i = 0; i < 256; i++)
	{
		prob[i] = hist[i] / (h*w); 
	}
	

	//omega and mu generation
	double omega[256];
	omega[0] = prob[0];
	double mu[256];
	mu[0] = 0.0;
	for (int i = 1; i < 256; i++)
	{
		omega[i] = omega[i-1] + prob[i];
		mu[i] = mu[i-1] + i*prob[i];
	}

	//maximization of sigma -> determines optimal threshold value
	int threshold = 0; 
	double max_sigma = 0.0;
	double sigma[256];

	for (int i = 0; i < 255; i++)
	{
		if (omega[i] !=0.0 && omega[i] != 1.0)
			sigma[i] = pow(mu[255]*omega[i] - mu[i], 2)/
				(omega[i]*(1.0 - omega[i]));
		else 
			sigma[i] = 0.0;
		if (sigma[i] > max_sigma)
		{
			max_sigma = sigma[i];
			threshold = i;
		}	
	}
	
	//binarization output
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			Uint32 pixel = get_pixel(image_surface, i, j);
			SDL_GetRGB(pixel, image_surface->format, &average, 
					&average, &average);
			if (average > threshold)
				binarization[i][j] = 1;
			else
				binarization[i][j] = 0;
		}
	}
}

