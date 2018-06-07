#pragma once
#include "Object.h"

class Elipsoid : public Object
{
public:
	Elipsoid(glm::vec3 pos, Material *m, float raioX, float raioY, float raioZ, int id_);
	~Elipsoid();
	glm::vec3 coltest(glm::vec3 porigem, glm::vec3 ray, float& t, int& colisao, glm::vec3& normal);
	
protected:
	float radiusX;
	float radiusY;
	float radiusZ;
};

