#ifndef CTEXT_SEGMENTATION_H
#define CTEXT_SEGMENTATION_H

#include <stdlib.h>

void hori_histo(unsigned int ext[],
                size_t sizex,
                size_t sizey,
                unsigned char img[sizey][sizex]);
void vert_histo(size_t upper,
                size_t lower,
                unsigned int ext[],
                size_t sizex,
                size_t sizey,
                unsigned char img[sizey][sizex],
                size_t left,
                size_t right);
void letter_seg(size_t upper,
                size_t lower,
                size_t left,
                size_t right,
                size_t sizex,
                size_t sizey,
                unsigned char img[sizey][sizex]);
void word_seg(size_t upper,
              size_t lower,
              size_t sizex,
              size_t sizey,
              unsigned char img[sizey][sizex]);
void line_seg(size_t sizex, size_t sizey, unsigned char img[sizey][sizex]);

#endif