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

	double R = sqrt(180*180+h*h);
	int r = (int)R;

	double *stockMat = calloc(180*R, sizeof(double));

	for(int i=0; i< w; i++)
	{
		for(int j=0; j< h; j++)  //course through all the pixels
		{
			if(matrix[j*w+i] == 0)
			{
				for(int t=0; t<=180; t++)  //course through all the possible thetas
				{
					double I = (double)i;
					double J = (double)j;
					double T = (double)t;
					double H = (double)h;

					double dT = M_PI/180 ;

					double P = I*cos(T*dT) + (H-J)*sin(T*dT);

					int p = (int)P;
					if(p>0)
					    stockMat[p*180+t]++; //segfault
				}
			}
		}
	}

	for(int k=0; k<180; k++)  //course through stockMat
	{
		for(int l = 0; l<r; l++)
		{
			if(angle < stockMat[l * 180 + k])
            {
                angle = k;
            }
		}
	}

    for(int v = 0; v < 180; v++)
    {
        for(int b = 0; b < R; b++)
        {
            printf("%i,", stockMat[b*180+v]);
        }
        printf("\n");
    }

	return angle;
}


/*
 * angle: the angle we want to rotate the image with
 * matrix: the matrix of the image
 * w: the width of the matrix
 * h: the height of the matrix
*/

//rotates the image according to the angle 'angle'
void rotation(double angle, int matrix[], int w, int h)
{
	int *resMat = calloc(h*w, sizeof(int));  

	for(int i=0; i< w; i++)
	{
		for(int j =0; j< h; j++)
		{
			double I = (double)I;
			double J = (double)J;
			
			//new coordinates of the current pixel
			double X = I*cos(angle) + J*sin(angle);
			double Y = (-1)*I*sin(angle) + J*cos(angle);
			
			int x = (int)X;
			int y = (int)Y;

			//replace pixel values
			resMat[x*w+y] = matrix[i*w+j];
		}
	}

	matrix = resMat;
}
