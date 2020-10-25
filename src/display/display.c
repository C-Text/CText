#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"


/**
  *Author: Lise Giraud
  *Date: 20/10/2020
  */

/**
  *Init only the video part.
  *
  *@throw error message if it fail.
  */
void init_sdl() {
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    errx(1, "Could not initialize SDL: %s.\n", SDL_GetError());
}

/**
  *Load an image from a given path using SDL_image with format detection.
  *
  *@throw error if there is no image at the given path.
  *@param path: the path of the image to display.
  *
  *@return image found at the given path.
  */
SDL_Surface *load_image(char *path) {
  SDL_Surface *img;

  img = IMG_Load(path);
  if (!img)
    errx(3, "can't load %s: %s", path, IMG_GetError());

  return img;
}

/**
  *Displays a given image in a window.
  *
  *@throw error if screen is null (cannot set video mode).
  *@param img the image to display in a window.
  *
  @return screen: a displayed image in a window.
  */
SDL_Surface *display_image(SDL_Surface *img) {
  SDL_Surface *screen;

  // Set the window to the same size as the image
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE | SDL_ANYFORMAT);
  if (screen == NULL) {
    // error management
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }

  // Blit onto the screen surface
  if (SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());

  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);

  // return the screen for further uses
  return screen;
}

/**
  *Wait for a key of the keyboard to be pressed before executing any action.
  */
void wait_for_keypressed() {
  SDL_Event event;

  // Wait for a key to be down.
  do {
    SDL_PollEvent(&event);
  } while (event.type != SDL_KEYDOWN);

  // Wait for a key to be up.
  do {
    SDL_PollEvent(&event);
  } while (event.type != SDL_KEYUP);
}