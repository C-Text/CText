/**
  * Author: Lise Giraud and Valentin Chassignol
  * Date: 24/10/2020
  * File's name : otsu.c
  */

#include <err.h>
#include <SDL/SDL.h>
#include "pixel_operations.h"
#include "../application/app.h"

/**
  * Calculation of the median in the histogram between start and end values.
  *
  * @param histo is the histogram of grayscale in a given image.
  * @param start is where to start to calculate the median.
  * @param end is where to end to calculate the median.
  *
  * @return the median value between start and end in the histogram.
  */
int mean(unsigned int *histo, int start, int end) {
  return histo[end - start];
}

/**
  * Calculate the sum between start and end (end excluded) of the histogram.
  *
  * @param *histo is the histogram of grayscale in a given image.
  * @param start is where to start the calculus.
  * @param end is where to end the calculus (end is excluded).
  *
  * @return the sum of all the values between start and end.
  */
int sum(unsigned int *histo, int start, int end) {
  int sum = 0;
  for (int i = start; i < end; i++)
    sum += (int) histo[i];
  return sum;
}

void histo(unsigned int histo[256], GdkPixbuf *pixbuf) {
  int n_channels = gdk_pixbuf_get_n_channels (pixbuf);

  g_assert (gdk_pixbuf_get_colorspace (pixbuf) == GDK_COLORSPACE_RGB);
  g_assert (gdk_pixbuf_get_bits_per_sample (pixbuf) == 8);
  g_assert (gdk_pixbuf_get_has_alpha (pixbuf));
  g_assert (n_channels == 4);

  int w = gdk_pixbuf_get_width (pixbuf);
  int h = gdk_pixbuf_get_height (pixbuf);
  for (int i = 0; i < w; i++)
    for (int j = 0; j < h; j++) {
      int rowstride = gdk_pixbuf_get_rowstride (pixbuf);
      guchar *pixels = gdk_pixbuf_get_pixels (pixbuf);

      guchar *p = pixels + j * rowstride + i * n_channels;
      histo[p[1]] += 1;
    }
}

int otsu(unsigned int histo[256], unsigned w,unsigned h) {
  double final_thresh = -1.0;
  int final_t = -1;
  double mean_weight = 1.0 / (w * h);
  for (int t = 1; t < 255; t++) {
    double wb = (double) sum(histo, 0, t) * mean_weight;
    double wf = (double) sum(histo, t, 255) * mean_weight;

    int mub = mean(histo, 0, t);
    int muf = mean(histo, t, 255);

    double value = wb * wf * (mub - muf);
    value *= value;
    if (value > final_thresh) {
      final_thresh = value;
      final_t = t;
    }
  }
  return final_t;
}

/**
  *Complete the binarization matrice (matrice of 1 and 0).
  *
  *@param w is the weight of the image to binarize.
  *@param h is the height of the image to binarize.
  *@param binarization is the binarization matrice of the image. Must contain only 0 and 1.
  *@param final_t is the optimal threshold of the image to binarize.
  *@param image_surface is the image to binarize.
  */
void binarization(unsigned int w, unsigned int h, char binarization[w][h],
                  int final_t, SDL_Surface *image_surface) {
  Uint8 average;
  for (size_t i = 0; i < w; i++) {
    for (size_t j = 0; j < h; j++) {
      Uint32 pixel = get_pixel(image_surface, i, j);
      SDL_GetRGB(pixel, image_surface->format, &average,
                 &average, &average);
      if (average > final_t)
        binarization[i][j] = 1;
      else
        binarization[i][j] = 0;
    }
  }
}

void gtk_otsu_binarization(GdkPixbuf *pixbuf) {
  unsigned int *h = calloc(sizeof(unsigned int), 256);
  histo(h, pixbuf);

  int width = gdk_pixbuf_get_width(pixbuf);
  int height = gdk_pixbuf_get_height(pixbuf);

  int final_t = otsu(h, width, height);

  int n_channels = gdk_pixbuf_get_n_channels(pixbuf);

  g_assert (gdk_pixbuf_get_colorspace(pixbuf) == GDK_COLORSPACE_RGB);
  g_assert (gdk_pixbuf_get_bits_per_sample(pixbuf) == 8);
  g_assert (gdk_pixbuf_get_has_alpha(pixbuf));
  g_assert (n_channels == 4);

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      int rowstride = gdk_pixbuf_get_rowstride(pixbuf);
      guchar *pixels = gdk_pixbuf_get_pixels(pixbuf);

      guchar *p = pixels + y * rowstride + x * n_channels;
      guchar average = p[0];
      if (average > final_t)
        gtk_put_pixel(pixbuf, x, y, 255,255,255, p[3]);
      else
        gtk_put_pixel(pixbuf, x, y, 0, 0, 0, p[3]);
    }
  }

}
