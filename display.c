#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdio.h>
#include "pixel_operations.h"

void init_sdl();
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void wait_for_keypressed();
void SDL_FreeSurface(SDL_Surface *surface);


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

   FILE * file = fopen(str, "r");
   if (!file){
	   exit(201);
   }
   fseek(file, 0L, SEEK_END);
   Uint32 res = ftell(file);
   fclose(file);

    SDL_Surface* image_surface = malloc(res);
    SDL_Surface* screen_surface = malloc(res);

    init_sdl(); 

    image_surface = load_image(str);
    screen_surface = display_image(image_surface);

    wait_for_keypressed();

    int w = image_surface->w;
    int h = image_surface->h;
    Uint8 r, g, b;


    for (int i = 0; i < w; i++)
    {
	    for (int j = 0; j < h; j++)
	    {
		    Uint32 pixel = get_pixel(image_surface, i,j);
		    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
		    float average = 0.3*r + 0.59*g + 0.11*b;
		    r = average;
		    g = average;
		    b = average;
		    pixel = SDL_MapRGB(image_surface->format, r, g, b);
		    put_pixel(image_surface, i,j, pixel);
	    }
    }

    update_surface(screen_surface, image_surface);

    wait_for_keypressed();

    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);

    return 0;
}

void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}

SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;

    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    img = IMG_Load(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}

SDL_Surface* display_image(SDL_Surface *img)
{
    SDL_Surface *screen;

    // Set the window to the same size as the image
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
    if (screen == NULL)
    {
        // error management
        errx(1, "Couldn't set %dx%d video mode: %s\n",
                img->w, img->h, SDL_GetError());
    }

    // Blit onto the screen surface
    if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    // Update the screen
    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

    // return the screen for further uses
    return screen;
}

void wait_for_keypressed()
{
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
}
