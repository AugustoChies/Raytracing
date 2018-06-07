#pragma once
#include "Image.h"
#include <fstream>
#include <string>

using namespace std;

static class Output
{
public:
	Output();
	~Output();
	static void saveImage(Image*,const char *);
};

