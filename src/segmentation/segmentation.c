#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


typedef struct Block
{
    size_t upperx;
    size_t uppery;
    size_t lowerx;
    size_t lowery;
}Block;

typedef struct BiBlock
{
    Block* upper;
    Block* lower;
}BiBlock;

typedef struct Coords
{
    size_t x;
    size_t y;
}Coords;

typedef struct Node
{
    
    Block* block;

    struct Node* left;
    struct Node* right;
}Node;

Coords* newcoords()
{
    Coords* coords = (Coords*)malloc(sizeof(struct Coords));

    coords->x = 0;
    coords->y = 0; 
    return coords;
}

Block* newblock(size_t upperx,size_t uppery,size_t lowerx,size_t lowery)
{
    Block* block = (Block*)malloc(sizeof(struct Block));

    block->upperx = upperx;
    block->uppery = uppery; 
    block->lowerx = lowerx;
    block->lowery = lowery;
    return block;
}

BiBlock* newbiblock(Block* upper,Block* lower)
{
    BiBlock* biblock = (BiBlock*)malloc(sizeof(struct BiBlock));
    biblock->upper = upper;
    biblock->lower = lower;
    return biblock;
}

struct Node* newNode() 
{ 
    // Allocate memory for new node  
    struct Node* node = (struct Node*)malloc(sizeof(struct Node)); 

    // Initialize block as null
    node->block = NULL;
    // Initialize left and right children as NULL 
    node->left = NULL; 
    node->right = NULL; 
    return(node); 
}
BiBlock* Xcut(Block* block,Coords* size,unsigned char M[size->x][size->y]);
BiBlock* Ycut(Block* block,Coords* size,unsigned char M[size->x][size->y]);

Node* __buildtreeX(Node* tree, Coords* size,unsigned char M[size->x][size->y]);
Node* __buildtreeY(Node* tree, Coords* size,unsigned char M[size->x][size->y]);

void printB(Block* block,Coords* coords, unsigned char M[coords->x][coords->y]);

void printM(Coords* coords,
            unsigned char M[coords->x][coords->y]);
int isblack(size_t x, size_t y ,
            Coords* coords,
            unsigned char M[coords->x][coords->y]);
Coords* optiM(Coords* Msize,
            unsigned char M[Msize->y][Msize->x],
            unsigned char opti[Msize->y/12+1][Msize->x/12+1]);

void seg(Coords* size,unsigned char M[size->x][size->y]);



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


/**
 * 
 * testing function that generates a random binarized image to experiment with histogram
 * genaration(sadly it appear to be sligthly broken at the moment)
 * 
 */

void generate( size_t sizex, size_t sizey,unsigned char image[sizey][sizex]) 
{
    srand((unsigned int)time(NULL));
    size_t i, j;
    for ( i=1; i < sizey-1; ++i) 
    {
        for ( j=1; j < sizex-1; j++) 
        {
            image[i][j] = rand() % 2;

        }
    } 

    for (size_t y = 1; y < sizex-1; y++)
    {
        image[0][y]=0;
        image[sizey-1][y]=0;
    }
} 


int main() {
  size_t sizex = 60;
  size_t sizey = 60;
  unsigned char image[sizey][sizex];

  //unsigned char image[][4]={ { 0,1,0,1 } , { 1,1,1,1 } ,{ 1,0,0,0 }};

  //unsigned int test[60];
  //unsigned int ptest = test;

  generate(sizex, sizey, image);
  line_seg(sizex, sizey, image);

  //printf("%s\n",ext);

  return 0;
}


/**
 * 
 * Modify array into a histogram of a bit multidimensionnal array.
 * horizontal lecture.
 * @author matthieu
 * @param img the image analysed
 * @param ext empty array that will be modified
 * @param sizex horizontal size of the treated image
 * @param sizey verticale size of the treated image
 * 
 */
void hori_histo(unsigned int ext[],
                size_t sizex,
                size_t sizey,
                unsigned char img[sizey][sizex]) {

  for (unsigned int y = 0; y < sizey; y++) {
    ext[y] = 0;
    for (unsigned int x = 0; x < sizex; x++) {
      ext[y] += img[y][x];
      //printf("%u",img[y][x]);
    }
    //printf("\n");
  }
}

/**
 * 
 * Uses hori_histo's horizontal histogram to segment different lines in img,
 * then calls word_seg for each segmented line.
 * @author matthieu
 * @param img analysed image
 * @param sizex horizontal size of img
 * @param sizey verticale size of img
 * 
 */
void line_seg(size_t sizex, size_t sizey, unsigned char img[sizey][sizex]) {
  unsigned int ho_histo[sizey];
  hori_histo(ho_histo, sizex, sizey, img);

  size_t y = 0;
  size_t upper = 0;
  size_t lower = 0;
  while (y < sizey) {
    if (ho_histo[y] != 0) {
      upper = y;
      while (ho_histo[y] != 0) {
        y += 1;
      }
      lower = y - 1;
      word_seg(upper, lower, sizex, sizey, img);
    }

    y += 1;
  }
  //printf("upper = %lu \nladder = %lu\n",upper,lower);
  /*
  for(int i =0; i< 60; i++)
  {
      for (unsigned int y = 0; y< ho_histo[i]; y++)
      {
          printf("|");
      }
      //printf("%u\n",ho_histo[i]);
      printf("\n");
  }
  */
}

/**
 * 
 * Uses vert_histo vertical histogram to segment words in a line.
 * letter_seg is called for each segmented word.
 * @author matthieu
 * @param img analysed image
 * @param sizex horizontal size of img
 * @param sizey verticale size of img
 * @param upper limit the histogram to a precise max in img[][]
 * @param lower limit the histogram to a precise min in img[][]
 * 
 */
void word_seg(size_t upper,
              size_t lower,
              size_t sizex,
              size_t sizey,
              unsigned char img[sizey][sizex]) {
  unsigned int ver_histo[sizex];
  vert_histo(upper, lower, ver_histo, sizex, sizey, img, 0, sizex);

  size_t x = 0;
  size_t left = 0;
  size_t right = 0;
  int space_finder;
  int nbspace;
  while (x < sizex) {
    if (ver_histo[x] != 0) {
      left = x;
      space_finder = 1;
      nbspace = 0;
      while ((space_finder) && (x < sizex)) {
        if (ver_histo[x] == 0) {
          nbspace += 1;
          if (nbspace > 4) {
            space_finder = 0;
            right = x - nbspace;
            //printf("%lu,%lu",left,right);
          }
        }
        x += 1;
      }
    } else {
      x += 1;
    }
  }
  printf("%lu,%lu\n", left, right);

  /*
  for(size_t i =0; i< sizex; i++)
  {

      for (unsigned int y = 0; y < ver_histo[i]; y++)
      {
          printf("|");
      }

      printf("histo(%lu) = %u\n",i,ver_histo[i]);
      //printf("\n");
  }
  */

}

/**
 * 
 * Modify array into a histogram of a bit multidimensionnal array.
 * vertical lecture
 * @author matthieu
 * @param img the image analysed
 * @param ext empty array that will be modified
 * @param sizex horizontal size of img
 * @param sizey verticale size of img
 * @param upper limit the histogram to a precise max in img[][]
 * @param lower limit the histogram to a precise min in img[][]
 * @param left specify from which indexe to start histogram
 * @param right specify from which indexe to end histogram
 * 
 */
void vert_histo(size_t upper,
                size_t lower,
                unsigned int ext[],
                size_t sizex,
                size_t sizey,
                unsigned char img[sizey][sizex],
                size_t left,
                size_t right) {
  size_t x, y;
  for (x = left; x < right; x++) {
    ext[x] = 0;
    //printf("ext(%lu) = %u\n",x,ext[x]);
    for (y = upper; y < lower; y++) {

      ext[x] += img[y][x];
      //printf("%u",img[y][x]);
    }
    //printf("\n");
    //printf("ext(%lu) = %u\n",x,ext[x]);
  }
}

/**
 * 
 * Uses vert_histo vertical histogram to segment letters in a word.
 * the neural network is called for each segmented letter to analyse them.
 * @author matthieu
 * @param img analysed image
 * @param sizex horizontal size of img
 * @param sizey verticale size of img
 * @param upper limit the histogram to a precise max in img[][]
 * @param lower limit the histogram to a precise min in img[][]
 * @param left specify from which indexe to start each word
 * @param right specify from which indexe to end each word
 * 
 */
void letter_seg(size_t upper,
                size_t lower,
                size_t left,
                size_t right,
                size_t sizex,
                size_t sizey,
                unsigned char img[sizey][sizex]) {
  unsigned int word_histo[right - left + 1];
  vert_histo(upper, lower, word_histo, sizex, sizey, img, left, right);

  size_t x = 0;
  size_t y = 0;
  while (x < right - left + 1) {
    if (word_histo[x] != 0) {
      y = x;
      while (word_histo[y] != 0) {
        x += 1;
      }
      /* insert call to neural network */
    } else {
      x += 1;
    }

  }
}



void printM(Coords* size, unsigned char M[size->x][size->y])
{
    size_t x,y;
    for(y=0;y<size->y;y++)
    {
        printf("|");
        for(x=0;x<size->x;x++)
        {
            printf("%i|",M[y][x]);
        }
        printf("\n");
    }
}

void printB(Block* block,Coords* size, unsigned char M[size->x][size->y])
{
    size_t x,y;
    printf("****************************\n");
    for(y=block->uppery;y<=block->lowery;y++)
    {
        printf("|");
        for(x=block->upperx;x<=block->lowerx;x++)
        {
            printf("%i|",M[y][x]);
        }
        printf("\n");
    }
}


Coords* optiM(Coords* Msize,
          unsigned char M[Msize->y][Msize->x],
          unsigned char opti[Msize->y/12+1][Msize->x/12+1])
{
    Coords* OPMsize = newcoords();
    OPMsize->x = Msize->x/12+1;
    OPMsize->y = Msize->y/12+1;
    size_t i,j;
    for (j=0; j<OPMsize->y; j++)
    {
        for(i=0; i<OPMsize->x; i++)
        {
            opti[j][i]=isblack(i*12,j*12,Msize,M);
        }
    }
    return OPMsize;
}

int isblack(size_t x, size_t y ,
            Coords* coords,
            unsigned char M[coords->x][coords->y])
{
    int ext = 0;
    size_t i = 1, j = 1, tmp = 3; 
    while ((!ext && (y+j<coords->y)) &&(j<12))
    {
        if(tmp==1)
        {
            i=3;
            tmp = 3;
        }
        else
        {
            i=1;
            tmp = 1;
        }
        while ((!ext && (x+i<coords->x)) && (i<12))
        {
            if (M[j+y][i+x]==1)
            {
                ext = 1;
            }
            i+=4;
        }
        j+=2;
    }

    return ext;
}

BiBlock* Xcut(Block* block,Coords* size,unsigned char M[size->x][size->y])
{
    size_t i=block->upperx,j=block->uppery;
    int first = 0;
    int second = 0;
    int sum=0;
    Block* block1 = NULL;
    Block* block2 = NULL;
    while((i<=block->lowerx)&&(!second))
    {
        j=block->uppery;
        sum=0;
        while((j<=block->lowery)&&(first==1))
        {
            if(M[j][i]==1)
            {
                sum += 1;
                break;
            }
            j+=1;
        }
        if((sum==0)&&(first==1))
        {
            block1->lowerx = i-1;
            first=2;
        }
   
        while((j<=block->lowery)&&(first==0))
        {
            if(M[j][i]==1)
            {
                first = 1;
                block1 = newblock(i,block->uppery,block->lowerx,block->lowery);
            }
            j+=1;
        }
        
        while(((j<=block->lowery)&&(!second))&&(first==2))
        {
            if(M[j][i]==1)
            {
                second = 1;
                block2 = newblock(i,block->uppery,block->lowerx,block->lowery);
            }
            j+=1;
        }      
        i+=1;
    }
    BiBlock* ext = newbiblock(block1,block2);
    return ext;
}



BiBlock* Ycut(Block* block,Coords* size,unsigned char M[size->x][size->y])
{
    size_t i=block->upperx,j=block->uppery;
    int first = 0;
    int second = 0;
    int sum=0;
    Block* block1 = NULL;
    Block* block2 = NULL;
    while((j<=block->lowery)&&(!second))
    {
        i=block->upperx;
        sum=0;
        while((i<=block->lowerx)&&(first==1))
        {
            if(M[j][i]==1)
            {
                sum += 1;
                break;
            }
            i+=1;
        }
        if((sum==0)&&(first==1))
        {
            block1->lowery = j-1;
            first=2;
        }
   
        while((i<=block->lowerx)&&(first==0))
        {
            if(M[j][i]==1)
            {
                first = 1;
                block1 = newblock(block->upperx,j,block->lowerx,block->lowery);
            }
            i+=1;
        }
        
        while(((i<=block->lowerx)&&(!second))&&(first==2))
        {
            if(M[j][i]==1)
            {
                second = 1;
                block2 = newblock(block->upperx,j,block->lowerx,block->lowery);
            }
            i+=1;
        }      
        j+=1;
    }
    BiBlock* ext = newbiblock(block1,block2);
    return ext;
}


Node* __buildtreeX(Node* tree, Coords* size,unsigned char M[size->x][size->y])
{
    
    BiBlock* children = Xcut(tree->block,size,M);
    if(children->lower!=NULL)
    {
        tree->left = newNode();
        tree->right = newNode();
        tree->left->block = children->upper;
        tree->right->block = children->lower;
        tree->left = __buildtreeY(tree->left,size,M);
        tree->right = __buildtreeY(tree->right,size,M);
        return tree;
    }
    else
    {
        tree->block =children->upper;
        children = Ycut(tree->block,size,M);
        if (children->lower!=NULL)
        {
            tree->left = newNode();
            tree->right = newNode();
            tree->left->block = children->upper;
            tree->right->block = children->lower;
            tree->left = __buildtreeX(tree->left,size,M);
            tree->right = __buildtreeX(tree->right,size,M);
        }
        else
        {
            tree->block =children->upper;
        }
        

        ///////////////////////////////////////////////
        printB(tree->block,size,M);
        printf("leaf\n");
        ///////////////////////////////////////////////
        return tree;
    }
    
}

Node* __buildtreeY(Node* tree, Coords* size,unsigned char M[size->x][size->y])
{
    BiBlock* children = Ycut(tree->block,size,M);
    if(children->lower!=NULL)
    {
        tree->left = newNode();
        tree->right = newNode();
        tree->left->block = children->upper;
        tree->right->block = children->lower;
        tree->left = __buildtreeX(tree->left,size,M);
        tree->right = __buildtreeX(tree->right,size,M);
        return tree;
    }
    else
    {
        tree->block =children->upper;
        children = Xcut(tree->block,size,M);
        if (children->lower!=NULL)
        {
            tree->left = newNode();
            tree->right = newNode();
            tree->left->block = children->upper;
            tree->right->block = children->lower;
            tree->left = __buildtreeY(tree->left,size,M);
            tree->right = __buildtreeY(tree->right,size,M);
        }
        else
        {
            tree->block =children->upper;
        }
        
        ///////////////////////////////////////////////
        printB(tree->block,size,M);
        printf("leaf\n");
        ///////////////////////////////////////////////
        return tree;
    }
    
}


void seg(Coords* size,unsigned char M[size->x][size->y])
{
    Node* root = newNode();
    root->block = newblock(0,0,size->x-1,size->y-1);
    root = __buildtreeX(root,size,M);
    printB(root->block,size,M);
}