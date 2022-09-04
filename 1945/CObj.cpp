#include "pch.h"
#include "CObj.h"


int CObj::ObjectTotalCount;

CObj::CObj()
	: m_transform()
	, m_rect()
{
	ObjectTotalCount++;
}

CObj::CObj(Transform _transform)
	: m_transform(_transform)
	, m_rect()
{
	ObjectTotalCount++;
}

CObj::CObj(float _xPos, float _yPos, float _fScale)
	: m_transform(_xPos, _yPos, _fScale)
	, m_rect()
{
	ObjectTotalCount++;
}

CObj::~CObj()
{
	ObjectTotalCount--;
}
