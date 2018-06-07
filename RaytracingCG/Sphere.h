#pragma once
#include "Object.h"
class Sphere : public Object
{
public:
	Sphere(glm::vec3 pos, Material *m, float raio,int id_);
	~Sphere();
	glm::vec3 coltest(glm::vec3 porigem, glm::vec3 ray, float& t, int& colisao, glm::vec3& normal);
	
protected:
	float radius;
};

