#include "Raycast.h"



Raycast::Raycast(vector <Lightsource> ls, vector<Object*> objs, int global_l,int background)
{
	lights = ls;
	objects = objs;
	global_lighting = global_l;
	background_color = background;
}


Raycast::~Raycast()
{
}

int Raycast::castRay(glm::vec3 origin, glm::vec3 dir)
{
	int rgb=0;
	vector <float> ts;
	vector <Object*> hitobjs;
	vector<glm::vec3> colisions;
	vector<glm::vec3> normals;
	//vector<Lightsource> gotlights;
	glm::vec3 collide_point;
	glm::vec3 normal;
	int collide;
	float t;

	for (int i = 0; i < objects.size(); i++)
	{
		
		collide_point = objects[i]->coltest(origin,dir,t,collide,normal);
		if (collide == 1)
		{
			ts.push_back(t);
			hitobjs.push_back(objects[i]);
			colisions.push_back(collide_point);
			normals.push_back(normal);
		}
		
	}

	float nearestvalue = FLT_MAX;
	int nearestid = 0;
	if (ts.size() > 0)
	{
		for (int i = 0; i < ts.size(); i++)
		{
			if (ts[i] < nearestvalue)
			{
				nearestvalue = ts[i];
				nearestid = i;
			}
		}

		collide_point = colisions[nearestid];
		normal = normals[nearestid];
		
		//luz ambiente
		float airo = (float)((hitobjs[nearestid]->getMaterial()->getAmbientColor() >> 16) & 0xff) / 255;
		float aigo = (float)((hitobjs[nearestid]->getMaterial()->getAmbientColor() >> 8) & 0xff) / 255;
		float aibo = (float)(hitobjs[nearestid]->getMaterial()->getAmbientColor() & 0xff) / 255;

		float airl = (float)((global_lighting >> 16) & 0xff) / 255;
		float aigl = (float)((global_lighting >> 8) & 0xff) / 255;
		float aibl = (float)(global_lighting  & 0xff) / 255;

		glm::vec3 ambient_intensity(airo * airl, aigo *aigl, aibo * aibl);
		glm::vec3 diffuse_intensity(0,0,0);
		glm::vec3 specular_intensity(0, 0, 0);
		
		for (int k = 0; k < lights.size(); k++)
		{
			//luz difusa
			glm::vec3 lightdirection = lights[k].position - colisions[nearestid];
			lightdirection = glm::normalize(lightdirection);

			float dotproduct = glm::dot(normals[nearestid],lightdirection);
			dotproduct = glm::clamp(dotproduct, 0.0f, 1.0f);

			float diro = (float)((hitobjs[nearestid]->getMaterial()->getDifuseColor() >> 16) & 0xff) / 255;
			float digo = (float)((hitobjs[nearestid]->getMaterial()->getDifuseColor() >> 8) & 0xff) / 255;
			float dibo = (float)(hitobjs[nearestid]->getMaterial()->getDifuseColor() & 0xff) / 255;

			float dirl = (float)((lights[k].difuse_color >> 16) & 0xff) / 255;
			float digl = (float)((lights[k].difuse_color >> 8) & 0xff) / 255;
			float dibl = (float)(lights[k].difuse_color & 0xff) / 255;

			diffuse_intensity.x += diro * dirl * dotproduct;
			diffuse_intensity.y += digo * digl * dotproduct;
			diffuse_intensity.z += dibo * dibl * dotproduct;
			
			//luz especular
			glm::vec3 refl = reflection(lightdirection,normals[nearestid]);
			refl = glm::normalize(refl);
			glm::vec3 toviewer = colisions[nearestid] - origin;
			toviewer = glm::normalize(toviewer);

			dotproduct = glm::dot(refl,toviewer);
			dotproduct = glm::clamp(dotproduct, 0.0f, 1.0f);

			if (dotproduct > 0.0f)
			{
				float specular_factor = pow(dotproduct, hitobjs[nearestid]->getMaterial()->getSpecularQuo());

				float siro = (float)((hitobjs[nearestid]->getMaterial()->getSpecularColor() >> 16) & 0xff) / 255;
				float sigo = (float)((hitobjs[nearestid]->getMaterial()->getSpecularColor() >> 8) & 0xff) / 255;
				float sibo = (float)(hitobjs[nearestid]->getMaterial()->getSpecularColor() & 0xff) / 255;

				float sirl = (float)((lights[k].specular_color >> 16) & 0xff) / 255;
				float sigl = (float)((lights[k].specular_color >> 8) & 0xff) / 255;
				float sibl = (float)(lights[k].specular_color & 0xff) / 255;

				specular_intensity.x += siro * sirl * specular_factor;
				specular_intensity.y += sigo * sigl * specular_factor;
				specular_intensity.z += sibo * sibl * specular_factor;
			}


		}
		//diffuse_intensity = diffuse_intensity / lights.size();
		//specular_intensity = specular_intensity / lights.size();

		glm::vec3 final_color(0, 0, 0);
		

		//final_color.x = (ambient_intensity.x + diffuse_intensity.x + specular_intensity.x)/3;
		//final_color.y = (ambient_intensity.y + diffuse_intensity.y + specular_intensity.y)/3;
		//final_color.z = (ambient_intensity.z + diffuse_intensity.z + specular_intensity.z)/3;
		
		
		final_color.x = glm::min((ambient_intensity.x + diffuse_intensity.x + specular_intensity.x),1.0f);
		final_color.y = glm::min((ambient_intensity.y + diffuse_intensity.y + specular_intensity.y), 1.0f);
		final_color.z = glm::min((ambient_intensity.z + diffuse_intensity.z + specular_intensity.z), 1.0f);

		int finalrgb = VecToColor(final_color);
		rgb = finalrgb;
	}
	else
	{
		rgb = background_color;
	}

	return rgb;
}

void Raycast::run(Image *image,float fov)
{
	glm::vec3 origin(0, 0, 0);

	
	float aspectratio = (float)image->getWidth() / (float)image->getHeight();
	float scale = tan(glm::radians(fov * 0.5));
	
	for (int i = 0; i < image->getWidth(); i++)
	{
		for (int j = 0; j < image->getHeight(); j++)
		{
			float x = (2 * (i + 0.5) / (float)image->getWidth() - 1) * aspectratio * scale;
			float y = (1 - 2 * (j + 0.5) / (float)image->getHeight()) * scale;
			float z = -1;

			glm::vec3 pixelpoint(x, y, z);

			glm::vec3 dir = pixelpoint - origin;
			dir = glm::normalize(dir);
			
			int newcolor = castRay(origin, dir);
			image->setPixel(newcolor, i, j);
		}
	}
}