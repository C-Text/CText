#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


void hori_histo(unsigned int ext[], size_t sizex, size_t sizey, unsigned char img[sizey][sizex]);
void vert_histo(size_t upper,size_t lower,unsigned int ext[], size_t sizex, size_t sizey, unsigned char img[sizey][sizex]);
void word_seg(size_t upper,size_t lower,size_t sizex, size_t sizey, unsigned char img[sizey][sizex]);
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


int main()
{
    size_t sizex = 60;
    size_t sizey = 60;
    unsigned char image[sizey][sizex];

    //unsigned char image[][4]={ { 0,1,0,1 } , { 1,1,1,1 } ,{ 1,0,0,0 }};
    
    //unsigned int test[60];
    //unsigned int ptest = test;

    generate(sizex,sizey,image);
    line_seg(sizex,sizey,image);

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
void hori_histo(unsigned int ext[], size_t sizex, size_t sizey, unsigned char img[sizey][sizex])
{
    
    for(unsigned int y = 0 ; y < sizey ; y++)
    {
        ext[y]=0;
        for(unsigned int x = 0; x < sizex ; x++)
        {
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
void line_seg(size_t sizex, size_t sizey, unsigned char img[sizey][sizex])
{
    unsigned int ho_histo[sizey];
    hori_histo(ho_histo,sizex,sizey,img);
    
    size_t y=0;
    size_t upper=0;
    size_t lower=0;
    while (y<sizey)
    {
        if (ho_histo[y]!=0)
        {
            upper = y;
            while(ho_histo[y]!=0)
            {
                y+=1;
            }
            lower = y-1;
            word_seg(upper,lower,sizex,sizey,img);
        }

        y+=1;
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
void word_seg(size_t upper,size_t lower,size_t sizex, size_t sizey, unsigned char img[sizey][sizex])
{
    unsigned int ver_histo[sizex];
    vert_histo(upper,lower,ver_histo,sizex,sizey,img);


    size_t x = 0;
    size_t left = 0;
    size_t right = 0;
    int space_finder;
    int nbspace;
    while (x<sizex)
    {
        if (ver_histo[x]!=0)
        {
            left = x;
            space_finder = 1;
            nbspace = 0;
            while((space_finder) && ( x<sizex ))
            {
                if(ver_histo[x]==0)
                {
                    nbspace+=1;
                    if (nbspace>4)
                    {
                        space_finder = 0;
                        right  = x-nbspace;
                        //printf("%lu,%lu",left,right);
                    }
                }
                x+=1;
            }
        }
        else
        {
            x+=1;
        }
    }
    printf("%lu,%lu\n",left,right);

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
 * 
 */
void vert_histo(size_t upper,size_t lower,unsigned int ext[], size_t sizex, size_t sizey, unsigned char img[sizey][sizex])
{
    size_t x, y;
    for(x = 0 ; x < sizex ; x++)
    {
        ext[x]=0;
        //printf("ext(%lu) = %u\n",x,ext[x]);
        for(y = upper; y < lower ; y++)
        {
            
            ext[x] += img[y][x];
            //printf("%u",img[y][x]);
        }
        //printf("\n");
        //printf("ext(%lu) = %u\n",x,ext[x]);
    }
}


