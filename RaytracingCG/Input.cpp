#include "Input.h"



Input::Input()
{
}


Input::~Input()
{
}

Image* Input::loadImage(const char* file)
{
	Image *readimg;
	int a, r, g, b;
	ifstream arq(file);
	char buffer[500];
	arq >> buffer;
	bool modo = buffer[1] == '7';
	int w, h;
	arq >> buffer;
	if (buffer[0] == '#')
	{
		arq.getline(buffer, 500);
		arq >> w;
	}
	else
	{
		w = atoi(buffer);
	}
	arq >> h;

	readimg = new Image(w, h);
	int maxvalue;
	arq >> maxvalue;
	if (modo)
	{
		for (int y = h - 1; y >= 0; y--)
		{
			for (int x = 0; x < w; x++)
			{
				arq >> a >> r >> g >> b;
				readimg->setPixel(r, g, b, x, y);
			}
		}
	}
	arq.close();

	return readimg;
}

Render* Input::loadScene(const char * sfile)
{
	Render* rend;
	ifstream arq(sfile);
	char buffer[100];
	arq >> buffer;
	bool modo = buffer[1] == 't';
	
	int lightcount;
	vector <Lightsource> arqlights;
	float x, y, z;
	int r, g, b;
	int er, eg, eb;

	arq >> lightcount;
	for (int i = 0; i < lightcount; i++)
	{
		arq >> x >> y >> z;
		arq >> r >> g >> b;
		arq >> er >> eg >> eb;

		glm::vec3 pos(x, y, z);

		Lightsource newlight(pos,r,g,b,er,eg,eb);
		arqlights.push_back(newlight);
	}

	vector <Material*> arqmats;
	int matcount;

	int dr, dg, db;
	int ar, ag, ab;
	
	float specularq;
	float refl;
	float refra, refraq;
	float alph;

	arq >> matcount;
	for (int i = 0; i < matcount; i++)
	{
		arq >> dr >> dg >> db;
		arq >> er >> eg >> eb >> specularq;
		arq >> ar >> ag >> ab;
		arq >> refl >> refra >> refraq;

		Material *nmat = new Material(dr, dg, db, er, eg, eb, specularq, ar, ag, ab, refl, refra, refraq);
		arqmats.push_back(nmat);
	}

	vector <Object*> arqobjs;
	int objcount;
	int type;
	int matindex;
	int id;
	float radiusX, radiusY, radiusZ;

	arq >> objcount;

	for (int i = 0; i < objcount; i++)
	{
		arq >> type;

		if (type == 0)
		{
			arq >> x >> y >> z;
			arq >> matindex;
			arq >> radiusX;
			arq >> id;

			glm::vec3 pos(x, y, z);

			Object *nobj = new Sphere(pos, arqmats[matindex], radiusX, id);

			arqobjs.push_back(nobj);
		}
	}
	
	arq >> r >> g >> b;
	int global_l = (r << 16) | (g << 8) | b;
	arq >> r >> g >> b;
	int background = (r << 16) | (g << 8) | b;

	arq >> buffer;
	bool npr = buffer[0] == 'n';

	arq >> r >> g >> b;
	arq >> type;
	bool ischalk = type == 1;

	int max_iterations;
	if (modo)
	{
		arq >> max_iterations;
		rend = new Raytrace(arqlights, arqobjs, global_l, background, max_iterations, npr, r, g, b, ischalk);
	}
	else
	{
		rend = new Raycast(arqlights, arqobjs,global_l,background);
	}

	arq.close();

	return rend;
}