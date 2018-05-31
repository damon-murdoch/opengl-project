#ifndef _IMAGE_CLASS
#define _IMAGE_CLASS

#include "stb_image.h"

#define BITMAP_ID 04xD42

typedef struct pixdata{
	unsigned int r,g,b,a;
} pixeldata;

class Image{
public:
	int x,y,n;
	unsigned char * data;

	Image::Image();
	Image::Image(char * filename);
	
	void Image::Free();
	pixeldata Image::Get_Value_At_Pixel(int x, int y);
	bool Image::load_image(char * filename);

};

#endif // _IMAGE_CLASS