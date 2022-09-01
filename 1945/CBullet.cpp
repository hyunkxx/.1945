#include "pch.h"
#include "CBullet.h"

CBullet::CBullet(float _xPos, float _yPos)
	: CObj(_xPos, _yPos, 10.f)
{
	Initalize();
}

CBullet::~CBullet()
{
}

void CBullet::Initalize()
{
	m_fSpeed = 1000.f;
	m_fLocalTime = 0.3f;
}

void CBullet::Update(float _fDeltaTime)
{
	m_fLocalTime += _fDeltaTime;
	m_transform.fY -= m_fSpeed * _fDeltaTime * 0.7f * m_fLocalTime;

	SetRect();
}

void CBullet::Render(HDC _hdc)
{
	HBRUSH outBrush, inBrush, myBrush;
	outBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 255));
	inBrush = (HBRUSH)CreateSolidBrush(RGB(204, 255, 255));
	myBrush = (HBRUSH)SelectObject(_hdc, outBrush);
	Ellipse(_hdc, m_rect.left + 1, m_rect.top, m_rect.right - 1, m_rect.bottom + 12);
	outBrush = (HBRUSH)SelectObject(_hdc, inBrush);
	Ellipse(_hdc, m_rect.left + 1, m_rect.top - 1, m_rect.right - 1, m_rect.bottom);

	SelectObject(_hdc, myBrush);

	DeleteObject(inBrush);
	DeleteObject(outBrush);
}
