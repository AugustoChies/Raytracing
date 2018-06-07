#pragma once
#include "Raycast.h"
#include "Raytrace.h"
#include <fstream>

using namespace std;


static class Input
{
public:
	Input();
	~Input();
	static Image* loadImage(const char*);
	static Render* loadScene(const char*);
	
};

