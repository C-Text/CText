/**
  *Author: Lise
  *Date: 22/10/2020
  *File's name: pixel_operations.c
  */
#include "pixel_operations.h"

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
  *Determines on how many bytes pixels are encoded.
  *
  *@param surf is the SDL surface of the image.
  *@param x and param y are the coordonates (x,y) of the pixel on the surface.
  *
  *@return the value of the pixel(r,g,b) in decimal base.
  */
static inline
Uint8 *pixel_ref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8 *) surf->pixels + y * surf->pitch + x * bpp;
}

/**
  *get the pixel on coordonates x y of the image.
  *
  *@param *surface is the SDL surface of the image.
  *@param x and param y are the coordonates (x,y) of the pixel on the surface.
  *
  *@return the pixel (x,y) in the right format.
  */
Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y) {
  Uint8 *p = pixel_ref(surface, x, y);

  switch (surface->format->BytesPerPixel) {
    case 1:return *p;

    case 2:return *(Uint16 *) p;

    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;

    case 4:return *(Uint32 *) p;
  }

  return 0;
}

/**
  *Replace the pixel (x,y) by the new value pixel on a given surface
  *
  *@param *surface is the SDL surface of the image
  *@param x and param y are the coordinates (x,y) of the pixel to replace onthe image.
  *@param pixel is the new value of the pixel.
  *
  */
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
  Uint8 *p = pixel_ref(surface, x, y);

  switch (surface->format->BytesPerPixel) {
    case 1:*p = pixel;
      break;

    case 2:*(Uint16 *) p = pixel;
      break;

    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        p[0] = (pixel >> 16) & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = pixel & 0xff;
      } else {
        p[0] = pixel & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = (pixel >> 16) & 0xff;
      }
      break;

    case 4:*(Uint32 *) p = pixel;
      break;
  }
}

/**
  *Update the "old" surface with its new values.
  *
  *@throw warning if there is no surface to blit.
  *@param screen is the window to update
  *@param image is the image to update
  */
void update_surface(SDL_Surface *screen, SDL_Surface *image) {
  if (SDL_BlitSurface(image, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());

  SDL_UpdateRect(screen, 0, 0, image->w, image->h);
}

void
gtk_put_pixel (GdkPixbuf *pixbuf, int x, int y, guchar red, guchar green, guchar
blue, guchar alpha)
{
  int rowstride, n_channels;
  guchar *pixels, *p;

  n_channels = gdk_pixbuf_get_n_channels (pixbuf);
  rowstride = gdk_pixbuf_get_rowstride (pixbuf);
  pixels = gdk_pixbuf_get_pixels (pixbuf);

  p = pixels + y * rowstride + x * n_channels;
  p[0] = red;
  p[1] = green;
  p[2] = blue;
  p[3] = alpha;
}