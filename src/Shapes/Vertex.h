/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	Vertex.h
//
//	Description:
//	 Vertex storing a position, normal, texture coordinate, and a colour.
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "../Datatypes/Vector3.h"
#include "../Datatypes/Vector2.h"
#include"../Datatypes/Colour.h"


struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 textureCoordinate;
	Colour colour;

	Vertex() {}
	~Vertex() {}

	Vertex(Vector3 pos, Vector3 normal, Vector2 texCoord, Colour colour) 
		: position(pos), normal(normal), textureCoordinate(texCoord), colour(colour)
	{

	}
};