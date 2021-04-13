#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image::Image(){
	Image::x=0;
	Image::y=0;
	Image::n=0;
	Image::data=NULL;
}

Image::Image(char * filename){
	load_image(filename);
}

pixeldata Image::Get_Value_At_Pixel(int x, int y){
	unsigned byte_per_pixel = Image::n;
	unsigned char * pixel_offset = Image::data + (x + Image::x * y) * byte_per_pixel;
	pixeldata ret = {pixel_offset[0],pixel_offset[1],pixel_offset[2],(byte_per_pixel <=4 ? pixel_offset[3] : 0xff)};
	return ret;
}

bool Image::load_image(char * filename){
	
	Image::data = stbi_load(filename,&x,&y,&n,0);
	
	if(data!=NULL){
		fprintf(stdout,"%s opened successfully!\n",filename);
		return 0; // image loaded successfully
	}
	// image didnt load
	
	//if (MessageBox(NULL,L"Would You Like To Run In Fullscreen Mode?", L"Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO) {
	//	fullscreen=FALSE;
	//}

	fprintf(stdout,"%s could not be opened!\n",filename);

	Image::x=0;
	Image::y=0;
	Image::n=0;
	
	return 1;
}

void Image::Free(){
	stbi_image_free(data);
}