#include <stdio.h>
#include <stdlib.h>
#include "type.h"

void readPPM_P6(char* filename, uint8 *img, int wid, int hgt)
{
    FILE *fin = NULL;
    int i;
    char temp[100];
    
    fin = fopen(filename, "rb");
    if (fin == NULL)
    {
        printf("readPPM_P6 Error : %s cannot open.\n", filename);
        return;
    }
 
    fgets(temp, 100, fin); //printf("%s", temp);
    fgets(temp, 100, fin); //printf("%s", temp);
    fgets(temp, 100, fin); //printf("%s", temp);
    fgets(temp, 100, fin); //printf("%s", temp);
    fread(img, 1, wid*hgt*3, fin);
    fclose(fin);

    printf("readPPM_P6 : %s.\n", filename);
}

void readPPM_P3(char* filename, uint8 *rgb, int wid, int hgt)
{
    FILE *fin = NULL;
    int i;
    char temp[100];
    
    fin = fopen(filename, "rt");
    if (fin == NULL)
    {
        printf("readPPM_P6 Error : %s cannot open.\n", filename);
        return;
    }
 
    fgets(temp, 100, fin); //printf("%s", temp);
    fgets(temp, 100, fin); //printf("%s", temp);
    fgets(temp, 100, fin); //printf("%s", temp);
    fgets(temp, 100, fin); //printf("%s", temp);
    
    for (i=0;i<wid*hgt;i++)
    {
        fscanf(fin, "%d %d %d", (rgb+i*3+0), (rgb+i*3+1), (rgb+i*3+2));
//        printf("%d : %d %d %d\n", i, rgb[i*3+0], rgb[i*3+1], rgb[i*3+2]);
    }

    fclose(fin);

    printf("readPPM_P6 : %s.\n", filename);
}

void savePPM_P6(char* filename, uint8 *img, int wid, int hgt)
{
    FILE *fout = NULL;
    int i;

    fout = fopen(filename, "wb");
    if (fout == NULL)
    {
        printf("savePPM_P6 Error : %s cannot open.\n", filename);
        return;
    }

    fprintf(fout, "P6\n# Created by Kevin\n%d %d\n255\n", wid, hgt);
    fwrite(img, 1, wid*hgt*3, fout);

    fclose(fout);
    printf("savePPM_P6 : %s.\n", filename);
}

void readPGM_P2_U16(char* filename, uint16 *gray, int wid, int hgt)
{
    FILE *fin = NULL;
    int i, range;
    char temp[100];

    fin = fopen(filename, "rt");
    if (fin == NULL)
    {
        printf("readPGM_P2_U16 Error : %s cannot open.\n", filename);
        return;
    }
 
    fgets(temp, 100, fin); //printf("%s", temp);
    fgets(temp, 100, fin); //printf("%s", temp);
    fgets(temp, 100, fin); //printf("%s", temp);
    fgets(temp, 100, fin); //printf("%s", temp);
    
	for (i=0;i<wid*hgt;i++)
	{
        fscanf(fin, "%d,", gray+i);
        //printf("%d\t", gray[i]);
	}

    fclose(fin);

    printf("readPGM_P2_U16 : %s.\n", filename);
}

void savePGM_P2_U16(char* filename, uint16 *gray, int wid, int hgt, uint16 max)
{
    FILE *fout = NULL;
    int i, range;
    char temp[100];

    fout = fopen(filename, "wt");
    if (fout == NULL)
    {
        printf("savePGM_P2_U16 Error : %s cannot open.\n", filename);
        return;
    }
 
    fprintf(fout, "P2\n# Created by Kevin\n%d %d\n%d\n", wid, hgt, max);

    for (i=0;i<wid*hgt;i++)
    {
        fprintf(fout, "%d\n", gray[i]);
        //printf("%d\t", gray[i]);
    }

    fclose(fout);

    printf("savePGM_P2_U16 : %s.\n", filename);
}

void readPGM_P5_U24(char* filename, uint8 *rgb, int wid, int hgt)
{
    FILE *fin = NULL;
    int i, range;
    char temp[100];
    uint8 *gray;

    gray = (uint8*)calloc(wid*hgt,1);
    fin = fopen(filename, "rb");
    if (fin == NULL)
    {
        printf("readPGM_P5_U24 Error : %s cannot open.\n", filename);
        return;
    }
 
    fgets(temp, 100, fin); //printf("%s", temp);
    fgets(temp, 100, fin); //printf("%s", temp);
    fgets(temp, 100, fin); //printf("%s", temp);
    fgets(temp, 100, fin); //printf("%s", temp);
    fread(gray, 1, wid*hgt, fin);
    fclose(fin);

    for (i=0;i<wid*hgt;i++)
    {
        rgb[i*3+0] = rgb[i*3+1] = rgb[i*3+2] = gray[i];
    }
    free(gray);

    printf("readPGM_P5_U24 : %s.\n", filename);
}

void readPGM_P5_U8(char* filename, uint8 *gray, int wid, int hgt)
{
    FILE *fin = NULL;
    int i, range;
    char temp[100];

    fin = fopen(filename, "rb");
    if (fin == NULL)
    {
        printf("readPGM_P5_U8 Error : %s cannot open.\n", filename);
        return;
    }
 
    fgets(temp, 100, fin); //printf("%s", temp);
    fgets(temp, 100, fin); //printf("%s", temp);
    fgets(temp, 100, fin); //printf("%s", temp);
    fgets(temp, 100, fin); //printf("%s", temp);
    fread(gray, 1, wid*hgt, fin);
    fclose(fin);

    printf("readPGM_P5_U8 : %s.\n", filename);
}

void savePPM_P6_F(char* filename, float *weight, int wid, int hgt)
{
	int i;
	float min = 1, max = 0;
	uint8 imgDat;
	uint8 *img;

	img = (uint8*)calloc(wid*hgt*3, 1);

	for (i=0;i<wid*hgt;i++)
	{
		if (weight[i] < min) min = weight[i];
		if (weight[i] > max) max = weight[i];
	}
	printf("Min:%7.5f, Max:%7.5f\n", min, max);

	for (i=0;i<wid*hgt;i++)
	{
		imgDat = (uint8)((weight[i]-min)/(max-min)*255.0);
		img[i*3+0] = img[i*3+1] = img[i*3+2] = imgDat;
	}

	savePPM_P6(filename, img, wid, hgt);
	free(img);
	
	printf("savePPM_P6_F : %s.\n", filename);
}

void savePPM_P6_U8(char* filename, uint8 *img8, int wid, int hgt)
{
    int i;
    uint8 min = 0xff, max = 0;
    uint8 imgDat;
    uint8 *img;

    img = (uint8*)calloc(wid*hgt*3, 1);

    for (i=0;i<wid*hgt;i++)
    {
        if (img8[i] < min) min = img8[i];
        if (img8[i] > max) max = img8[i];
    }
    printf("Normalize - Min:%d, Max:%d\n", min, max);

    for (i=0;i<wid*hgt;i++)
    {
        if (min==max) imgDat = 0;
        else imgDat = (uint8)((img8[i]-min)*255/(max-min));
        img[i*3+0] = img[i*3+1] = img[i*3+2] = imgDat;
    }

    savePPM_P6(filename, img, wid, hgt);
    free(img);
    printf("savePPM_P6_U8 : %s.\n", filename);
}

void savePPM_P6_U16(char* filename, uint16 *img16, int wid, int hgt)
{
    int i;
    uint16 min = 0xffff, max = 0;
    uint8 imgDat;
    uint8 *img;

    img = (uint8*)calloc(wid*hgt*3, 1);

    for (i=0;i<wid*hgt;i++)
    {
        if (img16[i] < min) min = img16[i];
        if (img16[i] > max) max = img16[i];
    }
    printf("Normalize - Min:%d, Max:%d\n", min, max);

    for (i=0;i<wid*hgt;i++)
    {
        if (min==max) imgDat = 0;
        else imgDat = (uint8)((img16[i]-min)*255/(max-min));
        img[i*3+0] = img[i*3+1] = img[i*3+2] = imgDat;
    }

    savePPM_P6(filename, img, wid, hgt);
    free(img);
    printf("savePPM_P6_U16 : %s.\n", filename);
}

int getImgType(char *filename)
{
    FILE *fin = NULL;
    int type;
    char temp[100];

    fin = fopen(filename, "rb");
    if (fin == NULL)
    {
        printf("getImgType Error : %s cannot open.\n", filename);
        return 0;
    }
 
    fscanf(fin, "%s", temp);
    type = temp[1] - '0';

    if (type<1 || type>6)
    {
        printf("Not Supported Type : %s\n", temp);
        return 0;
    }

    fclose(fin);
    printf("getImgType : %s - P%d.\n", filename, type);
    
    return type;
}

int getImgRange(char *filename)
{
    FILE *fin = NULL;
    int range;
    char temp[100];

    fin = fopen(filename, "rb");
    if (fin == NULL)
    {
        printf("getImgType Error : %s cannot open.\n", filename);
        return 0;
    }
 
    fgets(temp, 100, fin); //printf("%s", temp);
    fgets(temp, 100, fin); //printf("%s", temp);
    fgets(temp, 100, fin); //printf("%s", temp);
    fgets(temp, 100, fin); //printf("%s", temp);
    range = atoi(temp);

    fclose(fin);
    printf("getImgRange : %d\n", range);
    
    return range;
}

void getImgSize(char *filename, S_IMG_SIZE *size)
{
    FILE *fin = NULL;
    char temp[100];

    fin = fopen(filename, "rb");
    if (fin == NULL)
    {
        printf("getImgSize Error : %s cannot open.\n", filename);
        return ;
    }
 
    fscanf(fin, "%s\n", temp);
    fgets(temp, 100, fin); //printf("%s", temp);
    fscanf(fin, "%d %d\n", &size->width, &size->height);

    fclose(fin);
    printf("getImgSize : %s - (%d, %d)\n", filename, size->width, size->height);
}

void saveTxt_Float(char *filename, float *f, int len)
{
    FILE *fout = NULL;
    int i;

    fout = fopen(filename, "wt");
    if (fout == NULL)
    {
        printf("saveTxt_Float Error : %s cannot open.\n", filename);
        return;
    }

    for (i=0;i<len;i++)
    {
        fprintf(fout, "%10.3f\n", f[i]);
    }

    fclose(fout);
    printf("saveTxt_Float : %s.\n", filename);
}

void readTxt_Float(char *filename, float *f, int len)
{
    FILE *fin = NULL;
    int i;

    fin = fopen(filename, "rt");
    if (fin == NULL)
    {
        printf("readTxt_Float Error : %s cannot open.\n", filename);
        return;
    }

    for (i=0;i<len;i++)
    {
        fscanf(fin, "%f\n", &f[i]);
    }

    fclose(fin);
    printf("readTxt_Float : %s.\n", filename);
}

void saveTxt_Uint16(char *filename, uint16 *dat, int len)
{
    FILE *fout = NULL;
    int i;

    fout = fopen(filename, "wt");
    if (fout == NULL)
    {
        printf("saveTxt_Uint16 Error : %s cannot open.\n", filename);
        return;
    }

    for (i=0;i<len;i++)
    {
        fprintf(fout, "%5d\n", dat[i]);
    }

    fclose(fout);
    printf("saveTxt_Uint16 : %s.\n", filename);
}

void readTxt_Uint16(char *filename, uint16 *dat, int len)
{
    FILE *fin = NULL;
    int i;

    fin = fopen(filename, "rt");
    if (fin == NULL)
    {
        printf("readTxt_Uint16 Error : %s cannot open.\n", filename);
        return;
    }

    for (i=0;i<len;i++)
    {
        fscanf(fin, "%d\n", &dat[i]);
    }

    fclose(fin);
    printf("readTxt_Uint16 : %s.\n", filename);
}
