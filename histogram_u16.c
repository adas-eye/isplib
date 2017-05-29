#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "histogram.h"

void getHistogram_U16(uint16 *in, uint32 *hist, int length)
{
    int i, val;

    memset(hist, 0, MAX_U16*sizeof(uint32));

    for (i=0;i<length;i++)
    {
        val = in[i];
        hist[val]++;
    }
}

void limitedHist_U16(uint32 *hist, uint32 *hist2, int upLimit, int downLimit, bool limitSave)
{
    int i, val, remainder = 0;

    for (i=0;i<MAX_U16;i++)
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
        if (remainder<MAX_U16) remainder = MAX_U16;
        for (i=0;i<MAX_U16;i++) hist2[i] += (remainder/MAX_U16);
        printf("remainder = %d\n", remainder);
    }
}

void accumHistogram_U16(uint32 *hist, uint32 *accumHist, bool normalize)
{
    int i, count=0;

    accumHist[0] = hist[0];
    for (i=1;i<MAX_U16;i++)
    {
        accumHist[i] = accumHist[i-1] + hist[i];
    }

    if (normalize)
    {
        for (i=0;i<MAX_U16;i++)
        {
            accumHist[i] = accumHist[i]*MAX_U16/(accumHist[MAX_U16-1]+1);
        }
    }
}

void getAccumHistogram_U16(uint16 *imgIn, uint32 *accumHist, int length, bool normalize)
{
    int i, count=0;
    uint32 *hist;

    hist = (uint32*)calloc(MAX_U16, sizeof(uint32));
    getHistogram_U16(imgIn, hist, length);
    accumHistogram_U16(hist, accumHist, normalize);

    free(hist);
}

void histEQ_AH_U16(uint16 *imgIn, uint16 *imgOut, uint32 *accumHist, int length)
{
    int i;

    if (accumHist[MAX_U16-1] == 0) return ;
    for (i=0;i<length;i++)
    {
        imgOut[i] = accumHist[imgIn[i]];
    }
}

void histEQ_H_U16(uint16 *imgIn, uint16 *imgOut, uint32 *hist, int length)
{
    int i;
    uint32 *accumHist;

    accumHist = (uint32*)calloc(MAX_U16, sizeof(uint32));
    accumHistogram_U16(hist, accumHist, true);
    histEQ_AH_U16(imgIn, imgOut, accumHist, length);

    free(accumHist);
}

void histEQ_U16(uint16 *imgIn, uint16 *imgOut, int length)
{
    int i;
    uint32 *hist;

    hist = (uint32*)calloc(MAX_U16, sizeof(uint32));
    getHistogram_U16(imgIn, hist, length);
    histEQ_H_U16(imgIn, imgOut, hist, length);

    free(hist);
}

