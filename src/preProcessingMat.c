#include "pixel_operations.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"


/*
 * matrix: the image matrix
 * max: the width of the median filter
 * w: the width of the matrix
 * h: the height of the matrix
*/

//applies a median filter to the whole image
void medianFilterMatrix(int matrix[], int max, int w, int h)
{
	int* tmp = matrix;

	for(int x = max/2; x < w-(max/2); x++)  //traverese the image
	{
		for(int y = max/2; y < h-(max/2); y++)
		{
			int *list = calloc(max*max, sizeof(int));
			int pix;

			int index = 0;

			for(int i = -(max/2); i<=(max/2); i++)  //for each pixel
			{
				for(int j = -(max/2); j<=(max/2); j++)
				{
					pix = tmp[(x+i)*max + y+j];

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
						int swp = list[m];
						list[m] = list[m+1];
						list[m+1] = swp;
					}
				}
			}
			//replace the old pixel value by the median
			matrix[x*w+y] = list[(max*max)/2];
		}
	}
}
