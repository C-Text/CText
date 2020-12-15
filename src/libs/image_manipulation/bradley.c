#include <stdlib.h>
#include "bradley.h"
#include "pixel_operations.h"

void gtk_bradley(int t,
                     int s,
                     GdkPixbuf *pixbuf) {
  int n_channels = gdk_pixbuf_get_n_channels(pixbuf);
  int w = gdk_pixbuf_get_width(pixbuf);
  int h = gdk_pixbuf_get_height(pixbuf);
  int rowstride = gdk_pixbuf_get_rowstride(pixbuf);

  unsigned int sum, count;
  unsigned int x1, x2, y1, y2;
  unsigned int *intImg = malloc(sizeof(unsigned int) * w * h);

  for (int i = 0; i < w; i++) {
    sum = 0;
    for (int j = 0; j < h; j++) {
      guchar *pixels = gdk_pixbuf_get_pixels(pixbuf);
      guchar *p = pixels + j * rowstride + i * n_channels;
      sum += p[0];
      if (i == 0)
        intImg[i * h + j] = sum;
      else
        intImg[i * h + j] = intImg[(i - 1) * h + j] + sum;
    }
  }

  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      if (i > s / 2)
        x1 = i - s / 2;
      else
        x1 = 1;
      if (i + s / 2 >= w)
        x2 = w - 1;
      else
        x2 = i + s / 2;
      if (j > s / 2)
        y1 = j - s / 2;
      else
        y1 = h;
      if (j + s / 2 >= h)
        y2 = h - 1;
      else
        y2 = j + s / 2;

      count = (x2 - x1) * (y2 - y1);
      sum = intImg[x2 * h + y2] - intImg[x2 * h + (y1 - 1)] - intImg[(x1 -
          1) * h + y2] + intImg[(x1 - 1) * h + (y1 - 1)];

      guchar *pixels = gdk_pixbuf_get_pixels(pixbuf);
      guchar *p = pixels + j * rowstride + i * n_channels;
      guchar new_p = (p[0] * count <= sum * (100 - t) / 100) ? 0 : 255;
      // Black = 1 => 0 in rgb
      gtk_put_pixel(pixbuf, i, j, new_p, new_p, new_p, 255);
    }
  }
  free(intImg);
}