#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "../neural_network/neuralnetwork.h"

typedef struct Block {
  size_t upperx;
  size_t uppery;
  size_t lowerx;
  size_t lowery;
  char *M;
} Block;

typedef struct BiBlock {
  Block *upper;
  Block *lower;
} BiBlock;

typedef struct Coords {
  size_t x;
  size_t y;
} Coords;

typedef struct TreeNode {

  Block *block;

  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

TreeNode *seg(Coords *size, unsigned char M[size->x][size->y]);

char *concat(char *str1, char *link, char *str2);
char *concat2(char *str1, char *str2);
void freetree(TreeNode *tree);
void fileout(char *str);

void printB(Block *block,
            Coords *coords,
            unsigned char M[coords->x][coords->y]);
void printM(Coords *coords,
            unsigned char M[coords->x][coords->y]);
BiBlock *Xcut(Block *block, Coords *size, unsigned char M[size->x][size->y]);
BiBlock *Ycut(Block *block, Coords *size, unsigned char M[size->x][size->y]);

TreeNode *__buildtreeX(TreeNode *tree,
                       Coords *size,
                       unsigned char M[size->x][size->y],
                       Coords *Osize,
                       unsigned char opti[Osize->x][Osize->y]);
TreeNode *__buildtreeY(TreeNode *tree,
                       Coords *size,
                       unsigned char M[size->x][size->y],
                       Coords *Osize,
                       unsigned char opti[Osize->x][Osize->y]);

void printB(Block *block,
            Coords *coords,
            unsigned char M[coords->x][coords->y]);

void printM(Coords *coords,
            unsigned char M[coords->x][coords->y]);
int isblack(size_t x, size_t y,
            Coords *coords,
            unsigned char M[coords->x][coords->y]);
void optiM(Coords *Msize,
           Coords *Osize,
           unsigned char M[Msize->y][Msize->x],
           unsigned char opti[Osize->y][Osize->x]);

void printcoords(Block *block);

void block_to_mat(Block *block,
                  Coords *size,
                  unsigned char M[size->x][size->y],
                  Coords *sizeMat,
                  unsigned char Mat[sizeMat->x][sizeMat->y]);

void hori_histo(unsigned int ext[],
                Block *block,
                size_t histolen,
                Coords *size,
                unsigned char img[size->y][size->x]);
void vert_histo(Block *block,
                size_t histolen,
                unsigned int ext[],
                Coords *size,
                unsigned char img[size->y][size->x]);
void letter_seg(Block *block,
                Coords *size,
                unsigned char img[size->y][size->x]);
void word_seg(Block *block,
              Coords *size,
              unsigned char img[size->y][size->x]);
void line_seg(Block *block,
              Coords *size,
              unsigned char img[size->y][size->x]);

#endif