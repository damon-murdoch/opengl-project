#include "terrain.h"

Terrain::Terrain(){

}

Terrain::Terrain(float x, float y, float z, float width, float height, float length){
	Terrain::Init(x,y,z,width,height,length);
}

Terrain::Terrain(float x, float y, float z, float width, float height, float length,char * heightmap_file,char * texture_file){
	Terrain::Init(x,y,z,width,height,length);
	Terrain::Load_Image(heightmap_file,texture_file);
}

void Terrain::Render(){
	
	//glBindTexture(GL_TEXTURE_2D,Terrain::Texture);

	for (int i=Heightmap_Img.x;i<Heightmap_Img.x*Heightmap_Img.y;i++){
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f,0.0f); glVertex3f(Indexes[i].x,Indexes[i].y,Indexes[i].z);
			glTexCoord2f(0.0f,1.0f); glVertex3f(Indexes[i+1].x,Indexes[i+1].y,Indexes[i+1].z);
			glTexCoord2f(1.0f,0.1f); glVertex3f(Indexes[i-Heightmap_Img.x].x,Indexes[i-Heightmap_Img.x].y,Indexes[i-Heightmap_Img.x].z);
			glTexCoord2f(1.0f,1.0f); glVertex3f(Indexes[i-Heightmap_Img.x+1].x,Indexes[i-Heightmap_Img.x+1].y,Indexes[i-Heightmap_Img.x+1].z);
		}
		glEnd();
	}
}

void Terrain::Init(float x, float y, float z, float width, float height, float length){
	Terrain::x = x + width / 2;
	Terrain::y = y + height / 2;
	Terrain::z = z + length / 2;
	Terrain::width = width;
	Terrain::height = height;
	Terrain::length = length;
}

// terrain.load_image("img/terrain_map.png","img/terrain_tex.jpg");

void Terrain::Load_Image(char*heightmap_file,char*texture_file){
	Terrain::Heightmap_Img.load_image(heightmap_file);
	Terrain::Texture_Img.load_image(texture_file);

	Indexes = (tVector3*)malloc(Heightmap_Img.x*Heightmap_Img.y*sizeof(tVector3));

	for(int i=0;i<Heightmap_Img.x;i++){
		for(int j=0;j<Heightmap_Img.y;i++){
			Indexes[j+Heightmap_Img.x*i].x = i*(width/Heightmap_Img.x);
			Indexes[j+Heightmap_Img.x*i].y = (i+j);
			Indexes[j+Heightmap_Img.x*i].z = j*(length/Heightmap_Img.y);
		}
	}
}

void Terrain::Free(){
	free(Indexes);
}