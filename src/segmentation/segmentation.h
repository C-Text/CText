#ifndef SEGMENTATION_H
#define SEGMENTATION_H
#include <stdlib.h>

void printB(Block* block,
            Coords* coords,
            unsigned char M[coords->x][coords->y]);
void printM(Coords* coords,
            unsigned char M[coords->x][coords->y]);
Node* seg(Coords* size,unsigned char M[size->x][size->y]);
void freetree(Node* tree);
void hori_histo(unsigned int ext[],
                Block* block,
                size_t histolen,
                Coords* size,
                unsigned char img[size->y][size->x]);
void vert_histo(Block* block,
                size_t histolen,
                unsigned int ext[],
                Coords* size,
                unsigned char img[size->y][size->x]);
void letter_seg(Block* block,
                Coords* size,
                unsigned char img[size->y][size->x]);
void word_seg(Block* block,
              Coords* size,
              unsigned char img[size->y][size->x]);
void line_seg(Block* block,
              Coords* size,
              unsigned char img[size->y][size->x]);

#endif