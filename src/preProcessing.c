#include "pixel_operations.h"
#include "SDL/SDL.h"


/**
 * Applies a convolution matrix to the whole image
 * @param convolMat: convolution matrix we want to apply
 * @param max: width of the convolution matrix
 * @param image_surface: the loaded image
 */
void applyConvol(int convolMat[], int max, SDL_Surface *image_surface)
{
	int w = image_surface->w;  //get image width and height
	int h = image_surface->h;

	SDL_Surface *tmp = image_surface;

	for(int x = max/2; x < w - (max/2); x++)
	{
		for(int y = max/2; y < h - (max/2); y++)
		{
			Uint32 pi;
			Uint8 r, g, b;

			Uint8 R=0, G=0, B=0;
			int iR = (int)R;
			int iG = (int)G;
			int iB = (int)B;

			for(int i = -(max/2); i<=(max/2); i++)  //courses current pixels and neighbours
			{
				for(int j = -(max/2); j<=(max/2); j++)
				{
					//get the value of surrounding pixel
					pi = get_pixel(tmp, x+i, y+j);

					SDL_GetRGB(pi, tmp->format, &r, &g, &b);

					int index = (i+max/2)*max + (j+max/2);
		
					int ir = (int)r;
					int ig = (int)g;
					int ib = (int)b;

					ir = (ir*convolMat[index]);//matrixSum;
					ig = (ig*convolMat[index]);//matrixSum;
					ib = (ib*convolMat[index]);//matrixSum;
	
					iR+=ir;
					iG+=ig;
					iB+=ib;
				}
			}

			//replace the old pixel value by the fresh one
			iR = iR/(max*max)*2;
			iG = iG/(max*max)*2;
			iB = iB/(max*max)*2;
			
			if(iR>254)
				iR = 254;
			else if(iR<0)
				iR = 0;
			
			if(iG>254)
				iG = 254;
			else if(iG<0)
				iG = 0;

			if(iB>254)
				iB = 254;
			if(iB<0)
				iB = 0;

			R = (Uint8)iR;
			G = (Uint8)iG;
			B = (Uint8)iB;

			pi = SDL_MapRGB(image_surface->format, R, G, B);

			put_pixel(image_surface, x, y, pi);
		}
	}
}


/**
 * Applies a median filter to the whole image
 * @param image_surface: the loaded image
 * @param max: the width of the median filter
 * @return the new image_surface
 */
SDL_Surface medianFilter(SDL_Surface *image_surface, int max)
{
	int w = image_surface->w;  //get image width and height
	int h = image_surface->h;

	SDL_Surface* tmp = image_surface;

	for(int x = max/2; x < (w - (max/2)); x++)  //traverese the image
	{
		for(int y = max/2; y < (h - (max/2)); y++)
		{
			Uint32 *list = calloc(max*max, sizeof(Uint32));
			Uint32 pix;

			int index = 0;

			for(int i = -(max/2); i<=(max/2); i++)  //for each pixel
			{
				for(int j = -(max/2); j<=(max/2); j++)
				{
					pix = get_pixel(tmp, x+i, y+j);

					list[index] = pix;
					index++;
				}
			}

			//sort list
			for(int k = 0; k< (max*max); k++)
			{
				for(int m = 0; m < (k-1); m++)
				{
					if(list[m+1] < list[m])
					{
						Uint32 swp = list[m];
						list[m] = list[m+1];
						list[m+1] = swp;
					}
				}
			}
			//replace the old pixel value by the median
			put_pixel(image_surface, x, y, list[(max*max)/2]);
		}
	}
	return *image_surface;
}
