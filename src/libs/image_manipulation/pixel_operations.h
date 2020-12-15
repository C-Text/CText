#ifndef CTEXT_PIXEL_OPERATIONS_H_
#define CTEXT_PIXEL_OPERATIONS_H_
/**
  *Author: Lise Giraud
  *Date: 22/10/2020
  *File's name: pixel_operations.h
  */

#include <stdlib.h>
#include <err.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

/**
 *get the pixel on coordonates x y of the image.
 *
 *@param *surface is the SDL surface of the image.
 *@param x and param y are the coordonates (x,y) of the pixel on the surface.
 *
 *@return the pixel (x,y) in the right format.
  */
Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);

/**
 *Replace the pixel (x,y) by the new value pixel on a given surface.
 *
 *@param *surface is the SDL surface of the image.
 *@param x and param y are the coordinates (x,y) of the pixel to replace on the image.
 *@param pixel is the new value of the pixel.
 *
 */
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

/**
 *Update the "old" surface with its new values.
 *
 *@throw warning if there is no surface to blit.
 *@param screen is the window to update.
 *@param image is the image to update.
 */
void update_surface(SDL_Surface *screen, SDL_Surface *image);

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
SDL_Surface *load_image(char *path);

/**
 * Put pixel function implemented for GdkPixBuf
 * @param pixbuf
 * @param x
 * @param y
 * @param red
 * @param green
 * @param blue
 * @param alpha
 */
void
gtk_put_pixel (GdkPixbuf *pixbuf, int x, int y, guchar red, guchar green, guchar
blue, guchar alpha);

#endif //CTEXT_PIXEL_OPERATIONS_H_