/////////////////////////////////////////////////////////////////////////////////////////////
// 
//	Colour.h
//
//	Description:
//	 Essentially a lightweight version of Vector3 with RGB instead of XYZ.
//	 Complete with some useful colour presets!
// 
//  
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once


class Colour
{
public:
	// Store floats as enum[3]
	float e[3];

	// Constructors
	const Colour() : e{ 0,0,0 } {}
	const Colour(float e0, float e1, float e2) : e{ e0, e1, e2 } {}

	// Get rgb floats
	float r() const { return e[0]; }
	float g() const { return e[1]; }
	float b() const { return e[2]; }

	// Presets
	static Colour White()	{ return Colour(1.0f, 1.0f, 1.0f); }
	static Colour Black()	{ return Colour(0.0f, 0.0f, 0.0f); }
	static Colour Red()		{ return Colour(1.0f, 0.0f, 0.0f); }
	static Colour Green()	{ return Colour(0.0f, 1.0f, 0.0f); }
	static Colour Blue()	{ return Colour(0.0f, 0.0f, 1.0f); }
	static Colour Cyan()	{ return Colour(0.0f, 1.0f, 1.0f); }
	static Colour Magenta() { return Colour(1.0f, 0.0f, 1.0f); }
	static Colour Yellow()	{ return Colour(1.0f, 1.0f, 0.0f); }
	// BubblesRT Logo Colours
	static Colour BubbleBlue()		{ return Colour(0.03f, 0.73f, 0.95f); }
	static Colour BubbleHotpink()	{ return Colour(0.92f, 0.00f, 0.58f); }
	static Colour BubblePurple()	{ return Colour(0.81f, 0.31f, 0.92f); }

};

// Type aliases
using Vector3colour = Colour;
using colour = Colour;
using color = Colour;