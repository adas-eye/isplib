#include <stdio.h>
#include <stdlib.h>
#include "type.h"

#define CONST_A 0.39874
static float getGaussianFilter(float *gaussian, float sigma, int halfsize)
{
	int i, j, index;
	float distance;
	float const_b = -1.0/(2*sigma*sigma);
	float sum = 0;

	index = 0;
	for (i=0;i<halfsize*2+1;i++)
	{
		for (j=0;j<halfsize*2+1;j++)
		{
			distance = sqrt((float)(halfsize-i)*(halfsize-i)+(halfsize-j)*(halfsize-j));
			gaussian[index] = (CONST_A * exp(distance*distance*const_b));
			
			sum += gaussian[index];
			index++;
		}
	}

	return sum;
}

static float getGaussianValue(float sigma, int distance)
{
	int i, j, index;

	float const_b = -1.0/(2*sigma*sigma);
	float gaussian;

	gaussian = (CONST_A * exp((float)distance*distance*const_b));

	return gaussian;
}

void bilateralFilter_U16(uint16 *in, uint16 *out, float sigma, int halfsize, int wid, int hgt)
{
	int x, y;
	int subx, suby;
	int window_size = halfsize*3+1;
	int filter_index;
	float filter_sum, filter_I;
	float matrix_sum;
	int newX, newY;
	uint16 gapWithCenter, centerVal, newVal;
	float *gaussian = (float*)malloc(window_size*window_size*sizeof(float));

	(void)getGaussianFilter(gaussian, sigma, halfsize);

	for (y=0; y<hgt; y++)
	{
		for (x=0;x<wid;x++)
		{
			matrix_sum = 0;
			filter_sum = 0;
			filter_index = 0;
			for (suby=y-halfsize;suby<=(y+halfsize);suby++)
			{
				for (subx=x-halfsize;subx<=(x+halfsize);subx++)
				{
					newX = (subx<0)?-subx:(subx>=wid)?(wid*2-subx-1):subx;
					newY = (suby<0)?-suby:(suby>=hgt)?(hgt*2-suby-1):suby;

					centerVal = in[y*wid+x];
					newVal = in[newY*wid+newX];
					gapWithCenter = (centerVal>newVal)?(centerVal-newVal):(newVal-centerVal);
					filter_I = getGaussianValue(sigma*10, gapWithCenter);

					matrix_sum += (newVal*gaussian[filter_index]*filter_I);
					filter_sum += gaussian[filter_index]*filter_I;
					filter_index ++;
				}
			}
			out[y*wid+x] = (uint16)(matrix_sum / filter_sum);
		}
	}

	free(gaussian);
}

void print_gaussian(float sigma, int halfsize)
{
	int window_size = halfsize*3+1;
	int i, j, index;

	float *gaussian = (float*)malloc(window_size*window_size*sizeof(float));

	(void)getGaussianFilter(gaussian, sigma, halfsize);

	index = 0;
	for (i=0;i<(halfsize*2+1);i++)
	{
		for (j=0;j<(halfsize*2+1);j++)
		{
			printf("%7.4f", gaussian[index]);
			index++;
		}
		printf("\n");
	}
/*
	for (i=0;i<256;i++)
	{
		printf("%3d - %f\n", i, getGaussianValue(sigma*10, i));
	}
*/
	free(gaussian);
}

