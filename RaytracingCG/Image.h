#pragma once



class Image
{ 
public:
	Image();
	Image(float w, float h)
	{
		width = w;
		height = h;
		pixels = new int[w*h];
	}
	void setPixel(int rgb, int x, int y) {
		pixels[x + y*width] = rgb;
	}
	void setPixel(int r, int g, int b, int x, int y)
	{
		int rgb = (r << 16) | (g << 8) | b;
		pixels[x + y*width] = rgb;
	}
	int getPixel(int x, int y) {
		return pixels[x + y*width];
	}
	int getWidth() { return width; }
	int getHeight() { return height; }
	int* getPixels() { return pixels; }
	

private:
	int *pixels; // alternativamente char *pixels – 1 byte por canal
	
	int width, height;
	
	
};

