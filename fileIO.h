#include "type.h"

void readPPM_P6(char* filename, uint8 *img, int wid, int hgt);
void readPPM_P3(char* filename, uint8 *rgb, int wid, int hgt);
void savePPM_P6(char* filename, uint8 *img, int wid, int hgt);
void readPGM_P2_U16(char* filename, uint16 *gray, int wid, int hgt);
void savePGM_P2_U16(char* filename, uint16 *gray, int wid, int hgt, uint16 max);
void readPGM_P5_U24(char* filename, uint8 *rgb, int wid, int hgt);
void readPGM_P5_U8(char* filename, uint8 *gray, int wid, int hgt);
void savePPM_P6_F(char* filename, float *weight, int wid, int hgt);
void savePPM_P6_U8(char* filename, uint8 *img8, int wid, int hgt);
void savePPM_P6_U16(char* filename, uint16 *img16, int wid, int hgt);
int getImgType(char *filename);
int getImgRange(char *filename);
void getImgSize(char *filename, S_IMG_SIZE *size);
void saveTxt_Float(char *filename, float *f, int len);
void readTxt_Float(char *filename, float *f, int len);
void saveTxt_Uint16(char *filename, uint16 *dat, int len);

