#include "Raytrace.h"



Raytrace::Raytrace(vector <Lightsource> ls, vector<Object*> objs, int global_l, int background, int it,bool npr, int borderr, int borderg, int borderb,bool ischalk)
{
	lights = ls;
	objects = objs;
	global_lighting = global_l;
	background_color = background;
	max_iterations = it;
	isNPR = npr;
	bordercolor = (borderr << 16) | (borderg << 8) | borderb;
	chalk = ischalk;
}


Raytrace::~Raytrace()
{
}

int Raytrace::traceRay(glm::vec3 origin, glm::vec3 dir, int iteration, bool isrefraction, int refraid,int* borderimgcolor)
{
	int rgb = 0;
	vector <float> ts;
	vector <Object*> hitobjs;
	vector<glm::vec3> colisions;
	vector<glm::vec3> normals;
	
	glm::vec3 collide_point;
	glm::vec3 normal;
	int collide;
	float t;

	for (int i = 0; i < objects.size(); i++)
	{
		
		collide_point = objects[i]->coltest(origin, dir, t, collide, normal);
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
		float aibl = (float)(global_lighting & 0xff) / 255;
		

		glm::vec3 ambient_intensity(airo * airl, aigo *aigl, aibo * aibl);
		glm::vec3 diffuse_intensity(0, 0, 0);
		glm::vec3 specular_intensity(0, 0, 0);

		*borderimgcolor = VecToColor(ambient_intensity);

		for (int k = 0; k < lights.size(); k++)
		{
			//luz difusa
			glm::vec3 lightdirection = lights[k].position - colisions[nearestid];
			lightdirection = glm::normalize(lightdirection);
			//testa se bate em outro obj no meio do caminho
			bool bloqueado = false;

			float attenuation = 0;
			float distancetoblocker, distancetolight;
			for (int i = 0; i < objects.size(); i++)
			{
				collide_point = objects[i]->coltest(colisions[nearestid], lightdirection, t, collide, normal);
				if (collide == 1)
				{
					distancetoblocker = glm::distance(colisions[nearestid], collide_point);
					distancetolight = glm::distance(lights[k].position, collide_point);

					if (distancetoblocker < distancetolight)
					{
						bloqueado = true;
						attenuation = 1 / distancetoblocker * distancetoblocker;
						break;
					}
				}

			}

			//if(!bloqueado)
			//{
				float dotproduct = glm::dot(normals[nearestid], lightdirection);
				
				dotproduct = glm::clamp(dotproduct, 0.0f, 1.0f);
				
				float diro = (float)((hitobjs[nearestid]->getMaterial()->getDifuseColor() >> 16) & 0xff) / 255;
				float digo = (float)((hitobjs[nearestid]->getMaterial()->getDifuseColor() >> 8) & 0xff) / 255;
				float dibo = (float)(hitobjs[nearestid]->getMaterial()->getDifuseColor() & 0xff) / 255;
	
				float dirl = (float)((lights[k].difuse_color >> 16) & 0xff) / 255;
				float digl = (float)((lights[k].difuse_color >> 8) & 0xff) / 255;
				float dibl = (float)(lights[k].difuse_color & 0xff) / 255;
	
				if (isNPR)
				{
					if (dotproduct > 0.5 && !bloqueado)
					{
						diffuse_intensity.x += diro * dirl;
						diffuse_intensity.y += digo * digl;
						diffuse_intensity.z += dibo * dibl;
					}

				}
				else
				{
					diffuse_intensity.x += diro * dirl * dotproduct;
					diffuse_intensity.y += digo * digl * dotproduct;
					diffuse_intensity.z += dibo * dibl * dotproduct;
	
					if (bloqueado)
					{
						diffuse_intensity.x *= (1 - attenuation);
						diffuse_intensity.y *= (1 - attenuation);
						diffuse_intensity.z *= (1 - attenuation);
					}
				}
				//luz especular
				glm::vec3 refl = reflection(lightdirection, normals[nearestid]);
				refl = glm::normalize(refl);
				glm::vec3 toviewer = origin - colisions[nearestid];
				toviewer = glm::normalize(toviewer);
	
				dotproduct = glm::dot(refl, toviewer);
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
	
					if (bloqueado)
					{
						if (!isNPR)
						{
							specular_intensity.x *= (1 - attenuation);
							specular_intensity.y *= (1 - attenuation);
							specular_intensity.z *= (1 - attenuation);
						}
					}
				}
			//}
			

		}
	

		glm::vec3 final_color(0, 0, 0);


		//final_color.x = (ambient_intensity.x + diffuse_intensity.x + specular_intensity.x)/3;
		//final_color.y = (ambient_intensity.y + diffuse_intensity.y + specular_intensity.y)/3;
		//final_color.z = (ambient_intensity.z + diffuse_intensity.z + specular_intensity.z)/3;


		final_color.x = glm::min((ambient_intensity.x + diffuse_intensity.x + specular_intensity.x), 1.0f);
		final_color.y = glm::min((ambient_intensity.y + diffuse_intensity.y + specular_intensity.y), 1.0f);
		final_color.z = glm::min((ambient_intensity.z + diffuse_intensity.z + specular_intensity.z), 1.0f);

		glm::vec3 reflect_color(0, 0, 0);
		glm::vec3 refract_color(0, 0, 0);
		
		glm::vec3 combined_color = final_color;

		
		if (iteration < max_iterations && !isNPR)
		{
			if ((hitobjs[nearestid]->getMaterial()->getReflectiveness() > 0))
			{
				if (!isrefraction)
				{
					glm::vec3 newdir = reflection(dir, normals[nearestid]);
					newdir = colisions[nearestid] + newdir * 0.01f;
					newdir = glm::normalize(newdir);
					int reflrgb = traceRay(colisions[nearestid], newdir, iteration + 1, false, 0, borderimgcolor);
					reflect_color.x = ((reflrgb >> 16) & 0xff) / 255.0;
					reflect_color.y = ((reflrgb >> 8) & 0xff) / 255.0;
					reflect_color.z = (reflrgb & 0xff) / 255.0;

					combined_color = blendColor(combined_color, reflect_color, hitobjs[nearestid]->getMaterial()->getReflectiveness());
				}
			}
			if ((hitobjs[nearestid]->getMaterial()->getRefractiveness() > 0))
			{
				if (!isrefraction) //entra na refração
				{										
					glm::vec3 newdir = refraction(dir, normals[nearestid],1,hitobjs[nearestid]->getMaterial()->getRefractionQuo());
					newdir = colisions[nearestid] + newdir * 0.01f; 
					int refrrgb = traceRay(colisions[nearestid], newdir, iteration, true,hitobjs[nearestid]->getId(), borderimgcolor);
					refract_color.x = ((refrrgb >> 16) & 0xff) / 255.0;
					refract_color.y = ((refrrgb >> 8) & 0xff) / 255.0;
					refract_color.z = (refrrgb & 0xff) / 255.0;
					combined_color = blendColor(combined_color, refract_color, hitobjs[nearestid]->getMaterial()->getRefractiveness());
				}
				else
				{
					if (refraid == hitobjs[nearestid]->getId()) //sai da refração
					{
						glm::vec3 newdir = refraction(dir, normals[nearestid], hitobjs[nearestid]->getMaterial()->getRefractionQuo(),1);
						newdir = colisions[nearestid] + newdir * 0.01f;
						int refrrgb = traceRay(colisions[nearestid], newdir, iteration + 1, false, 0, borderimgcolor);
						refract_color.x = ((refrrgb >> 16) & 0xff) / 255.0;
						refract_color.y = ((refrrgb >> 8) & 0xff) / 255.0;
						refract_color.z = (refrrgb & 0xff) / 255.0;
						combined_color = blendColor(combined_color, refract_color, 1.0);
					}
				}
			}
		}
		

		int finalrgb = VecToColor(combined_color);

		

		rgb = finalrgb;
	}
	else
	{
		rgb = background_color;
		if (isNPR)
		{
			*borderimgcolor = background_color;
		}
	}

	

	return rgb;
}

void Raytrace::run(Image *image, float fov)
{
	glm::vec3 origin(0, 0, 0);
	if (isNPR)
	{
		borderimage = new Image(image->getWidth(), image->getHeight());
	}

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
			int borderimgcolor;

			int newcolor = traceRay(origin, dir,0,false,0,&borderimgcolor);
			image->setPixel(newcolor, i, j);
			if (isNPR)
			{
				borderimage->setPixel(borderimgcolor, i, j);
			}
			
		}
	}

	if (isNPR)
	{
		
		Filter::prewitt(borderimage);
		Filter::greyScale(borderimage);
		NPRmix(image);
	}
}

void Raytrace::NPRmix(Image * image)
{
	for (int x = 0; x < image->getWidth(); x++)
	{
		for (int y = 0; y < image->getHeight(); y++)
		{
			if(borderimage->getPixel(x,y) > 0)
				image->setPixel(bordercolor, x, y);
		}
	}

	if (chalk)
	{
		char *data = new char[image->getWidth() * image->getHeight() * 4];

		float xFactor = 1.0f / (image->getWidth() - 1);
		float yFactor = 1.0f / (image->getHeight() - 1);

		float a = 10;//modificaveis a,b e limit
		float b = 1;
		int limit = 250;

		for (int row = 0; row < image->getHeight(); row++) 
		{
			for (int col = 0; col < image->getWidth(); col++)
			{
				float x = xFactor * col;
				float y = yFactor * row;
				float sum = 0.0f;
				float freq = a;
				float scale = b;

				// Compute the sum for each octave
				for (int oct = 0; oct < 4; oct++) {
					glm::vec2 p(x * freq, y * freq);
					float val = 0.0f;
					val = glm::perlin(p, glm::vec2(freq)) / scale;
					sum += val;
					float result = (sum + 1.0f) / 2.0f;
					 
					// Store in texture buffer 
					data[((row * image->getWidth() + col) * 4) + oct] =	(char)(result * 255.0f);						
					
					
					freq *= 2.0f;   // Double the frequency
					scale *= b;     // Next power of b
				}
				if ((int)(data[((row * image->getWidth() + col) * 4) + 3]) + 128 > limit)
				{
					image->setPixel(background_color, col, row);
				}
				//int newgrey = (int)(data[((row * image->getWidth() + col) * 4) + 3]) + 128;
				//image->setPixel(newgrey, newgrey, newgrey, col, row);
			}
		}
	}
}