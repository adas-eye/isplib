#include <stdio.h>
#include <stdlib.h>
#include "type.h"

void bindRGB(uint8 *r, uint8 *g, uint8 *b, uint8 *rgb, int wid, int hgt)
{
	int i;

	for (i=0;i<wid*hgt;i++)
	{
		rgb[i*3+0] = r[i];
		rgb[i*3+1] = g[i];
		rgb[i*3+2] = b[i];
	}
}

void splitRGB(uint8 *rgb, uint8 *r, uint8 *g, uint8 *b
	         , int wid, int hgt)
{
	int i;

	for (i=0;i<wid*hgt;i++)
	{
		r[i] = rgb[i*3+0];
		g[i] = rgb[i*3+1];
		b[i] = rgb[i*3+2];
	}	
}

void splitRGBY(uint8 *rgb, uint8 *r, uint8 *g, uint8 *b, uint8 *y
	         , int wid, int hgt)
{
	int i;

	for (i=0;i<wid*hgt;i++)
	{
		r[i] = rgb[i*3+0];
		g[i] = rgb[i*3+1];
		b[i] = rgb[i*3+2];
		y[i] = (r[i] + g[i] + b[i])/3;
	}	
}

void bindRGB16(uint16 *r, uint16 *g, uint16 *b, uint8 *rgb, int wid, int hgt)
{
	int i;

	for (i=0;i<wid*hgt;i++)
	{
		rgb[i*3+0] = r[i];
		rgb[i*3+1] = g[i];
		rgb[i*3+2] = b[i];
	}
}

void splitRGB16(uint8 *rgb, uint16 *r, uint16 *g, uint16 *b
	         , int wid, int hgt)
{
	int i;

	for (i=0;i<wid*hgt;i++)
	{
		r[i] = rgb[i*3+0];
		g[i] = rgb[i*3+1];
		b[i] = rgb[i*3+2];
	}	
}

void splitRGBY16(uint8 *rgb, uint16 *r, uint16 *g, uint16 *b, uint16 *y
	         , int wid, int hgt)
{
	int i;

	for (i=0;i<wid*hgt;i++)
	{
		r[i] = rgb[i*3+0];
		g[i] = rgb[i*3+1];
		b[i] = rgb[i*3+2];
		y[i] = (r[i] + g[i] + b[i])/3;
	}	
}

