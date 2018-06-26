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
	float upf[3][3] = { {-1,-1,-1},
						{ 0,0,0 },
						{1,1,1 } };
	float downf[3][3] = { { 1,1,1 },
						  { 0,0,0 },
						  { -1,-1,-1 } };

	float rightf[3][3] = { { -1,0,1 },	
						   { -1,0,1 },
	                       { -1,0,1 } };
	float leftf[3][3] = { { 1,0,-1 },
						  { 1,0,-1 },
	                      { 1,0,-1 } };

	Image *newimageFull = new Image(image->getWidth(), image->getHeight());
	for (int x = 1; x < image->getWidth()-1; x++)
	{
		for (int y = 1; y < image->getHeight()-1; y++)
		{
			int nr, ng, nb;
			int nr2, ng2, nb2;
			int nr3, ng3, nb3;
			int nr4, ng4, nb4;
			nr = nb = ng = 0;
			nr2 = nb2 = ng2 = 0;
			nr3 = nb3 = ng3 = 0;
			nr4 = nb4 = ng4 = 0;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					nr += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 16) & 0xff) * upf[j][i];
					ng += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 8) & 0xff) * upf[j][i];
					nb += (image->getPixel(x + (i - 1), y + (j - 1)) & 0xff) * upf[j][i];

					nr2 += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 16) & 0xff) * leftf[j][i];
					ng2 += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 8) & 0xff) * leftf[j][i];
					nb2 += (image->getPixel(x + (i - 1), y + (j - 1)) & 0xff) * leftf[j][i];

					nr3 += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 16) & 0xff) * downf[j][i];
					ng3 += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 8) & 0xff) * downf[j][i];
					nb3 += (image->getPixel(x + (i - 1), y + (j - 1)) & 0xff) * downf[j][i];

					nr4 += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 16) & 0xff) * rightf[j][i];
					ng4 += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 8) & 0xff) * rightf[j][i];
					nb4 += (image->getPixel(x + (i - 1), y + (j - 1)) & 0xff) * rightf[j][i];
				}
			}
			
			nr = glm::clamp(nr, 0, 255);
			ng = glm::clamp(ng, 0, 255);
			nb = glm::clamp(nb, 0, 255);

			nr2 = glm::clamp(nr2, 0, 255);
			ng2 = glm::clamp(ng2, 0, 255);
			nb2 = glm::clamp(nb2, 0, 255);

			nr3 = glm::clamp(nr3, 0, 255);
			ng3 = glm::clamp(ng3, 0, 255);
			nb3 = glm::clamp(nb3, 0, 255);

			nr4 = glm::clamp(nr4, 0, 255);
			ng4 = glm::clamp(ng4, 0, 255);
			nb4 = glm::clamp(nb4, 0, 255);
			
			int finalcolorul = (glm::clamp((int)sqrt(pow(nr, 2) + pow(nr2, 2)),0,255) << 16) |
				(glm::clamp((int)sqrt(pow(ng, 2) + pow(ng2, 2)), 0, 255) << 8) |
				glm::clamp((int)sqrt(pow(nb, 2) + pow(nb2, 2)), 0, 255);

			int finalcolorbr = (glm::clamp((int)sqrt(pow(nr3, 2) + pow(nr4, 2)), 0, 255) << 16) |
				(glm::clamp((int)sqrt(pow(ng3, 2) + pow(ng4, 2)), 0, 255) << 8) |
				glm::clamp((int)sqrt(pow(nb3, 2) + pow(nb4, 2)), 0, 255);
			
		    
			newimageFull->setPixel(finalcolorul+finalcolorbr, x, y);
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
	float horizontalf[3][3] = { { 1,2,1 },
								{ 0,0,0 },
								{ -1,-2,-1 } };
	float verticalf[3][3] = { { 1,0,-1 },
							  { 2,0,-2 },
							 { 1,0, -1 } };

	Image *newimageFull = new Image(image->getWidth(), image->getHeight());
	for (int x = 1; x < image->getWidth() - 1; x++)
	{
		for (int y = 1; y < image->getHeight() - 1; y++)
		{
			int nr, ng, nb;
			int nr2, ng2, nb2;
			nr = nb = ng = 0;
			nr2 = nb2 = ng2 = 0;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					nr += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 16) & 0xff) * horizontalf[j][i];
					ng += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 8) & 0xff) * horizontalf[j][i];
					nb += (image->getPixel(x + (i - 1), y + (j - 1)) & 0xff) * horizontalf[j][i];

					nr2 += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 16) & 0xff) * verticalf[j][i];
					ng2 += ((image->getPixel(x + (i - 1), y + (j - 1)) >> 8) & 0xff) * verticalf[j][i];
					nb2 += (image->getPixel(x + (i - 1), y + (j - 1)) & 0xff) * verticalf[j][i];
				}
			}

			nr = glm::clamp(nr, 0, 255);
			ng = glm::clamp(ng, 0, 255);
			nb = glm::clamp(nb, 0, 255);

			nr2 = glm::clamp(nr2, 0, 255);
			ng2 = glm::clamp(ng2, 0, 255);
			nb2 = glm::clamp(nb2, 0, 255);

			int finalcolor = (glm::clamp((int)sqrt(pow(nr, 2) + pow(nr2, 2)), 0, 255) << 16) |
				(glm::clamp((int)sqrt(pow(ng, 2) + pow(ng2, 2)), 0, 255) << 8) |
				glm::clamp((int)sqrt(pow(nb, 2) + pow(nb2, 2)), 0, 255);


			newimageFull->setPixel(finalcolor, x, y);
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