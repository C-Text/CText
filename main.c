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
#include "otsu.h"

//Initializong functions
void init_sdl();
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void grayscale (SDL_Surface* image_surface);
void wait_for_keypressed();
int mean(unsigned int *histo, int start, int end);
int sum(unsigned int *histo, int start, int end);
void histo(unsigned int histo[256], unsigned w, unsigned h,
	       SDL_Surface* image_surface);
int otsu(unsigned int histo[256], unsigned w, unsigned h);
void binarization(unsigned int w, unsigned int h, char binarization[w][h],
		int final_t, SDL_Surface* image_surface);
void SDL_FreeSurface(SDL_Surface *surface);

/**
  *Main function: use all functions initialized above to display an image and convert it into grayscale.
  *Then, it prints the binarization matrice of the given image and display the binarized image.
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

    int w = image_surface->w;
    int h = image_surface->h;

    int histo[256];
    histo(histo, w, h, image_surface);

    int threshold;
    threshold = otsu(histo, w, h);

    char binarization[w][h];
    binarization(w, h, binarization, threshold, image_surface);

    //print the matrix of the binarized image.
    printf("binarization: ");
    for (int i = 0; i < w; i++)
    {
	    for (int j = 0; j < h; j++)
	    {
		    printf("%d", binarization[i][j]);
	    }
	    printf("\n");
    }

    //display the binarized image.
    Uint8 gray;
    for (int i = 0; i <w; i++)
    {
	    for (int j = 0; j < h; j++)
	    {
		    Uint32 pixel = get_pixel(image_surface, i, j);
		    SDL_GetRGB(pixel, image_surface->format, &gray, &gray,
				    &gray);
		    pixel = SDL_MapRGB(image_surface->format, gray*255,
				    gray*255, gray*255);
		    put_pixel(image_surface, i, j, pixel);
	    }
    }

    update_surface(screen_surface, image_surface);

    wait_for_keypressed();

    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);

    return 0;
}
