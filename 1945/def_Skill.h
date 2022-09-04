#pragma once

struct POS
{
	POS operator-(const POS& _pos)
	{
		return POS{ X_COM - _pos.X_COM,Y_COM - _pos.Y_COM };
	}

	POS operator+(const POS& _pos)
	{
		return POS{ X_COM + _pos.X_COM,Y_COM + _pos.Y_COM };
	}

	float X_COM;
	float Y_COM;
};

const float unitRadian = float(3.141592 / 180.f);

struct COLLISION
{
	POS		pos;
	float	radius;
};
