#include <stdio.h>
#include <stdlib.h>
#include "lib_isp.h"

void removeZeroHistNormalize_U8(uint8 *in, uint8* in4hist, uint8 *out, int imgLen)
{
	uint32 *hist, *hist2;

	hist = (uint32*)calloc(MAX_U8, sizeof(uint32));
	hist2 = (uint32*)calloc(MAX_U8, sizeof(uint32));

	getHistogram_U8(in4hist, hist, imgLen);
	limitedHist_U8(hist, hist2, 1, 0, false);
	histEQ_H_U8(in, out, hist2, imgLen);

	free(hist);
	free(hist2);
}

void removeZeroHistNormalize_U16(uint16 *in, uint16* in4hist, uint16 *out, int imgLen)
{
	uint32 *hist, *hist2;

	hist = (uint32*)calloc(MAX_U16, sizeof(uint32));
	hist2 = (uint32*)calloc(MAX_U16, sizeof(uint32));

	getHistogram_U16(in4hist, hist, imgLen);
	limitedHist_U16(hist, hist2, 1, 0, false);
	histEQ_H_U16(in, out, hist2, imgLen);

	free(hist);
	free(hist2);
}

void removeZeroHist_U16(uint16 *in, uint16* in4hist, uint16 *out, int imgLen)
{
	int i;
	uint32 *hist, *hist2;
	uint32 *accumHist;

	hist = (uint32*)calloc(MAX_U16, sizeof(uint32));
	hist2 = (uint32*)calloc(MAX_U16, sizeof(uint32));
	accumHist = (uint32*)calloc(MAX_U16, sizeof(uint32));

	getHistogram_U16(in4hist, hist, imgLen);
	limitedHist_U16(hist, hist2, 1, 0, false);
    accumHistogram_U16(hist2, accumHist, false);
    histEQ_AH_U16(in, out, accumHist, imgLen);

    free(accumHist);
	free(hist);
	free(hist2);
}

void removeZeroHistNormalize_U24(uint8 *in, uint8 *out, int imgLen)
{
	uint8 *inRgb, *inR, *inG, *inB, *inY;
	uint8 *outR, *outG, *outB;
	uint32 *hist, *hist2;

	inR = (uint8*)calloc(imgLen, sizeof(uint8));
	inG = (uint8*)calloc(imgLen, sizeof(uint8));
	inB = (uint8*)calloc(imgLen, sizeof(uint8));
	inY = (uint8*)calloc(imgLen, sizeof(uint8));
	outR = (uint8*)calloc(imgLen, sizeof(uint8));
	outG = (uint8*)calloc(imgLen, sizeof(uint8));
	outB = (uint8*)calloc(imgLen, sizeof(uint8));

	hist = (uint32*)calloc(MAX_U8, sizeof(uint32));
	hist2 = (uint32*)calloc(MAX_U8, sizeof(uint32));
	splitRGBY(in, inR, inG, inB, inY, imgLen, 1);
	
	getHistogram_U8(inY, hist, imgLen);
	limitedHist_U8(hist, hist2, 1, 0, false);
	histEQ_H_U8(inR, outR, hist2, imgLen);
	histEQ_H_U8(inG, outG, hist2, imgLen);
	histEQ_H_U8(inB, outB, hist2, imgLen);

	bindRGB(outR, outG, outB, out, imgLen, 1);

	free(inR);
	free(inG);
	free(inB);
	free(inY);
	free(outR);
	free(outG);
	free(outB);
	free(hist);
	free(hist2);
}

