#include "filter.h"
#include "pixel_operations.h"
#include "SDL/SDL.h"

/**
 * Applies a convolution matrix to the whole image
 * @param convolMat: convolution matrix we want to apply
 * @param max: width of the convolution matrix
 * @param image_surface: the loaded image
 */
void applyConvol(const int *convolMat, int max, GdkPixbuf *pixbuf) {
  int n_channels = gdk_pixbuf_get_n_channels(pixbuf);
  int w = gdk_pixbuf_get_width(pixbuf);
  int h = gdk_pixbuf_get_height(pixbuf);
  int rowstride = gdk_pixbuf_get_rowstride(pixbuf);

  GdkPixbuf *tmp = gdk_pixbuf_copy(pixbuf);

  for (int x = max / 2; x < w - (max / 2); x++) {
    for (int y = max / 2; y < h - (max / 2); y++) {
      Uint8 R = 0, G = 0, B = 0;
      int iR = (int) R;
      int iG = (int) G;
      int iB = (int) B;

      for (int i = -(max / 2); i <= (max / 2); i++)  //courses current pixels
        // and neighbours
      {
        for (int j = -(max / 2); j <= (max / 2); j++) {
          //get the value of surrounding pixel
          guchar *pixels = gdk_pixbuf_get_pixels(tmp);
          guchar *p = pixels + j * rowstride + i * n_channels;

          int index = (i + max / 2) * max + (j + max / 2);

          int ir = (int) p[0];
          int ig = (int) p[1];
          int ib = (int) p[2];

          ir = (ir * convolMat[index]);//matrixSum;
          ig = (ig * convolMat[index]);//matrixSum;
          ib = (ib * convolMat[index]);//matrixSum;

          iR += ir;
          iG += ig;
          iB += ib;
        }
      }

      //replace the old pixel value by the fresh one
      iR = iR / (max * max) * 2;
      iG = iG / (max * max) * 2;
      iB = iB / (max * max) * 2;

      if (iR > 254)
        iR = 254;
      else if (iR < 0)
        iR = 0;

      if (iG > 254)
        iG = 254;
      else if (iG < 0)
        iG = 0;

      if (iB > 254)
        iB = 254;
      if (iB < 0)
        iB = 0;

      R = (Uint8) iR;
      G = (Uint8) iG;
      B = (Uint8) iB;

      gtk_put_pixel(pixbuf, x, y, R, G, B, 255);
    }
  }
  g_free(tmp);
}

/**
 * Applies a median filter to the whole image
 * @param image_surface: the loaded image
 * @param max: the width of the median filter
 * @return the new image_surface
 */
void medianFilter(GdkPixbuf *pixbuf, int max) {
  int n_channels = gdk_pixbuf_get_n_channels(pixbuf);
  int w = gdk_pixbuf_get_width(pixbuf);
  int h = gdk_pixbuf_get_height(pixbuf);
  int rowstride = gdk_pixbuf_get_rowstride(pixbuf);

  GdkPixbuf *tmp = gdk_pixbuf_copy(pixbuf);
  guchar *pixels = gdk_pixbuf_get_pixels(tmp);

  for (int x = max / 2; x < (w - (max / 2)); x++)  //traverese the image
  {
    for (int y = max / 2; y < (h - (max / 2)); y++) {
      guchar **list = calloc(max * max, sizeof(guchar));
      guchar *pix;

      int index = 0;

      for (int i = -(max / 2); i <= (max / 2); i++)  //for each pixel
      {
        for (int j = -(max / 2); j <= (max / 2); j++) {
          pix = pixels + j * rowstride + i * n_channels;

          list[index] = pix;
          index++;
        }
      }

      //sort list
      for (int k = 0; k < (max * max); k++) {
        for (int m = 0; m < (k - 1); m++) {
          if (list[m + 1] < list[m]) {
            guchar *swp = list[m];
            list[m] = list[m + 1];
            list[m + 1] = swp;
          }
        }
      }
      //replace the old pixel value by the median
      guchar *elm = list[(max * max) / 2];
      gtk_put_pixel(pixbuf, x, y, elm[0], elm[1], elm[2], 255);
      free(list);
    }
  }
  g_free(tmp);
}

/**
 * Applies a median filter to the whole image matrix
 * @param matrix: The image matrix
 * @param max: The width of the median filter applied
 * @param w: The width of the matrix
 * @param h: The height od the matrix
 */
void medianFilterMatrix(int matrix[], int max, int w, int h) {
  int *tmp = matrix;

  for (int x = max / 2; x < w - (max / 2); x++)  //traverese the image
  {
    for (int y = max / 2; y < h - (max / 2); y++) {
      int *list = calloc(max * max, sizeof(int));
      int pix;

      int index = 0;

      for (int i = -(max / 2); i <= (max / 2); i++)  //for each pixel
      {
        for (int j = -(max / 2); j <= (max / 2); j++) {
          pix = tmp[(x + i) * max + y + j];

          list[index] = pix;
          index++;
        }
      }

      //sort list
      for (int k = 0; k < (max * max); k++) {
        for (int m = 0; m < (k - 1); m++) {
          if (list[m + 1] < list[m]) {
            int swp = list[m];
            list[m] = list[m + 1];
            list[m + 1] = swp;
          }
        }
      }
      //replace the old pixel value by the median
      matrix[x * w + y] = list[(max * max) / 2];
    }
  }
}