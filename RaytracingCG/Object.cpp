#include "Object.h"



Object::Object()
{
}


Object::~Object()
{
}

Material* Object::getMaterial()
{
	return mat;
}

int Object::getId()
{
	return id;
}