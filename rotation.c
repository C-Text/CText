#include "SDL/SDL.h"
#include "math.h"


/*
 * matrix: the matrix of the image
 * w: the width of the matrix
 * h: the height of the matrix
*/

//returns the angle of the image
int getAngle(int[] matrix, int w, int h)
{
	int angle = 0;

	double stockMat [180*h] = {0};
	

	for(int i=0; i< w; i++)
	{
		for(int j =0; j< h; j++)  //course through all the pixels
		{
			for(int t=1; t<=180; t++)  //course through all the possible thetas
			{
				double dblI = (double)i;
				double dblJ = (double)j;
				double dblT = (double)t;

				double dblP = dblI*cos(dblT) + dblJ*sin(dblT);


				stockMat[dblP*180+dblT]++;
			}
		}
	}

	// rho <= hauteur max image
	// 1<=theta<=180


	for(int k=1; k<=180; k++)  //course through the the matrix
	{
		for(int l = 0; l<h; l++)
		{
			if(angle < stockMat[l * 180 + k])
				angle = stockMat[l * 180 + k];
		}
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
void rotation(double angle, int[] matrix, int w, int h)
{
	double ray = sqrt(w*w + h*h);

	int resMat [h*w] = {0};  

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

	return resMat;
}
