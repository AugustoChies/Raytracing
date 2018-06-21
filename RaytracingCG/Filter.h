#pragma once
#include "Image.h"
#include <iostream>
#include "glm\glm.hpp"

static class Filter
{
public:
	Filter();
	~Filter();
	static void blur(Image* image, int blurammount);
	static void greyScale(Image* image);
	static void bioGreyScale(Image* image);
	static void RScale(Image* image);
	static void GScale(Image* image);
	static void BScale(Image* image);
	static void prewitt(Image * image);
	static void sobel(Image * image);
};

