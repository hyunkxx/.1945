#include "pch.h"
#include "CSkill.h"


void CSkill::Rotate(POS& _pos, float _rad)
{
	POS pos = _pos;

	_pos.X_COM = cos(_rad) * pos.X_COM + sin(_rad) * pos.Y_COM;
	_pos.Y_COM = -sin(_rad) * pos.X_COM + cos(_rad) * pos.Y_COM;
}

void CSkill::Scale(POS& _pos, float _coef)
{
	_pos.X_COM *= _coef;
	_pos.Y_COM *= _coef;
}

void CSkill::move(POS& _pos, float _x, float _y)
{
	_pos.X_COM += _x;
	_pos.Y_COM += _y;
}
