#include "math.h"
#include <stdlib.h>



/**
 * Returns the angle of the image
 * @param matrix: the matrix of the image
 * @param w: the width of the matrix
 * @param h: the height of the matrix
 * @return The angle determined
 */
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
                    T =T*M_PI/180;
					P = J*cos(T) + I*sin(T);  //principle of the Hough transform
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


/**
 * Rotates the image according to the angle 'angle'
 * @param angle: the angle we want to rotate the image with
 * @param matrix: the matrix of the image
 * @param w: the width of the matrix
 * @param h: the height of the matrix
 */
int* rotation(int angle, int matrix[], int w, int h)
{
    double R = sqrt(w*w+h*h);
    int r =(int)R;
    int* resMat  = calloc(r*r, sizeof(int));
    double A = (double)angle;
    double I, J, X, Y;
    int x,y;

    for(int i =0; i< r*r; i++)
        resMat[i] = 1;

	for(int i=0; i< w; i++)
	{
		for(int j =0; j< h; j++)
		{
			I = (double)i;
			J = (double)j;
			
			//new coordinates of the current pixel
			X = I*cos(A) - J*sin(A);
			Y = I*sin(A) + J*cos(A);
			
			x = (int)X;
			y = (int)Y;

			x = x+r/2;
			y = y+r/2;

			//replace pixel values
            resMat[y*w+x] = matrix[j*w+i];
		}
	}
	return resMat;
}