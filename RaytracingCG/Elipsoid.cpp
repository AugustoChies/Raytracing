#include "Elipsoid.h"



Elipsoid::Elipsoid(glm::vec3 pos, Material *m, float raioX, float raioY, float raioZ, int id_)
{
	position = pos;
	mat = m;
	radiusX = raioX;
	radiusY = raioY;
	radiusZ = raioZ;
	id = id_;
}


Elipsoid::~Elipsoid()
{
}


glm::vec3 Elipsoid::coltest(glm::vec3 porigem, glm::vec3 ray, float& t, int& colisao, glm::vec3& normal)
{
	glm::vec3 intpoint(0,0,0);
	float a, b, c, d, e, f, g, h, i, j;

	a = 1 / pow(radiusX, 2);
	b = 1 / pow(radiusY, 2);
	c = 1 / pow(radiusZ, 2);
	d = 0;
	e = 0;
	f = 0;
	g = -2 * position.x / pow(radiusX, 2);
	h = -2 * position.y / pow(radiusY, 2);
	i = -2 * position.z / pow(radiusZ, 2);
	j = pow(position.x,2)/ pow(radiusX,2) + pow(position.y, 2) / pow(radiusY, 2) + pow(position.z, 2) / pow(radiusZ, 2)-1;
	
	
	float aq = a* pow(ray.x, 2) + b *  pow(ray.y, 2) + c* pow(ray.z, 2) + d*ray.x * ray.y + e*ray.x * ray.z + f*ray.y * ray.z;
	float bq = 2 * a*porigem.x *ray.x + 2 * b*porigem.y*ray.y + 2 * c*porigem.z*ray.z + d * (porigem.x*ray.y + porigem.y*ray.x) + 
		e * (porigem.x * ray.z + porigem.z * ray.x) + f * (porigem.y * ray.z + porigem.z * ray.y) + g * ray.x + h * ray.y + i * ray.z;
	float cq = a * pow(porigem.x, 2) + b * pow(porigem.y, 2) + c * pow(porigem.z, 2) + d * porigem.x * porigem.y + e * porigem.x * porigem.z +
		f * porigem.y * porigem.z + g * porigem.x + h * porigem.y + i * porigem.z + j;

	if (aq == 0)
	{
		t = (-1) * cq / bq;
	}
	else
	{
		float delta = 2 * bq - 4 * aq*cq;
		if (delta == 0)
		{

		}
	}


	return intpoint;
}

