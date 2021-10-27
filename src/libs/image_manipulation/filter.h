#ifndef CTEXT_SRC_LIBS_IMAGE_MANIPULATION_FILTER_H_
#define CTEXT_SRC_LIBS_IMAGE_MANIPULATION_FILTER_H_

#include <gdk-pixbuf/gdk-pixbuf.h>

void applyConvol(const int *convolMat, int max, GdkPixbuf *pixbuf);

void medianFilter(GdkPixbuf *pixbuf, int max);

void medianFilterMatrix(int matrix[], int max, int w, int h);

#endif //CTEXT_SRC_LIBS_IMAGE_MANIPULATION_FILTER_H_
