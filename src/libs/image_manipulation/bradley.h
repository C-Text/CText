/*
 *Author: Lise Giraud
 * Date : 14/12/2020
 * File's name: bradley.h
 */

#ifndef CTEXT_SRC_LIBS_IMAGE_MANIPULATION_BRADLEY_H_
#define CTEXT_SRC_LIBS_IMAGE_MANIPULATION_BRADLEY_H_

#include <gdk-pixbuf/gdk-pixbuf.h>

/*
 * Convert grayscale image to a binary image.
 *
 * @param t is a value given by the user. It is used to determine if a
 * pixel is either black or white.
 * @param s is a value given by the user. It determines the number of pixel used to compare the
 * current pixel value with the average of its neighboor.
 * @param pixbuf is the image to convert into binary image.
 */

void gtk_bradley(int t,
                    int s,
                    GdkPixbuf *pixbuf);

#endif //CTEXT_SRC_LIBS_IMAGE_MANIPULATION_BRADLEY_H_
