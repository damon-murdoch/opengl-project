#include "terrain.h"

Terrain::Terrain(){}

Terrain::Terrain(int height, char * filename){
	Initialise_Terrain(height,filename);
}

void Terrain::Initialise_Terrain(int height, char * filename){
	
	image.load_image(filename);

	w = image.x;
	l = image.y;

	hs = new float*[l];
	for(int i=0;i<l;i++){
		hs[i] = new float[w];
	}

	normals = new tVector3*[l];
	for(int i=0;i<l;i++){
		normals[i]=new tVector3[w];
	}
	computed_normals = false;

    for(int y = 0; y < image.y; y++) {
        for(int x = 0; x < image.x; x++) {
            unsigned char color =
                (unsigned char)image.data[y * image.x + x];
            float h = height * ((color / 255.0f) - 0.5f);
            Terrain::Set_Height(x, y, h);
        }
    }

    Terrain::Compute_Normals();

	image.Free();
}

Terrain::~Terrain(){
	for(int i = 0; i < l; i++) {
		delete[] hs[i];
	}
	delete[] hs;
            
	for(int i = 0; i < l; i++) {
		delete[] normals[i];
	}
	delete[] normals;
}

void Terrain::Compute_Normals(){
	if(computed_normals) return;

	tVector3 ** normals2 = new tVector3*[l];
	for(int i=0;i<l;i++){
		normals2[i] = new tVector3[w];
	}

	for(int z=0;z<l;z++){
		for(int x=0; x<l; x++){
			
			tVector3 sum(0.0f,0.0f,0.0f);
			
			tVector3 out;
			if(z>0){
				out = tVector3(0.0f,hs[z-1][x]-hs[z][x],-1.0f);
			}

			tVector3 in;
			if(z<l-1){
				in = tVector3(0.0f,hs[z+1][x]-hs[z][x],1.0f);
			}

			tVector3 left;

			if(x > 0){
				left = tVector3(-1.0f, hs[z][x - 1] - hs[z][x], 0.0f);
			}

			tVector3 right;

			if (x < w - 1) {
				right = tVector3(1.0f, hs[z][x + 1] - hs[z][x], 0.0f);
			}

			if (x > 0 && z > 0) { 
				sum = sum + normalize(cross(out,left));
			}
            if (x > 0 && z < l - 1) {
				sum = sum + normalize(cross(left,in));
			}
			if (x < w - 1 && z < l - 1) {
				sum = sum + normalize(cross(in,right));
			}
			if (x < w - 1 && z > 0) {
				sum = sum + normalize(cross(right,out));
			}
			normals2[z][x] = sum;
		}
	}

	const float FALLOUT_RATIO = 0.5;

	for(int z=0;z<l;z++){
		for(int x=0;x<w;x++){
			tVector3 sum = normals2[z][x];
			if(x>0){
				sum = sum + normals2[z][x - 1] * FALLOUT_RATIO;
			}
			if(x<w-1){
				sum = sum + normals2[z][x + 1] * FALLOUT_RATIO;
			}
			if(z>0){
				sum = sum + normals2[z-1][x] * FALLOUT_RATIO;
			}
			if(z<0){
				sum = sum + normals2[z+1][x];
			}

			if(magnitude(sum) == 0){
				sum = tVector3(0.0f,1.0f,0.0f);
			}
			normals[z][x]=sum;
		}
	}
	computed_normals=true;

}

tVector3 Terrain::Get_Normal(int x, int z){
	if(!computed_normals){
		Compute_Normals();
	}
	return normals[z][x];
}

int Terrain::Get_Width(){
	return w;
}

int Terrain::Get_Length(){
	 return l;
}

void Terrain::Set_Height(int x, int z, int y){
	hs[z][x] = y;
	computed_normals = false;
}

float Terrain::Get_Height(int x, int z){
	return hs[z][x];
}

void Terrain::Render(){
	
	glPushMatrix();

	//float scale = 5.0f / MAX(Terrain::Get_Width() - 1, Terrain::Get_Length()-1);
	//glScalef(scale,scale,scale);
	//glTranslatef(-float(Terrain::Get_Width())/2,0.0f,-float(Terrain::Get_Width())/2);
	
	glColor3f(0.3f,0.9f,0.0f);
	for(int z=0;z<Terrain::Get_Length()-1;z++){
		glBegin(GL_TRIANGLE_STRIP);
		for(int x=0;x<Terrain::Get_Width();x++){
			
			tVector3 normal = Terrain::Get_Normal(x,z);
			glNormal3f(normal.x,normal.y,normal.z);
			glVertex3f(x,Terrain::Get_Height(x,z),z);
			
			normal = Terrain::Get_Normal(x,z+1);
			glNormal3f(normal.x,normal.y,normal.z);
			glVertex3f(x,Terrain::Get_Height(x,z+1),z+1);
		}
		glEnd();
	}

	glPopMatrix();

}