#include "Output.h"



Output::Output()
{
}


Output::~Output()
{
}

void Output::saveImage(Image* im,const char * name)
{
	ofstream arq(name);
	
	arq << "p7" << endl;
	
	
	arq << im->getWidth() << " ";
	arq << im->getHeight() << endl;
	
	arq << 255 << endl;

	for (int y = im->getHeight() - 1; y >= 0; y--)
	{
		for (int x = 0; x < im->getWidth(); x++)
		{
			int px = im->getPixel(x, y);
			int r = (px >> 16) & 0xff;
			int g = (px >> 8) & 0xff;
			int b = px & 0xff;

			arq << 255 << " " << r << " " << g << " " << b << " ";
			
		}
	}
	
	arq.close();
}