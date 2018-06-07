#include "Render.h"



Render::Render()
{
}


Render::~Render()
{
}

int Render::VecToColor(glm::vec3 v)
{
	int r=  (v.x * 255);
	int g = (v.y * 255);
	int b = (v.z * 255);

	int rgb = (r << 16) | (g << 8) | b;

	return rgb;
}

glm::vec3 Render::blendColor(glm::vec3 c1, glm::vec3 c2, float blend_q)
{
	glm::vec3 result(0, 0, 0);
	result.x = c1.x * (1 - blend_q) + c2.x * blend_q;
	result.y = c1.y * (1 - blend_q) + c2.y * blend_q;
	result.z = c1.z * (1 - blend_q) + c2.z * blend_q;

	return result;
}

glm::vec3 Render::reflection(glm::vec3 vec, glm::vec3 normal)
{
	glm::vec3 reflection;

	
	vec = glm::normalize(vec);
	vec *= -1;

	normal = glm::normalize(normal);
	/*float cos = glm::dot(normal,vec);


	reflection.x = 2 * normal.x * (cos)-vec.x;
	reflection.y = 2 * normal.y * (cos)-vec.y;
	reflection.z = 2 * normal.z * (cos)-vec.z;
	*/

	reflection = glm::reflect(vec, normal);

	return reflection;
}

glm::vec3 Render::refraction(glm::vec3 vec, glm::vec3 normal, float c1, float c2)
{
	glm::vec3 refraction;

	vec = glm::normalize(vec);

	normal = glm::normalize(normal);

	/*float cos1 = glm::dot(normal,vec);
	cos1 *= -1;
	float cos2 = sqrt(1 - ((c1 / c2) * (c1 / c2)) * (1 - (cos1 * cos1)));

	if (cos1 >= 0)
	{
		refraction.x = vec.x * (c1 / c2) + normal.x * ((c1 / c2) * cos1 - cos2);
		refraction.y = vec.y * (c1 / c2) + normal.y * ((c1 / c2) * cos1 - cos2);
		refraction.z = vec.z * (c1 / c2) + normal.z * ((c1 / c2)* cos1 - cos2);
	}
	else
	{
		refraction.x = vec.x * (c1 / c2) + normal.x * ((c1 / c2) * cos1 + cos2);
		refraction.y = vec.y * (c1 / c2) + normal.y * ((c1 / c2) * cos1 + cos2);
		refraction.z = vec.z * (c1 / c2) + normal.z * ((c1 / c2) * cos1 + cos2);
		
	}*/

	refraction = glm::refract(vec, normal, c1 / c2);

	
	return refraction;

	
}
