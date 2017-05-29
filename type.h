#ifndef __TYPE_H__
typedef unsigned long   uint64; 
typedef unsigned int    uint32; 
typedef unsigned short  uint16; 
typedef unsigned char   uint8;
typedef char            bool;

typedef long   int64; 
typedef int    int32; 
typedef short  int16; 
typedef char   int8;

enum {
    false = 0,
    true
};

typedef struct {
	int width;
	int height;
} S_IMG_SIZE;

#endif
#define __TYPE_H__
