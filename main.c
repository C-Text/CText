/**
  *Author: Lise Giraud
  *Date: 24/10/2020
  *File's name: main.c
*/
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdio.h>
#include "pixel_operations.h"
#include "display.h"
#include "grayscale.h"

//Initializong functions
void init_sdl();
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void grayscale (SDL_Surface* image_surface);
void wait_for_keypressed();
void SDL_FreeSurface(SDL_Surface *surface);

/**
  *Main function: use all functions initialized above to display an image and convert it into grayscale
  */
int main()
{
	char str[100];

   printf( "Enter the path of an image :");
   int scan = scanf("%s", str);
   if (scan == 0)
   {
	   errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
   }

   printf( "\nYou entered: %s", str);

    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    init_sdl(); 

    image_surface = load_image(str);
    screen_surface = display_image(image_surface);

    wait_for_keypressed();

    grayscale(image_surface);

    update_surface(screen_surface, image_surface);

    wait_for_keypressed();

    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);

    return 0;
}
