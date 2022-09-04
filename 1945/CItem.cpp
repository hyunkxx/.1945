#include "pch.h"
#include "CItem.h"

CItem::CItem(string _szName)
	:CObj()
	,m_szName(_szName)
{
}

CItem::CItem(string _szName, Transform _transform)
	: CObj(_transform)
	, m_szName(_szName)
{
}

CItem::CItem(string _szName, float _xPos, float _yPos, float _fScale)
	: CObj(_xPos,_yPos,_fScale)
	, m_szName(_szName)
{
}

void CItem::Initalize()
{
}

void CItem::Update(float _fDeltaTime)
{
}

void CItem::Render(HDC _hdc)
{
}
