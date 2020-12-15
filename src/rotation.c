#include "SDL/SDL.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>


/*
 * matrix: the matrix of the image
 * w: the width of the matrix
 * h: the height of the matrix
*/

//returns the angle of the image
int getAngle(int matrix[], int w, int h)
{
	int angle = 0;
    double I, J, T, P;
    double R = sqrt(180*180+h*h);
	int r = (int)R;
    int mem=0;

	double *stockMat = calloc(180*R, sizeof(double));

	for(int i=0; i< w; i++)
	{
		for(int j=0; j< h; j++)  //course through all the pixels
		{
			if(matrix[j*w+i] == 0)
			{
                I = (double)i;
                J = (double)j;

                for(int t=0; t<=180; t++)  //course through all the possible thetas
				{
                    T = (double)t;
					P = J*cos(T) + I*sin(T);
					int p = (int)P;
					p = p + (r/2);
					stockMat[p*180+t]++;
				}
			}
		}
	}

	for(int k=0; k<180; k++)  //course through stockMat
	{
		for(int l = 0; l<r; l++)
		{
			if(mem < stockMat[l * 180 + k])
            {
                mem = stockMat[l * 180 + k];
                angle= k;
            }
		}
	}
	free(stockMat);
	if(angle <= 90)
	    return angle;
	return 180-angle;
}


/*
 * angle: the angle we want to rotate the image with
 * matrix: the matrix of the image
 * w: the width of the matrix
 * h: the height of the matrix
*/

//rotates the image according to the angle 'angle'
void rotation(int angle, int matrix[], int w, int h)
{
    double A = (double)angle;
    double I, J;
	int *resMat = calloc(h*w, sizeof(int));  

	for(int i=0; i< w; i++)
	{
		for(int j =0; j< h; j++)
		{
			I = (double)i;
			J = (double)j;
			
			//new coordinates of the current pixel
			double X = I*cos(A) - J*sin(A);
			double Y = I*sin(A) + J*cos(A);
			
			int x = (int)X;
			int y = (int)Y;

			//replace pixel values
			resMat[y*w+x] = matrix[j*w+i];
		}
	}

	matrix = resMat;
}
