#pragma once
#include "Render.h"
class Raytrace : public Render
{
public:
	Raytrace(vector <Lightsource> ls, vector<Object*> objs, int local_l, int background, int it);
	~Raytrace();
	void run(Image *image, float fov);
	int traceRay(glm::vec3 origin, glm::vec3 dir, int iteration, bool isrefraction, int refraid);
	

protected:
	int max_iterations;
};

