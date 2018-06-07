#pragma once
#include "glm\glm.hpp"


class Lightsource
{
public:
	Lightsource(glm::vec3 pos, int dr, int dg, int db,int er,int eg,int eb);	
	~Lightsource();

	glm::vec3 position;
	int difuse_color;
	int specular_color;
};

