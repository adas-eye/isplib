#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "histogram.h"

void getHistogram_U8(uint8 *in, uint32 *hist, int length)
{
    int i, val;

    memset(hist, 0, MAX_U8*sizeof(uint32));

    for (i=0;i<length;i++)
    {
        val = in[i];
        hist[val]++;
    }
}

void limitedHist_U8(uint32 *hist, uint32 *hist2, int upLimit, int downLimit, bool limitSave)
{
    int i, val, remainder = 0;

    for (i=0;i<MAX_U8;i++)
    {
        if (hist[i] > upLimit) 
        {
            remainder += (hist[i] - upLimit);
            hist2[i] = upLimit;
        } 
        else hist2[i] = hist[i];

        if (hist2[i] < downLimit) hist2[i] = downLimit;

        hist2[i] -= downLimit;
    }
    
    if (limitSave)
    {
        if (remainder<MAX_U8) remainder = MAX_U8;
        for (i=0;i<MAX_U8;i++) hist2[i] += (remainder/MAX_U8);
        printf("remainder = %d\n", remainder);
    }
}

void accumHistogram_U8(uint32 *hist, uint32 *accumHist, bool normalize)
{
    int i, count=0;

    accumHist[0] = hist[0];
    for (i=1;i<MAX_U8;i++)
    {
        accumHist[i] = accumHist[i-1] + hist[i];
    }

    if (normalize)
    {
        for (i=0;i<MAX_U8;i++)
        {
            accumHist[i] = accumHist[i]*MAX_U8/(accumHist[MAX_U8-1]+1);
        }
    }
}

void getAccumHistogram_U8(uint8 *imgIn, uint32 *accumHist, int length, bool normalize)
{
    int i, count=0;
    uint32 *hist;

    hist = (uint32*)calloc(MAX_U8, sizeof(uint32));
    getHistogram_U8(imgIn, hist, length);
    accumHistogram_U8(hist, accumHist, normalize);

    free(hist);
}

void histEQ_AH_U8(uint8 *imgIn, uint8 *imgOut, uint32 *accumHist, int length)
{
    int i;

    if (accumHist[MAX_U8-1] == 0) return ;
    for (i=0;i<length;i++)
    {
        imgOut[i] = accumHist[imgIn[i]];
    }
}

void histEQ_H_U8(uint8 *imgIn, uint8 *imgOut, uint32 *hist, int length)
{
    int i;
    uint32 *accumHist;

    accumHist = (uint32*)calloc(MAX_U8, sizeof(uint32));
    accumHistogram_U8(hist, accumHist, true);
    histEQ_AH_U8(imgIn, imgOut, accumHist, length);

    free(accumHist);
}

void histEQ_U8(uint8 *imgIn, uint8 *imgOut, int length)
{
    int i;
    uint32 *hist;

    hist = (uint32*)calloc(MAX_U8, sizeof(uint32));
    getHistogram_U8(imgIn, hist, length);
    histEQ_H_U8(imgIn, imgOut, hist, length);

    free(hist);
}

