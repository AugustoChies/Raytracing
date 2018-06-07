#pragma once
#include "Render.h"
class Raycast : public Render
{
public:
	Raycast(vector <Lightsource> ls, vector<Object*> objs,int global_l,int background);
	~Raycast();
	void run(Image *image,float fov);
	int castRay(glm::vec3 origin, glm::vec3 dir);
};

