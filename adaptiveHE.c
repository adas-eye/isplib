#include <stdio.h>
#include <stdlib.h>
#include "lib_isp.h"

#define MAX 256
static void getRegionAccumHist(uint8* in, uint32 *accumHist, int wid, int hgt, int win_size, int limit)
{
	int i, j, k, l;
	uint8 *regionImg;
	int gridIndex = 0, regionIndex, regionLen = win_size*win_size;
	int x, y;
	uint32 *hist;

	regionImg = (uint8*)calloc(regionLen, sizeof(uint8));
	hist = (uint32*)calloc(MAX, sizeof(uint32));

	for (i=0;i<hgt;i+=win_size)
	{
		for (j=0;j<wid;j+=win_size)
		{
			regionIndex = 0;
			for (k=i;k<(i+win_size);k++)
			{
				for (l=j;l<(j+win_size);l++)
				{
					if (k>=hgt) y=(hgt-k+hgt-1);
					else y=k;
					if (l>=wid) x=(wid-l+wid-1);
					else x=l;

					regionImg[regionIndex++] = in[y*wid+x];
				}
			}
			printf("Grid : %4d - ", gridIndex);
			getHistogram_U8(regionImg, hist, regionLen);
			limitedHist_U8(hist, hist, limit, 0, true);
			accumHistogram_U8(hist, accumHist + gridIndex*MAX);
			gridIndex++;
		}
	}

	free(regionImg);
	free(hist);
}

static uint32 getHistGrid(uint8 val, int gridX, int gridY, uint32 *accumHist,
				   int gridWid, int gridHgt)
{
	if (gridX < 0) gridX = 0;
	else if (gridX >= gridWid) gridX = gridWid-1;
	
	if (gridY < 0) gridY = 0;
	else if (gridY >= gridHgt) gridY = gridHgt-1;
	
	return accumHist[(gridY*gridWid+gridX)*MAX+val];
}

void adaptiveHE(uint8 *in, uint8* in4hist, uint8 *out, int wid, int hgt, int win_size, int limit)
{
	int i, j;
	uint32 *accumHist;
	int gridWid = (wid+win_size-1)/win_size;
	int gridHgt = (hgt+win_size-1)/win_size;
	int gridX, gridY;
	uint32 histUL, histUR, histDL, histDR;
	int xRate, yRate;
	int intX1, intX2;

	printf("wid:%d, hgt:%d, win_size:%d, limit:%d\n", wid, hgt, win_size, limit);
	printf("gridWid:%d, gridHgt:%d\n", gridWid, gridHgt);
	accumHist = (uint32*)calloc(MAX*gridWid*gridHgt, sizeof(uint32));
	getRegionAccumHist(in4hist, accumHist, wid, hgt, win_size, limit);

	for (i=0;i<hgt;i++)
	{
		for (j=0;j<wid;j++)
		{
			gridX = (j+win_size/2)/win_size;
			gridY = (i+win_size/2)/win_size;

			histUL = getHistGrid(in[i*wid+j], gridX-1, gridY-1, 
								accumHist, gridWid, gridHgt);
			histUR = getHistGrid(in[i*wid+j], gridX, gridY-1, 
								accumHist, gridWid, gridHgt);
			histDL = getHistGrid(in[i*wid+j], gridX-1, gridY, 
								accumHist, gridWid, gridHgt);
			histDR = getHistGrid(in[i*wid+j], gridX, gridY, 
								accumHist, gridWid, gridHgt);
			
			xRate = (j+win_size/2) % win_size;
			yRate = (i+win_size/2) % win_size;
			intX1 = (histUL*(win_size-xRate)+histUR*xRate)/win_size;
			intX2 = (histDL*(win_size-xRate)+histDR*xRate)/win_size;
			out[i*wid+j] = (intX1*(win_size-yRate)+intX2*yRate)/win_size;
		}
	}

	free(accumHist);
}

