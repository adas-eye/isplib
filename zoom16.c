#include <stdio.h>
#include <stdlib.h>
#include "e:\\lib_isp\\lib_isp.h"

void zoom16_Bilinear(uint16 *in, int inWid, int inHgt, 
            uint16 *out, int outWid, int outHgt)
{
    int i, j, indexX, indexY;
    float fInX, fInY;
    float fRatioX, fRatioY;
    float fTmpVal1, fTmpVal2;

    for (i=0;i<outHgt;i++)
    {
        for (j=0;j<outWid;j++)
        {
            fInX = ((float)j/outWid)*inWid;
            indexX = (int)fInX;
            fInY = ((float)i/outHgt)*inHgt;
            indexY = (int)fInY;

            if (indexX == (inWid-1)) indexX -= 1;
            if (indexY == (inHgt-1)) indexY -= 1;

            fRatioX = fInX - indexX;
            fRatioY = fInY - indexY;
            //printf("(%4d, %4d)-(%7.1f[%3.1f], %7.1f[%3.1f])\n", j, i, fInX, fRatioX, fInY, fRatioY);

            fTmpVal1 = (in[indexY*inWid+indexX]*(1.0-fRatioX) +
                       in[indexY*inWid+indexX+1]*fRatioX);
            fTmpVal2 = (in[(indexY+1)*inWid+indexX]*(1.0-fRatioX) +
                       in[(indexY+1)*inWid+indexX+1]*fRatioX);
            out[i*outWid+j] = (uint16)(fTmpVal1*(1.0-fRatioY) +
                                       fTmpVal2*fRatioY);                
            //printf("%f %f %d\n", fTmpVal1, fTmpVal2, out[i*outWid+j]);
        }
    }
}

void zoom16_BiCubic(uint16 *in, int inWid, int inHgt, 
            uint16 *out, int outWid, int outHgt, int range)
{
    int i, j, indexX0, indexX1, indexX2, indexX3, indexY0, indexY1, indexY2, indexY3;
    float fInX, fInY;
    double a00, a01, a02, a03;
    double a10, a11, a12, a13;
    double a20, a21, a22, a23;
    double a30, a31, a32, a33;
    double x, x2, x3, y, y2, y3;
    double p[4][4], fVal;

    for (i=0;i<outHgt;i++)
    {
        for (j=0;j<outWid;j++)
        {
            fInX = ((float)j/outWid)*inWid;
            indexX1 = (int)fInX;
            fInY = ((float)i/outHgt)*inHgt;
            indexY1 = (int)fInY;

            if (indexX1 == (inWid-1))
            {
                indexX0 = indexX1 - 1;
                indexX2 = indexX1;
                indexX3 = indexX1;
            }
            else if (indexX1 == (inWid-2)) 
            {
                indexX0 = indexX1 - 1;
                indexX2 = indexX1 + 1;
                indexX3 = indexX1 + 1;
            }
            else if (indexX1 == 0)
            {
                indexX0 = 0;
                indexX2 = 1;
                indexX3 = 2;                
            }
            else
            {
                indexX0 = indexX1 - 1;
                indexX2 = indexX1 + 1;
                indexX3 = indexX1 + 2;                
            }

            if (indexY1 == (inHgt-1))
            {
                indexY0 = indexY1 - 1;
                indexY2 = indexY1;
                indexY3 = indexY1;
            }
            else if (indexY1 == (inHgt-2)) 
            {
                indexY0 = indexY1 - 1;
                indexY2 = indexY1 + 1;
                indexY3 = indexY1 + 1;
            }
            else if (indexY1 == 0)
            {
                indexY0 = 0;
                indexY2 = 1;
                indexY3 = 2;                
            }
            else
            {
                indexY0 = indexY1 - 1;
                indexY2 = indexY1 + 1;
                indexY3 = indexY1 + 2;
            }

            p[0][0] = in[indexY0*inWid + indexX0];
            p[1][0] = in[indexY0*inWid + indexX1];
            p[2][0] = in[indexY0*inWid + indexX2];
            p[3][0] = in[indexY0*inWid + indexX3];
            p[0][1] = in[indexY1*inWid + indexX0];
            p[1][1] = in[indexY1*inWid + indexX1];
            p[2][1] = in[indexY1*inWid + indexX2];
            p[3][1] = in[indexY1*inWid + indexX3];
            p[0][2] = in[indexY2*inWid + indexX0];
            p[1][2] = in[indexY2*inWid + indexX1];
            p[2][2] = in[indexY2*inWid + indexX2];
            p[3][2] = in[indexY2*inWid + indexX3];
            p[0][3] = in[indexY3*inWid + indexX0];
            p[1][3] = in[indexY3*inWid + indexX1];
            p[2][3] = in[indexY3*inWid + indexX2];
            p[3][3] = in[indexY3*inWid + indexX3];

            a00 = p[1][1];
            a01 = -.5*p[1][0] + .5*p[1][2];
            a02 = p[1][0] - 2.5*p[1][1] + 2*p[1][2] - .5*p[1][3];
            a03 = -.5*p[1][0] + 1.5*p[1][1] - 1.5*p[1][2] + .5*p[1][3];
            a10 = -.5*p[0][1] + .5*p[2][1];
            a11 = .25*p[0][0] - .25*p[0][2] - .25*p[2][0] + .25*p[2][2];
            a12 = -.5*p[0][0] + 1.25*p[0][1] - p[0][2] + .25*p[0][3] + .5*p[2][0] - 1.25*p[2][1] + p[2][2] - .25*p[2][3];
            a13 = .25*p[0][0] - .75*p[0][1] + .75*p[0][2] - .25*p[0][3] - .25*p[2][0] + .75*p[2][1] - .75*p[2][2] + .25*p[2][3];
            a20 = p[0][1] - 2.5*p[1][1] + 2*p[2][1] - .5*p[3][1];
            a21 = -.5*p[0][0] + .5*p[0][2] + 1.25*p[1][0] - 1.25*p[1][2] - p[2][0] + p[2][2] + .25*p[3][0] - .25*p[3][2];
            a22 = p[0][0] - 2.5*p[0][1] + 2*p[0][2] - .5*p[0][3] - 2.5*p[1][0] + 6.25*p[1][1] - 5*p[1][2] + 1.25*p[1][3] + 2*p[2][0] - 5*p[2][1] + 4*p[2][2] - p[2][3] - .5*p[3][0] + 1.25*p[3][1] - p[3][2] + .25*p[3][3];
            a23 = -.5*p[0][0] + 1.5*p[0][1] - 1.5*p[0][2] + .5*p[0][3] + 1.25*p[1][0] - 3.75*p[1][1] + 3.75*p[1][2] - 1.25*p[1][3] - p[2][0] + 3*p[2][1] - 3*p[2][2] + p[2][3] + .25*p[3][0] - .75*p[3][1] + .75*p[3][2] - .25*p[3][3];
            a30 = -.5*p[0][1] + 1.5*p[1][1] - 1.5*p[2][1] + .5*p[3][1];
            a31 = .25*p[0][0] - .25*p[0][2] - .75*p[1][0] + .75*p[1][2] + .75*p[2][0] - .75*p[2][2] - .25*p[3][0] + .25*p[3][2];
            a32 = -.5*p[0][0] + 1.25*p[0][1] - p[0][2] + .25*p[0][3] + 1.5*p[1][0] - 3.75*p[1][1] + 3*p[1][2] - .75*p[1][3] - 1.5*p[2][0] + 3.75*p[2][1] - 3*p[2][2] + .75*p[2][3] + .5*p[3][0] - 1.25*p[3][1] + p[3][2] - .25*p[3][3];
            a33 = .25*p[0][0] - .75*p[0][1] + .75*p[0][2] - .25*p[0][3] - .75*p[1][0] + 2.25*p[1][1] - 2.25*p[1][2] + .75*p[1][3] + .75*p[2][0] - 2.25*p[2][1] + 2.25*p[2][2] - .75*p[2][3] - .25*p[3][0] + .75*p[3][1] - .75*p[3][2] + .25*p[3][3];

            x = fInX - indexX1;
            y = fInY - indexY1;
            x2 = x * x;
            x3 = x2 * x;
            y2 = y * y;
            y3 = y2 * y;

            fVal = (a00 + a01 * y + a02 * y2 + a03 * y3) +
                   (a10 + a11 * y + a12 * y2 + a13 * y3) * x +
                   (a20 + a21 * y + a22 * y2 + a23 * y3) * x2 +
                   (a30 + a31 * y + a32 * y2 + a33 * y3) * x3;

            out[i*outWid+j] = (uint16)(fVal<0?0:fVal>range?range:fVal);
        }
    }
}

void doZoom16(char *inFilename, char *outFilename, 
              int inWid, int inHgt, int outWid, int outHgt, int range, int type)
{
    uint16 *in, *out;
    int i, j;

    in = (uint16*)calloc(inWid*inHgt*2, sizeof(uint16));
    out = (uint16*)calloc(outWid*outHgt*2, sizeof(uint16));

    readPGM_P2_U16(inFilename, in, inWid, inHgt);
    switch (type)
    {
        case 0:
            zoom16_Bilinear(in, inWid, inHgt, out, outWid, outHgt);
            printf("Do Biliear Interpolation Resize.\n");
            break;
        case 1:
        default:
            zoom16_BiCubic(in, inWid, inHgt, out, outWid, outHgt, range);
            printf("Do Bi-Cubic Interpolation Resize.\n");
            break;
    }
    
    savePGM_P2_U16(outFilename, out, outWid, outHgt, range);
    strcat(outFilename, ".ppm");
    savePPM_P6_U16(outFilename, out, outWid, outHgt);
    
    free(in);
    free(out);
}

int main(int argc, char *argv[])
{
    int fileType;
    S_IMG_SIZE imgSize, outSize;
    int range, type;

    if (argc < 6)
    {
        printf("** USAGE ***\n");
        printf("ex) zoom16.exe input.pgm output.pgm outWidth outHeight type\n");
        printf("   - type is 0 : Bilinear Interpolation.\n");
        printf("   - type is 1 : Bi-Cubic Interpolation.\n");
        return 1;
    }

    fileType = getImgType(argv[1]);
        
    if (fileType != 2) 
    {
        printf("This file type(P%d) is not supported yet.\n", fileType);
    }

    getImgSize(argv[1], &imgSize);
    range = getImgRange(argv[1]);
    outSize.width = atoi(argv[3]);
    outSize.height = atoi(argv[4]);
    printf("outWidth :%4d, outHeight : %4d\n", outSize.width, outSize.height);
    type = atoi(argv[5]);
    doZoom16(argv[1], argv[2], imgSize.width, imgSize.height, outSize.width, outSize.height, range, type);
    
    return 0;
}

