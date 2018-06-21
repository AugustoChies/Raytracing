#pragma once
#include "Render.h"
#include "Filter.h"
class Raytrace : public Render
{
public:
	Raytrace(vector <Lightsource> ls, vector<Object*> objs, int local_l, int background, int it,bool npr);
	~Raytrace();
	void run(Image *image, float fov);
	int traceRay(glm::vec3 origin, glm::vec3 dir, int iteration, bool isrefraction, int refraid);
	Image* NPRmix(Image * image);
	

protected:
	int max_iterations;
	bool isNPR;
	Image * borderimage;
};

