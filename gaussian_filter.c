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

void gaussianFilter_U8(uint8 *in, uint8 *out, float sigma, int halfsize, int wid, int hgt)
{
	int x, y;
	int subx, suby;
	int window_size = halfsize*2+1;
	int filter_index;
	float filter_sum;
	float matrix_sum;
	int newX, newY;

	printf("gaussianFilter_U8 : sigma(%f), hlafsize(%d) \n", sigma, halfsize);

	float *gaussian = (float*)malloc(window_size*window_size*sizeof(float));
	filter_sum = getGaussianFilter(gaussian, sigma, halfsize);

	for (y=0; y<hgt; y++)
	{
		for (x=0;x<wid;x++)
		{
			filter_index = 0;
			matrix_sum = 0;
			for (suby=y-halfsize;suby<=(y+halfsize);suby++)
			{
				for (subx=x-halfsize;subx<=(x+halfsize);subx++)
				{
					newX = (subx<0)?-subx:(subx>=wid)?(wid*2-subx-1):subx;
					newY = (suby<0)?-suby:(suby>=hgt)?(hgt*2-suby-1):suby;
					matrix_sum += (in[newY*wid+newX]*gaussian[filter_index]);
					filter_index ++;
				}
			}
			out[y*wid+x] = (uint8)(matrix_sum / filter_sum);
		}
	}

	free(gaussian);
}

void gaussianFilter_U16(uint16 *in, uint16 *out, float sigma, int halfsize, int wid, int hgt)
{
	int x, y;
	int subx, suby;
	int window_size = halfsize*2+1;
	int filter_index;
	float filter_sum;
	float matrix_sum;
	int newX, newY;

	printf("gaussianFilter_U16 : sigma(%f), halfsize(%d) \n", sigma, halfsize);

	float *gaussian = (float*)malloc(window_size*window_size*sizeof(float));
	filter_sum = getGaussianFilter(gaussian, sigma, halfsize);

	for (y=0; y<hgt; y++)
	{
		for (x=0;x<wid;x++)
		{
			filter_index = 0;
			matrix_sum = 0;
			for (suby=y-halfsize;suby<=(y+halfsize);suby++)
			{
				for (subx=x-halfsize;subx<=(x+halfsize);subx++)
				{
					newX = (subx<0)?-subx:(subx>=wid)?(wid*2-subx-1):subx;
					newY = (suby<0)?-suby:(suby>=hgt)?(hgt*2-suby-1):suby;
					matrix_sum += (in[newY*wid+newX]*gaussian[filter_index]);
					filter_index ++;
				}
			}
			out[y*wid+x] = (uint16)(matrix_sum / filter_sum);
		}
	}

	free(gaussian);
}

void gaussianFilter_F(float *in, float *out, float sigma, int halfsize, int wid, int hgt)
{
	int x, y;
	int subx, suby;
	int window_size = halfsize*2+1;
	int filter_index;
	float filter_sum;
	float matrix_sum;
	int newX, newY;

	printf("gaussianFilter_F : sigma(%f), hlafsize(%d) \n", sigma, halfsize);

	float *gaussian = (float*)malloc(window_size*window_size*sizeof(float));
	filter_sum = getGaussianFilter(gaussian, sigma, halfsize);

	for (y=0; y<hgt; y++)
	{
		for (x=0;x<wid;x++)
		{
			filter_index = 0;
			matrix_sum = 0;
			for (suby=y-halfsize;suby<=(y+halfsize);suby++)
			{
				for (subx=x-halfsize;subx<=(x+halfsize);subx++)
				{
					newX = (subx<0)?-subx:(subx>=wid)?(wid*2-subx-1):subx;
					newY = (suby<0)?-suby:(suby>=hgt)?(hgt*2-suby-1):suby;
					matrix_sum += (in[newY*wid+newX]*gaussian[filter_index]);
					filter_index ++;
				}
			}
			out[y*wid+x] = (matrix_sum / filter_sum);
		}
	}

	free(gaussian);
}

