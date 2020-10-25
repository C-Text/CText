/**
  *Author: Lise Giraud
  *Date: 20/10/2020
  *File's name: display.h
  */

#ifndef DISPLAY_H
#define DISPLAY_H

/**
 *Init only the video part.
 *@throw error message if it fail.
 */
void init_sdl();



/**
 *Load an image from a given path using SDL_image with format detection.
 *
 *@throw error if there is no image at the given path.
 *@param path: the path of the image to display.
 *
 *@return image found at the given path.
 */
SDL_Surface* load_image(char *path);



/**
 *Displays a given image in a window.
 *
 *@throw error if screen is null (cannot set video mode).
 *@param img the image to display in a window.
 *
 @return screen: a displayed image in a window.
 */
SDL_Surface* display_image(SDL_Surface *img);



/**
 *Wait for a key of the keyboard to be pressed before executing any action.
 */
void wait_for_keypressed();

#endif
