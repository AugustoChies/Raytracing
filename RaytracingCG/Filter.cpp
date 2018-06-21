#include "Filter.h"



Filter::Filter()
{
}


Filter::~Filter()
{
}

void Filter::blur(Image* image, int blurammount)
{
	Image *newimage = new Image(image->getWidth(), image->getHeight());

	for (int x = 0; x < image->getWidth(); x++)
	{
		for (int y = 0; y < image->getHeight(); y++)
		{
			newimage->setPixel(image->getPixel(x, y), x, y);
		}
	}

	for (int j = 0; j < blurammount; j++)
	{
		for (int x = 1; x < image->getWidth()-1; x++)
		{
			for (int y = 1; y < image->getHeight()-1; y++)
			{
				int nr, ng, nb;
				nr = nb = ng = 0;
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						nr += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 16) & 0xff) / 9;
						ng += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 8) & 0xff) / 9;
						nb += (image->getPixel(x + (i - 1), y + (j - 1)) & 0xff) / 9;
					}
				}
				newimage->setPixel(nr, ng, nb, x, y);
			}
		}


		for (int x = 0; x < image->getWidth(); x++)
		{
			for (int y = 0; y < image->getHeight(); y++)
			{
				image->setPixel(newimage->getPixel(x, y), x, y);
			}
		}
	}
}

void Filter::greyScale(Image* image)
{
	for (int x = 0; x < image->getWidth(); x++)
	{
		for (int y = 0; y < image->getHeight(); y++)
		{
			int px = image->getPixel(x, y);

			int r = (px >> 16) & 0xff;
			int g = (px >> 8) & 0xff;
			int b = (px) & 0xff;

			int nrgb = (((r + g + b) / 3) << 16) | (((r + g + b) / 3) << 8) | ((r + g + b) / 3);
			image->setPixel(nrgb, x, y);
		}
		
	}
}

void Filter::bioGreyScale(Image* image) // Experimento
{
	for (int x = 0; x < image->getWidth(); x++)
	{
		for (int y = 0; y < image->getHeight(); y++)
		{
			int px = image->getPixel(x, y);

			int r = (px >> 16) & 0xff;
			int g = (px >> 8) & 0xff;
			int b = (px)& 0xff;
			float fr = r/255.0;
			float fg = g / 255.0;
			float fb = b/ 255.0;

			fr *= 0.22;
			fg *= 0.71;
			fb *= 0.07;

			r = fr * 255;
			g = fg * 255;
			b = fb * 255;

			int nrgb = (((r + g + b) << 16) | ((r + g + b) << 8) | (r + g + b));
			image->setPixel(nrgb, x, y);
		}
	}
}

void Filter::RScale(Image* image)
{
	for (int x = 0; x < image->getWidth(); x++)
	{
		for (int y = 0; y < image->getHeight(); y++)
		{
			int px = image->getPixel(x, y);

			int r = (px >> 16) & 0xff;			

			int nrgb = (r << 16) | (r << 8) | r;
			image->setPixel(nrgb, x, y);
		}
	}
}

void Filter::GScale(Image* image)
{
	for (int x = 0; x < image->getWidth(); x++)
	{
		for (int y = 0; y < image->getHeight(); y++)
		{
			int px = image->getPixel(x, y);

			int g = (px >> 8) & 0xff;

			int nrgb = (g << 16) | (g << 8) | g;
			image->setPixel(nrgb, x, y);
		}
	}
}

void Filter::BScale(Image* image)
{
	for (int x = 0; x < image->getWidth(); x++)
	{
		for (int y = 0; y < image->getHeight(); y++)
		{
			int px = image->getPixel(x, y);

			int b = px  & 0xff;

			int nrgb = (b << 16) | (b << 8) | b;
			image->setPixel(nrgb, x, y);
		}
	}
}

void Filter::prewitt(Image * image)
{
	float horizontalf[3][3] = { {-1,1,-1},
								{ 0,0,0 },
								{1,-1,1 } };
	float verticalf[3][3] = { { 1,0,-1 },	
							  { -1,0,1 },
	                          { 1,0,-1 } };

	Image *newimageH = new Image(image->getWidth(), image->getHeight());
	Image *newimageV = new Image(image->getWidth(), image->getHeight());
	Image *newimageFull = new Image(image->getWidth(), image->getHeight());

	//HORIZONTAL
	for (int x = 1; x < image->getWidth()-1; x++)
	{
		for (int y = 1; y < image->getHeight()-1; y++)
		{
			int nr, ng, nb;
			float fnr, fng, fnb;
			nr = nb = ng = 0;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					nr += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 16) & 0xff) * horizontalf[j][i];
					ng += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 8) & 0xff) * horizontalf[j][i];
					nb += (image->getPixel(x + (i - 1), y + (j - 1)) & 0xff) * horizontalf[j][i];
				}
			}
			fnr = nr / 255.0;
			fng = ng / 255.0;
			fnb = nb / 255.0;
			glm::vec3 ccolor(fnr, fng, fnb);
			ccolor = glm::clamp(glm::vec3(ccolor), 0.0f, 255.0f);

			nr = ccolor.r * 255;
			ng = ccolor.g * 255;
			nb = ccolor.b * 255;

			newimageH->setPixel(nr, ng, nb, x, y);
		}
	}

	//VERTICAL
	for (int x = 1; x < image->getWidth() - 1; x++)
	{
		for (int y = 1; y < image->getHeight() - 1; y++)
		{
			int nr, ng, nb;
			float fnr, fng, fnb;
			nr = nb = ng = 0;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					nr += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 16) & 0xff) * verticalf[j][i];
					ng += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 8) & 0xff) * verticalf[j][i];
					nb += (image->getPixel(x + (i - 1), y + (j - 1)) & 0xff) * verticalf[j][i];
				}
			}
			fnr = nr / 255.0;
			fng = ng / 255.0;
			fnb = nb / 255.0;
			glm::vec3 ccolor(fnr, fng, fnb);
			ccolor = glm::clamp(glm::vec3(ccolor), 0.0f, 255.0f);

			nr = ccolor.r * 255;
			ng = ccolor.g * 255;
			nb = ccolor.b * 255;

			newimageV->setPixel(nr, ng, nb, x, y);
		}
	}
	int white = (255 << 16) | (255 << 8) | 255;
	//FUSE
	for (int x = 1; x < image->getWidth()-1; x++)
	{
		for (int y = 1; y < image->getHeight()-1; y++)
		{
			
			/*
			if (newimageH->getPixel(x, y) != 0)
			{
				newimageFull->setPixel(newimageH->getPixel(x, y), x, y);
			}
			else if (newimageV->getPixel(x, y) != 0)
			{
				newimageFull->setPixel(newimageV->getPixel(x, y), x, y);
			}
			else
			{
				newimageFull->setPixel(0, 0, 0, x, y);
			}*/	

			long ncolor = newimageH->getPixel(x, y) + newimageV->getPixel(x, y);
			if (ncolor > white)
			{
				ncolor = white;
			}
			else if (ncolor < 0)
			{
				ncolor = 0;
			}
			newimageFull->setPixel(ncolor, x, y);
		}
	}

	

	for (int x = 0; x < image->getWidth(); x++)
	{
		for (int y = 0; y < image->getHeight(); y++)
		{
			image->setPixel(newimageFull->getPixel(x, y), x, y);
		}
	}
}

void Filter::sobel(Image * image)
{
	float horizontalf[3][3] = { { 1,-2,1 },{ 0,0,0 },{ -1,2,-1 } };
	float verticalf[3][3] = { { -2,0,2 },{ 2,0,-2 },{ -1,0, 1 } };

	Image *newimageH = new Image(image->getWidth(), image->getHeight());
	Image *newimageV = new Image(image->getWidth(), image->getHeight());
	Image *newimageFull = new Image(image->getWidth(), image->getHeight());

	//HORIZONTAL
	for (int x = 1; x < image->getWidth() - 1; x++)
	{
		for (int y = 1; y < image->getHeight() - 1; y++)
		{
			int nr, ng, nb;
			float fnr, fng, fnb;
			nr = nb = ng = 0;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					nr += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 16) & 0xff) * horizontalf[j][i];
					ng += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 8) & 0xff) * horizontalf[j][i];
					nb += (image->getPixel(x + (i - 1), y + (j - 1)) & 0xff) * horizontalf[j][i];
				}
			}
			fnr = nr / 255.0;
			fng = ng / 255.0;
			fnb = nb / 255.0;
			glm::vec3 ccolor(fnr, fng, fnb);
			ccolor = glm::clamp(glm::vec3(ccolor), 0.0f, 255.0f);

			nr = ccolor.r * 255;
			ng = ccolor.g * 255;
			nb = ccolor.b * 255;

			newimageH->setPixel(nr, ng, nb, x, y);
		}
	}

	//VERTICAL
	for (int x = 1; x < image->getWidth() - 1; x++)
	{
		for (int y = 1; y < image->getHeight() - 1; y++)
		{
			int nr, ng, nb;
			float fnr, fng, fnb;
			nr = nb = ng = 0;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					nr += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 16) & 0xff) * verticalf[j][i];
					ng += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 8) & 0xff) * verticalf[j][i];
					nb += (image->getPixel(x + (i - 1), y + (j - 1)) & 0xff) * verticalf[j][i];
				}
			}
			fnr = nr / 255.0;
			fng = ng / 255.0;
			fnb = nb / 255.0;
			glm::vec3 ccolor(fnr, fng, fnb);
			ccolor = glm::clamp(glm::vec3(ccolor), 0.0f, 255.0f);

			nr = ccolor.r * 255;
			ng = ccolor.g * 255;
			nb = ccolor.b * 255;

			newimageV->setPixel(nr, ng, nb, x, y);
		}
	}

	//FUSE
	int white = (255 << 16) | (255 << 8) | 255;
	for (int x = 1; x < image->getWidth() - 1; x++)
	{
		for (int y = 1; y < image->getHeight() - 1; y++)
		{			
			
			long ncolor = newimageH->getPixel(x, y) + newimageV->getPixel(x, y);
			if (ncolor > white)
			{
				ncolor = white;
			}
			else if(ncolor < 0)
			{
				ncolor = 0;
			}
			newimageFull->setPixel(ncolor, x, y);
		}

	}



	for (int x = 0; x < image->getWidth(); x++)
	{
		for (int y = 0; y < image->getHeight(); y++)
		{
			image->setPixel(newimageFull->getPixel(x, y), x, y);
		}
	}
}