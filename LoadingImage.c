#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

int loadImage (char[] path)
{
	SDL_Surface* image = SDL_LoadBMP(path);

	if(!image)
	{
		printf("Loading Error : %s\n", SDL_GetError())
		return -1;
	}
	SDL_Texture* myImage = SDL_CreateTextureFromSurface(renderer, image);
	//myImage contains the loaded image.
	SDL_FreeSurface(image);
	//free the space of the surface after utilisation;
	return 0;
}
