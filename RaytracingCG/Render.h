#pragma once
#include <vector>
#include "Lightsource.h"
#include "Sphere.h"
#include "Image.h"
#include <glm/glm.hpp>

using namespace std;


class Render
{
public:
	Render();
	~Render();
	virtual void run(Image *image,float fov) = 0;
	int VecToColor(glm::vec3 v);
	glm::vec3 blendColor(glm::vec3 c1, glm::vec3 c2 , float blend_q);//0 tudo primeira, 1 tudo segunda
	glm::vec3 refraction(glm::vec3 vec, glm::vec3 normal, float c1, float c2);
	glm::vec3 reflection(glm::vec3 vec, glm::vec3 normal);

protected:
	
	vector <Lightsource> lights;
	vector <Object*> objects;
	int global_lighting;
	int background_color;
};

