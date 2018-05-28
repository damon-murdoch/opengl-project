#ifndef _IMAGE_CLASS
#define _IMAGE_CLASS

class Image{
public:
	int x,y,n;
	unsigned char * data;

	Image::Image();
	Image::Image(char * filename);
	
	void Image::Free();

	bool Image::load_image(char * filename);

};

#endif // _IMAGE_CLASS