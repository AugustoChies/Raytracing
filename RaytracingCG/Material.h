#pragma once


class Material
{
public:
	Material(int dr,int dg, int db, int er, int eg, int eb,float specularq,
		int ar, int ag, int ab, float refl,float refra , float refraq);
	~Material();
	int getDifuseColor();
	int getSpecularColor();
	int getAmbientColor();
	float getReflectiveness();
	float getRefractiveness();
	float getRefractionQuo();
	float getAlpha();
	float getSpecularQuo();

protected:
	int difuse_color; 
	int specular_color;
	int ambient_color;

	float reflectiveness;
	float refractionvalue;
	float alpha;
	float  refraquo;

	float specularquo;	
};

