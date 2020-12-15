#include "grayscale.h"
#include "pixel_operations.h"

/**
  * Author: Lise Giraud
  * Date: 22/10/2020
  * File's name: grayscale.c
  */

/**
  * Convert colored image into grayscale image.
  *
  * @param image_surface is the image to convert into grayscale.
  */
void grayscale(SDL_Surface *image_surface) {
  int w = image_surface->w;
  int h = image_surface->h;
  Uint8 r, g, b;

  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      Uint32 pixel = get_pixel(image_surface, i, j);
      SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
      float average = 0.3 * r + 0.59 * g + 0.11 * b;
      r = average;
      g = average;
      b = average;
      pixel = SDL_MapRGB(image_surface->format, r, g, b);
      put_pixel(image_surface, i, j, pixel);
    }
  }
}

void gtk_grayscale(GdkPixbuf *pixbuf) {
  int width, height, rowstride, n_channels;
  guchar *pixels, *p;

  n_channels = gdk_pixbuf_get_n_channels (pixbuf);

  g_assert (gdk_pixbuf_get_colorspace (pixbuf) == GDK_COLORSPACE_RGB);
  g_assert (gdk_pixbuf_get_bits_per_sample (pixbuf) == 8);
  g_assert (gdk_pixbuf_get_has_alpha (pixbuf));
  g_assert (n_channels == 4);

  width = gdk_pixbuf_get_width (pixbuf);
  height = gdk_pixbuf_get_height (pixbuf);

  for (int x = 0; x < width; x++){
    for (int y = 0; y < height; y++){
      rowstride = gdk_pixbuf_get_rowstride (pixbuf);
      pixels = gdk_pixbuf_get_pixels (pixbuf);

      p = pixels + y * rowstride + x * n_channels;
      double average = 0.3 * p[0] + 0.59 * p[1] + 0.11 * p[2];
      gtk_put_pixel(pixbuf,x,y,average,average,average,p[3]);
    }
  }
}