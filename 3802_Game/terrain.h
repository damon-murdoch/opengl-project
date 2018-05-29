#ifndef _INCLUDE_TERRAIN
#define _INCLUDE_TERRAIN

#include "common.h"
#include "image.h"

class Terrain{
public:
	float x,y,z,width,height,length;
	Image Heightmap_Img,Texture_Img;
	GLuint Heightmap,Texture,Resolution;
	tVector3 * Indexes;

	Terrain::Terrain();
	Terrain::Terrain(float x, float y, float z, float width, float height, float length);
	Terrain::Terrain(float x, float y, float z, float width, float height, float length,char*heightmap_file,char*texture_file);

	void Terrain::Render();
	void Terrain::Free();
	void Terrain::Init(float x, float y, float z, float width, float height, float length);
	void Terrain::Load_Image(char*heightmap_file,char*texture_file);
};

#endif // _INCLUDE_TERRAIN