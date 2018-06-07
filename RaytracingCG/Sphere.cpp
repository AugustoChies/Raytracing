#include "Sphere.h"



Sphere::Sphere(glm::vec3 pos, Material *m, float raio, int id_)
{
	position = pos;
	mat = m;
	radius = raio;
	id = id_;
}


Sphere::~Sphere()
{
}

glm::vec3 Sphere::coltest(glm::vec3 porigem, glm::vec3 ray, float& t, int& colisao, glm::vec3& normal)
{
	float raio = radius;
	glm::vec3 centro = position;

	ray = glm::normalize(ray);
	float a = 1;
	float b = 2 * (ray.x * (porigem.x - centro.x) + ray.y * (porigem.y - centro.y) + ray.z * (porigem.z - centro.z));
	float c = ((porigem.x - centro.x) * (porigem.x - centro.x)) + ((porigem.y - centro.y) * (porigem.y - centro.y)) +
		((porigem.z - centro.z) * (porigem.z - centro.z)) - (raio * raio);

	float delta = b*b - 4 * a * c;
	float t0, t1;
	glm::vec3 intpoint(0, 0, 0);

	if (delta < 0)
	{
		colisao = -1;
		return intpoint;//nao toca
	}
	else if (delta == 0)
	{
		colisao = 0;
		t0 = -1 * b;
		t = t0;
		if (t <= 0)
		{
			colisao = -1; //atras
		}
		else
		{
			intpoint = porigem + ray;
			intpoint *= t;
			intpoint.x -= centro.x;
			intpoint.y -= centro.y;
			intpoint.z -= centro.z;
		}
		return intpoint;//tangencia
	}
	colisao = 1;

	t0 = (-1 * b) - sqrt(delta) / 2;
	t1 = (-1 * b) + sqrt(delta) / 2;


	if (t0 < t1)
	{
		t = t0;

		if (t < 1)
		{
			colisao = -1; //atras
			if (t1 > 1)
			{
				colisao = 1;// pega o mais longe porque está passando por dentro do objeto
				t = t1;
			}
		}
		if (colisao == 1)
		{
			intpoint = porigem + ray;
			intpoint *= t;
			intpoint.x -= centro.x;
			intpoint.y -= centro.y;
			intpoint.z -= centro.z;

			normal = intpoint - centro;
			normal = normal / raio;
		}

		return intpoint;
	}
	else
	{
		t = t1;
		if (t < 1)
		{
			colisao = -1; //atras
			if (t0 > 0)
			{
				colisao = 1;
				t = t0;
			}
		}
		if (colisao == 1)
		{
			intpoint = porigem + ray;
			intpoint *= t;
			intpoint.x -= centro.x;
			intpoint.y -= centro.y;
			intpoint.z -= centro.z;
			normal = intpoint - centro;
			normal = normal / raio;
		}

		return intpoint;
	}

}

