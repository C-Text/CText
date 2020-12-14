#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <err.h>

typedef struct Block
{
    size_t upperx;
    size_t uppery;
    size_t lowerx;
    size_t lowery;
    char* M;
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

char* concat(char *str1,char *link ,char *str2);
char* concat2(char *str1,char *str2);
void freetree(Node* tree);

/**
 * 
 * initialize a new coords structure to modify later
 * @author matthieu
 */
Coords* newcoords()
{
    Coords* coords = (Coords*)malloc(sizeof(struct Coords));

    coords->x = 0;
    coords->y = 0; 
    return coords;
}

/**
 * 
 * initialize a new block, a block is a rectangle inside a matrix,
 * thus to create one, two point of coordonate(x,y) must be given.
 * @author matthieu
 * @param upperx x coordonate for the first point of the block
 * @param uppery y coordonate for the first point of the block
 * @param lowerx x coordonate for the second point of the block
 * @param lowery y coordonate for the second point of the block
 * @return the pointer to the newly created block
 * 
 */
Block* newblock(size_t upperx,size_t uppery,size_t lowerx,size_t lowery)
{
    Block* block = (Block*)malloc(sizeof(struct Block));

    block->upperx = upperx;
    block->uppery = uppery; 
    block->lowerx = lowerx;
    block->lowery = lowery;
    block->M = NULL;

    return block;
}

/**
 * 
 * initialize a new biblock, basically a tuple structure for block structure
 * @author matthieu
 * @param upper first block
 * @param lower second block
 * @return the pointer to the newly created biblock
 * 
 */
BiBlock* newbiblock(Block* upper,Block* lower)
{
    BiBlock* biblock = (BiBlock*)malloc(sizeof(struct BiBlock));
    biblock->upper = upper;
    biblock->lower = lower;
    return biblock;
}

/**
 * 
 * initialize a new Node structure(binary tree) 
 * with both children nodes initialized to NULL.
 * data contain within the node is a pointer to a block structure
 * also initialised to NULL.
 * @author matthieu
 */
Node* newNode() 
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

Node* __buildtreeX(Node* tree,
                   Coords* size,
                   unsigned char M[size->x][size->y],
                   Coords* Osize,
                   unsigned char opti[Osize->x][Osize->y]);
Node* __buildtreeY(Node* tree,
                   Coords* size,
                   unsigned char M[size->x][size->y],
                   Coords* Osize,
                   unsigned char opti[Osize->x][Osize->y]);

void printB(Block* block,Coords* coords, unsigned char M[coords->x][coords->y]);

void printM(Coords* coords,
            unsigned char M[coords->x][coords->y]);
int isblack(size_t x, size_t y ,
            Coords* coords,
            unsigned char M[coords->x][coords->y]);
void optiM(Coords* Msize,
            Coords* Osize,
            unsigned char M[Msize->y][Msize->x],
            unsigned char opti[Osize->y][Osize->x]);

Node* seg(Coords* size,unsigned char M[size->x][size->y]);

void printcoords(Block* block);

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


int main() 
{
    //size_t sizex = 60;
    //size_t sizey = 60;
    //unsigned char image[sizey][sizex];

    //unsigned char image[][4]={ { 0,1,0,1 } , { 1,1,1,1 } ,{ 1,0,0,0 }};

    //unsigned int test[60];
    //unsigned int ptest = test;

    //generate(sizex, sizey, image);
    //line_seg(sizex, sizey, image);

    //printf("%s\n",ext);
    /*
    unsigned char image[][14] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,1,1,1,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,1,0,0,0,1,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,1,1,1,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    */
    /*
    unsigned char image[][14] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {0,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,1,1,1,1,1,1,1},
        {0,0,0,1,1,1,1,1,1,1,1,1,1,1},
        {0,0,0,0,1,1,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,1,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,0,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,1}
    };
    */
   /*
    unsigned char image[][14] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,0,1,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,0,0,0,0,0,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,0,1,0,1,0,0,0,1,0,0,0,0,0},
        {1,1,0,1,0,0,0,1,1,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    Coords* matsize = newcoords();
    matsize->x = 14;
    matsize->y = 14;
    printM(matsize,image);
    Block* test = newblock(0,0,matsize->x-1,matsize->y-1);
    */
    //seg(matsize,image);

    /*
    char i = 14/12+1;
    unsigned char opi[i][i];
    Coords* opmsize = optiM(matsize,image,opi);
    printM(opmsize,opi);
    */
    
    //word_seg(test,matsize,image);
    //line_seg(test,matsize,image);
    /*
    test->M = "l";
    char* ah = "ah";
    char* link = "";
    test->M = concat(test->M,link,ah);
    */
    //printf("%s\n",test->M);
  return 0;
}


/**
 * 
 * Modify array into a histogram of a bit multidimensionnal array.
 * horizontal lecture.
 * @author matthieu
 * @param img the image analysed.
 * @param ext empty array that will be modified.
 * @param size struct containing the size of img (x,y).
 * @param histolen size of the histogram .
 * @param block contains the coordonates that needs to be processed
 * by the fonction.
 */
void hori_histo(unsigned int ext[],
                Block* block,
                size_t histolen,
                Coords* size,
                unsigned char img[size->y][size->x])
{

  for (unsigned int y = 0; y < histolen; y++) 
  {
    ext[y] = 0;
    for (unsigned int x = block->upperx; x <= block->lowerx; x++) 
    {
      ext[y] += img[y+block->uppery][x];
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
 * @param block struct that contains the coordonates of the rectangle ara 
 * that needs line segmentation
 * @param size struct that contains the size (x,y) of img[y][x]
 * 
 */
void line_seg(Block* block,Coords* size, unsigned char img[size->y][size->x])
{
    /*
    printB(block,size,img);
    printf("line\n");
    */
    size_t histolen = block->lowery - block->uppery+1;
    unsigned int ho_histo[histolen];
    hori_histo(ho_histo,block,histolen,size,img);
    char* ext ="";
    char* link ="\n";

    size_t y = block->uppery;
    Block* sousblock = newblock(block->upperx,block->uppery,
    block->lowerx,block->lowery);

    while (y < block->lowery) 
    {
        if (ho_histo[y] != 0) 
        {
            sousblock->uppery = y;
            while ((ho_histo[y] != 0)&&(y < block->lowery))
            {
                y += 1;
            }
            if(y < block->lowery)
            {
                y-=1;
            }
            sousblock->lowery = y;

            /////////////////////////////////////////
            /*
            printB(sousblock,size,img);
            printcoords(sousblock);
            printf("L_seg histolen=%lu\n",histolen);
            */
            /////////////////////////////////////////
            word_seg(sousblock, size, img);
            if(strlen(ext)==0)
            {
                ext = concat2(ext,sousblock->M);
            }
            else
            {
                
                ext = concat(ext,link,sousblock->M);
            }
            

        }
        y += 1;
    }
    ext = concat(ext,link,link);
    block->M = ext;
    free(sousblock->M);
    free(sousblock);


    /*
    for(size_t i =0; i< histolen; i++)
    {
        for (unsigned int y = 0; y< ho_histo[i]; y++)
        {
            printf("|");
        }
        printf("%u",ho_histo[i]);
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
 * @param block contains the coordonates that needs to be processed
 * by the fonction.
 * @param size struct that contains the size (x,y) of img[y][x]
 */
void word_seg(Block* block,
              Coords* size,
              unsigned char img[size->y][size->x])
{
    /*
    printB(block,size,img);
    printf("word\n");
    */

    size_t histolen = block->lowerx - block->upperx+1;
    unsigned int ver_histo[histolen];
    vert_histo(block,histolen,ver_histo,size,img);

    char* ext ="";
    char* link =" ";
    
    Block* sousblock = newblock(block->upperx,block->uppery,
    block->lowerx,block->lowery);

    size_t x = 0;
    size_t height = block->lowery - block->uppery +1;
    int space_finder;
    int nbspace;

    while (x < histolen) 
    {
        //printf("x=%lu",x);
        if (ver_histo[x] != 0) 
        {

            sousblock->upperx = x+block->upperx;
            space_finder = 1;
            nbspace = 0;
            while ((space_finder) && (x < histolen)) 
            {
                //printf(" x'=%lu\n",x);
                if (ver_histo[x] == 0) 
                {
                    nbspace += 1;
                    if (height/nbspace <= 4) 
                    {
                        space_finder = 0;
                        sousblock->lowerx =block->upperx + x - nbspace;

                        /////////////////////////////////////////
                        /*
                        printB(sousblock,size,img);
                        printcoords(sousblock);
                        printf("w_seg histolen=%lu\n",histolen);
                        */
                        /////////////////////////////////////////

                        letter_seg(sousblock,size,img);
                        if(strlen(ext)==0)
                        {
                            ext = concat2(ext,sousblock->M);
                        }
                        else
                        {
                            ext = concat(ext,link,sousblock->M);
                        }
                        
                    }
                }
                x += 1;
            }
            if(x==histolen)
            {
                if(space_finder==0)
                {
                    sousblock->lowerx = block->lowerx;
                }
                else
                {
                    sousblock->lowerx = block->lowerx-nbspace;
                }
                /////////////////////////////////////////
                /*
                printB(sousblock,size,img);
                printcoords(sousblock);
                printf("w_seg histolen=%lu\n",histolen);
                */
                /////////////////////////////////////////

                letter_seg(sousblock,size,img);
                if(strlen(ext)==0)
                {
                    ext = concat2(ext,sousblock->M);
                }
                else
                {
                    ext = concat(ext,link,sousblock->M);
                }
                
            }
        }
        else 
        {
            x += 1;
        }
    }
    block->M = ext;
    free(sousblock->M);
    free(sousblock);


    /*
    for(size_t i =0; i< histolen; i++)
    {
        for (unsigned int y = 0; y< ver_histo[i]; y++)
        {
            printf("|");
        }
        printf("%u",ver_histo[i]);
        printf("\n");
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
void vert_histo(Block* block,
                size_t histolen,
                unsigned int ext[],
                Coords* size,
                unsigned char img[size->y][size->x])
                 {
  size_t x, y;
  //printf("x=%lu y=%lu \nx'=%lu y'=%lu\n",block->upperx,block->uppery,block->lowerx,block->lowery);
  //printf("histolen=%lu\n",histolen);
  for (x = 0; x < histolen; x++)
  {
    ext[x] = 0;
    //printf("ext(%lu) = %u\n",x,ext[x]);
    for (y = block->uppery; y <= block->lowery; y++)
    {

      ext[x] += img[y][x+block->upperx];
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
 * @param block contains the coordonates that needs to be processed
 * by the fonction.
 * @param size struct that contains the size (x,y) of img[y][x]
 * 
 */
void letter_seg(Block* block,
                Coords* size,
                unsigned char img[size->y][size->x])
{
    /*
    printB(block,size,img);
    printf("letter\n");
    printcoords(block);
    */

    size_t histolen = block->lowerx - block->upperx+1;
    unsigned int word_histo[histolen];
    vert_histo(block,histolen,word_histo,size,img);
    /*
    printf("histo:\n");
    for(size_t i =0; i< histolen;i++)
    {
        printf("%u\n",word_histo[i]);
    }
    */

    char* ext ="";
    
    Block* sousblock = newblock(block->upperx,block->uppery,
    block->lowerx,block->lowery);

    size_t x = 0;
    //size_t height = block->lowery - block->uppery +1;
    size_t length = block->lowerx - block->upperx + 1;
    //printf("lenght = %lu\n",length);
    while (x < length)
    {
        if (word_histo[x] != 0)
        {
            sousblock->upperx = block->upperx + x;
            while ((word_histo[x] != 0)&&(x < length))
            {
                x += 1;
            }
            sousblock->lowerx = block->upperx + x-1;
            
            /////////////////////////////////////////
            /*
            printB(sousblock,size,img);
            printcoords(sousblock);
            printf("l_seg histolen=%lu\n",histolen);
            */
            /////////////////////////////////////////
            /* insert call to neural network */
            sousblock->M = "l";
            /* insert call to neural network */

            ext = concat2(ext,sousblock->M);
        }
        else
        {
            x += 1;
        }
    }
    //printf("%s\n",ext);
    block->M = ext;
    free(sousblock->M);
    free(sousblock);
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


void printcoords(Block* block)
{
    printf("upper: x=%lu y=%lu\n",block->upperx,block->uppery);
    printf("lower: x=%lu y=%lu\n",block->lowerx,block->lowery);
}


void optiM(Coords* Msize,
            Coords* Osize,
            unsigned char M[Msize->y][Msize->x],
            unsigned char opti[Osize->y][Osize->x])
{
    size_t i,j;
    size_t ibis,jbis;
    for (j=0; j<Osize->y; j++)
    {
        for(i=0; i<Osize->x; i++)
        {
            opti[j][i]=0;
        }
    }


    for (j=0; j<Osize->y; j++)
    {
        for(i=0; i<Osize->x; i++)
        {
            if(isblack(i*12,j*12,Msize,M)==1)
            {
                //opti[j][i]=isblack(i*12,j*12,Msize,M);
                if (i==0)
                {
                    ibis = 0;
                }
                else
                {
                    ibis = i-1;
                }
                if (j==0)
                {
                    jbis = 0;
                }
                else
                {
                    jbis = i-1;
                }
                //printf("jbis = %lu\nibis = %lu\n",jbis,ibis);
                while(jbis<=j+1)
                {
                    ibis = 0;
                    //printf("entrer en boucle");
                    while(ibis<=i+1)
                    {
                        if((jbis<Osize->y)&&(ibis<Osize->x))
                        {
                            opti[jbis][ibis]=1;
                        }
                        ibis+=1;
                    }
                    jbis+=1;
                }

            }
        }
    }
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
    Block* block1 = block;
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
    Block* block1 = block;
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


Node* __buildtreeX(Node* tree,
                   Coords* size,
                   unsigned char M[size->x][size->y],
                   Coords* Osize,
                   unsigned char opti[Osize->x][Osize->y])
{
    
    BiBlock* children = Xcut(tree->block,Osize,opti);
    if(children->lower!=NULL)
    {
        tree->left = newNode();
        tree->right = newNode();
        tree->left->block = children->upper;
        tree->right->block = children->lower;
        tree->left = __buildtreeY(tree->left,size,M,Osize,opti);
        tree->right = __buildtreeY(tree->right,size,M,Osize,opti);
        return tree;
    }
    else
    {
        tree->block =children->upper;
        children = Ycut(tree->block,Osize,opti);
        if (children->lower!=NULL)
        {
            tree->left = newNode();
            tree->right = newNode();
            tree->left->block = children->upper;
            tree->right->block = children->lower;
            tree->left = __buildtreeX(tree->left,size,M,Osize,opti);
            tree->right = __buildtreeX(tree->right,size,M,Osize,opti);
        }
        else
        {
            tree->block =children->upper;
            tree->block = newblock(tree->block->upperx*12,tree->block->uppery*12,
            tree->block->lowerx*12,tree->block->lowery*12);
            line_seg(tree->block,size,M);
        }
        

        ///////////////////////////////////////////////
        /*
        printB(tree->block,size,M);
        printf("leaf\n");
        */
        ///////////////////////////////////////////////
        return tree;
    }
    
}


Node* __buildtreeY(Node* tree,
                   Coords* size,
                   unsigned char M[size->x][size->y],
                   Coords* Osize,
                   unsigned char opti[Osize->x][Osize->y])
{
    BiBlock* children = Ycut(tree->block,Osize,opti);
    if(children->lower!=NULL)
    {
        tree->left = newNode();
        tree->right = newNode();
        tree->left->block = children->upper;
        tree->right->block = children->lower;
        tree->left = __buildtreeX(tree->left,size,M,Osize,opti);
        tree->right = __buildtreeX(tree->right,size,M,Osize,opti);
        return tree;
    }
    else
    {
        tree->block =children->upper;
        children = Xcut(tree->block,Osize,opti);
        if (children->lower!=NULL)
        {
            tree->left = newNode();
            tree->right = newNode();
            tree->left->block = children->upper;
            tree->right->block = children->lower;
            tree->left = __buildtreeY(tree->left,size,M,Osize,opti);
            tree->right = __buildtreeY(tree->right,size,M,Osize,opti);
        }
        else
        {
            tree->block =children->upper;
            tree->block = newblock(tree->block->upperx*12,tree->block->uppery*12,
            tree->block->lowerx*12,tree->block->lowery*12);
            line_seg(tree->block,size,M);
        }
        ///////////////////////////////////////////////
        /*
        printB(tree->block,size,M);
        printf("leaf\n");
        */
        ///////////////////////////////////////////////
        return tree;
    }
    
}


Node* seg(Coords* size,unsigned char M[size->x][size->y])
{
    Node* root = newNode();
    Coords* Osize = newcoords();
    if (size->x%12==0)
    {
        Osize->x = size->x/12;
    }
    else
    {
        Osize->x = size->x/12 +1;
    }
    if (size->y%12==0)
    {
        Osize->y = size->y/12;
    }
    else
    {
        Osize->y = size->y/12 +1;
    }
    unsigned char opti[Osize->x][Osize->y];
    optiM(size,Osize,M,opti);

    root->block = newblock(0,0,Osize->x-1,Osize->y-1);
    root = __buildtreeX(root,size,M,Osize,opti);
    //printB(root->block,size,M);
    return root;
}

char* concat(char *str1,char *link ,char *str2)
{
    size_t size = strlen(str1)+1+strlen(str2)+1;
    char *str = malloc(size * sizeof(char));
    if(str == NULL)
    {
        errx(1,"Mot enough memory!");
    }
    char *p = str;
    while(*str1!=0)
    {
        *(p++) = *(str1++);
    }
    *(p++)=*link;
    while(*str2 != 0)
    {
        *(p++)=*(str2++);
    }
    *p = 0;
    return str;
}

char* concat2(char *str1,char *str2)
{
    size_t size = strlen(str1)+1+strlen(str2)+1;
    char *str = malloc(size * sizeof(char));
    if(str == NULL)
    {
        errx(1,"Mot enough memory!");
    }
    char *p = str;
    while(*str1!=0)
    {
        *(p++) = *(str1++);
    }
    while(*str2 != 0)
    {
        *(p++)=*(str2++);
    }
    *p = 0;
    return str;
}

void freetree(Node* tree)
{
    if(tree->left!=NULL)
    {
        freetree(tree->left);
    }
    if(tree->right!=NULL)
    {
        freetree(tree->right);
    }
    if(tree->block->M!=NULL)
    {
        free(tree->block->M);
    }
    free(tree->block);
    free(tree);
}