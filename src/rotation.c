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
    double H = (double)h;
    double I, J, T, P;

    double R = sqrt(180*180+h*h);
	int r = (int)R;

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

					//double dT = M_PI/180;

					P = J*cos(T) + I*sin(T);

					int p = (int)P;
					p = p + (r/2);


					stockMat[p*180+t]++;
				}
			}
		}
	}


	int mem=0;
	int mem2=0;

	for(int k=0; k<180; k++)  //course through stockMat
	{
		for(int l = 0; l<r; l++)
		{
			if(angle < stockMat[l * 180 + k])
            {
                angle = stockMat[l * 180 + k];
                mem= k;
                mem2 = l;
            }
			printf("%lf, ", stockMat[l * 180 + k]);
		}
		printf("\n");
	}
	printf("k= %i, l= %i\n", mem, mem2-r/2);
	printf("content = %lf\n",stockMat[mem2 * 180 + mem]);

	free(stockMat);
	if(mem <= 90)
	    return mem;
	return 180-mem;
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
