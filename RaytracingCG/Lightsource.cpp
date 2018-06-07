#include "Lightsource.h"



Lightsource::Lightsource(glm::vec3 pos, int dr, int dg, int db, int er, int eg, int eb)
{	
		position = pos;
		difuse_color = (dr << 16) | (dg << 8) | db;	
		specular_color = (er << 16) | (eg << 8) | eb;
}


Lightsource::~Lightsource()
{
}
