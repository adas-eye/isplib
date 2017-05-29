#include <stdio.h>
#include <stdlib.h>
#include "type.h"

int findMin_U16(uint16 *array, int num)
{
	uint16 min = 65535;
	int i, index;

	for (i = 0; i< num; i++)
	{
		//printf("%2d: val : %3d, min :%3d\n", i, array[i], min);
		if (min>array[i])
		{
			min = array[i];
			index = i;	
		} 
	}

	return index;
}

int findMax_U16(uint16 *array, int num)
{
	uint16 max = 0;
	int i, index;

	for (i = 0; i< num; i++)
	{
		//printf("%2d: val : %3d, min :%3d\n", i, array[i], min);
		if (max<array[i])
		{
			max = array[i];
			index = i;	
		} 
	}

	return index;
}

void findMinMax_U16(uint16 *array, int num, uint16 *min, uint16 *max)
{
	int i, index;

	*max = 0;
	*min = 65535;
	for (i = 0; i< num; i++)
	{
		if (*max<array[i]) *max = array[i];
		if (*min>array[i]) *min = array[i];
	}
	printf("findMinMax_U16 - min(%d), max(%d)\n", *min, *max);
}

int findMin(int *array, int num)
{
	int min = 0x7FFFFFFF;
	int i, index;

	for (i = 0; i< num; i++)
	{
		//printf("%2d: val : %3d, min :%3d\n", i, array[i], min);
		if (min>array[i])
		{
			min = array[i];
			index = i;
		} 
	}

	return index;
}

void normalize_U16(uint16 *in, uint16 *out, int len, int range)
{
    int i;
    uint16 min, max;

    findMinMax_U16(in, len, &min, &max);

    for (i=0;i<len;i++)
    {
        out[i] = (in[i]-min)*range/(max-min+1);
    }
}

