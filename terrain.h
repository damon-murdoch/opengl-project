#ifndef _INCLUDE_TERRAIN
#define _INCLUDE_TERRAIN

#include "common.h"
#include "image.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

class Terrain{
private:
	Image image;
	int w,l;
	float **hs;
	tVector3 ** normals;
	bool computed_normals;
public:
	Terrain::Terrain();
	Terrain::Terrain(int height, char * filename);
	void Terrain::Initialise_Terrain(int height, char * filename);
	Terrain::~Terrain();
	int Terrain::Get_Width();
	int Terrain::Get_Length();
	void Terrain::Compute_Normals();
	tVector3 Terrain::Get_Normal(int x, int z);
	void Terrain::Set_Height(int x, int z, int y);
	float Terrain::Get_Height(int x, int z);
	void Terrain::Render();
};

#endif // _INCLUDE_TERRAIN