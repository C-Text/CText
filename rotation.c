#include "SDL/SDL.h"


/*
 * image_surface: loaded image
*/

//returns the angle of the image
int getAngle(SDL_Surface image_surface)
{
	int angle = 0;

	//

	return angle;
}


/*
 * angle: the angle we want to rotate the image with
 * image_surface: the loaded image
*/

//rotates the image according to the angle 'angle'
void rotation(int angle, SDL_Surface image_surface)
{
	int w = image_surface->w;  //get image width and height
	int h = image_surface->h;

	for(int i=0; i< w; i++)
	{
		for(int j =0; j< h; j++)
		{
			//
		}
	}
}
