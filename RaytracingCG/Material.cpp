#include "Material.h"



Material::Material(int dr, int dg, int db, int er, int eg, int eb, float specularq,
	int ar, int ag, int ab, float refl, float refra, float refraq)
{
	difuse_color = (dr << 16) | (dg << 8) | db;	
	specular_color = (er << 16) | (eg << 8) | eb;
	ambient_color = (ar << 16) | (ag << 8) | ab;
	specularquo = specularq;
	reflectiveness = refl;
	refractionvalue = refra;
	refraquo = refraq;
}


Material::~Material()
{
}

int Material::getDifuseColor()
{
	return difuse_color;
}

int Material::getSpecularColor()
{
	return specular_color;
}

int Material::getAmbientColor()
{
	return ambient_color;
}

float Material::getReflectiveness()
{
	return  reflectiveness;
}

float Material::getRefractiveness()
{
	return refractionvalue;
}

float Material::getRefractionQuo()
{
	return refraquo;
}

float Material::getAlpha()
{
	return alpha;
}

float Material::getSpecularQuo()
{
	return specularquo;
}