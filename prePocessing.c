#include "SDL/SDL.h"

/*
 * convolMat: convolution matrix we want to apply
 * max: width of the convolution matrix
 * image_surface: the loaded image
*/

//applies convolution to the whole image.
void applyConvol(int[] convolMat, int max; SDL_Surface image_surface)
{
	int w = image_surface->w;  //get image width and height
	int h = image_surface->h;

	int x = max/2;  //get the initial point avoiding edges
	int y = max/2;

	for(; x < w - (max/2); x++)
	{
		for(; y < h - (max/2); y++)
		{
			//get the value of the current pixel
			Uint32 pixel = get_pixel(image_surface, x, y);
			Uint32 pix =0;

			for(int i = -(max/2); i<(max/2); i++)
			{
				for(int j = -(max/2); j<(max/2); j++)
				{
					//get the value of surrounding pixel
					pi = get_pixel(image_surface, x+i, y+j);

					//apply convolution
					pix += convolMat[i*max+j] *	pi
				}
			}
			//replace the old pixel value by the fresh one
			put_pixel(image_surface, x, y, pix/(max*max));
		}
	}
}


/*
 * image_surface: the loaded image
*/

//applies a median filter to the whole image
void medianFilter(SDL_Surface image_surface)
{
	int w = image_surface->w;  //get image width and height
	int h = image_surface->h;

	int x = max/2;  //get the initial point avoiding edges
	int y = max/2;

	for(; x < w - (max/2); x++)
	{
		for(; y < h - (max/2); y++)
		{
			//get the value of the current pixel
			Uint32 pixel = get_pixel(image_surface, x, y);
			Uint32 pix =0;

			for(int i = -(max/2); i<(max/2); i++)
			{
				for(int j = -(max/2); j<(max/2); j++)
				{
					//get the value of current surrounding pixel
					pi = get_pixel(image_surface, x+i, y+j);

					//sum the value of current surrounding pixel
					pix += pi;
				}
			}
			//replace the old pixel value by the fresh one
			put_pixel(image_surface, x, y, pix/(max*max));
		}
	}
}
