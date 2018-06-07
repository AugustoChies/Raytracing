#pragma once
#include "glm\glm.hpp"
#include "Material.h"

class Object
{
public:
	Object();
	~Object();
	virtual glm::vec3 coltest(glm::vec3 porigem, glm::vec3 ray, float& t, int& colisao, glm::vec3& normal) = 0;
	Material* getMaterial();
	int getId();

protected:
	glm::vec3 position;
	Material * mat;
	int id;
};

