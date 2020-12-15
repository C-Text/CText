/**
  *Authors: Lise Giraud and Valentin Chassignol
  *Date: 14/12/2020
  *File's name: otsu.h
  */

#ifndef CTEXT_SRC_PREPROCESSING_OTSU_H_
#define CTEXT_SRC_PREPROCESSING_OTSU_H_

#include <SDL/SDL.h>

/**
 *Calculation of the median in the histogram between start and end values.
 *
 *@param histo is the histogram of grayscale in a given image.
 *@param start is where to start to calculate the median.
 *@param end is where to end to calculate the median.
 *
 *@return the median value between start and end in the histogram.
 */
int mean(unsigned int *histo, int start, int end);

/**
 *Calculate the sum between start and end (end excluded) of the histogram.
 *
 *@param *histo is the histogram of grayscale in a given image.
 *@param start is where to start the calculus.
 *@param end is where to end the calculus (end is excluded).
 *
 *@return the sum of all the values between start and end.
 */
int sum(unsigned int *histo, int start, int end);

/**
 *Make the grayscale histogram of a given image.
 *
 *@param histo is the histogram to complete.
 *@param w is the weight of the image.
 *@param h is the height of the image.
 *@param image_surface is the given image to make histogram.
 */
void histo(unsigned int histo[256], GdkPixbuf *pixbuf);

/**
 *Use the otsu's method to calculate the optimal threshold of a grayscale image.
 *
 *@param histo is the histogram of grayscale of the image.
 *@param w is the weight of the image.
 *@param h is the height of the image.
 *
 *@return the optimal threshold.
 */
int otsu(unsigned int histo[256], unsigned w,unsigned h);

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
                  int final_t, SDL_Surface *image_surface);

/**
 * Convert the given image into binary image using the functions below.
 *
 * @param pixbuf is the given image to convert into a binary image.
 */

void gtk_otsu_binarization(GdkPixbuf *pixbuf);

#endif //CTEXT_SRC_PREPROCESSING_OTSU_H_