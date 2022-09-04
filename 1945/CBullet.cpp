#include "pch.h"
#include "CCore.h"
#include "CBullet.h"

CBullet::CBullet(float _xPos, float _yPos)
	: CObj(_xPos, _yPos, 10.f)
	, m_bDie (false)
	, m_fSpeed(1300.f)
    , m_fLocalTime(0.3f)
{
}

CBullet::~CBullet()
{
}

void CBullet::Initalize()
{
	projectile = 1.0f;
	m_fSpeed = 1000.f;
	m_fLocalTime = 0.3f;
}

void CBullet::Update(float _fDeltaTime)
{
	moveUp();
	dieCheck();

	SetRect();
}

void CBullet::Render(HDC _hdc)
{
	HBRUSH outBrush, inBrush, myBrush;
	HBRUSH smokeBrush1, smokeBrush2;
	smokeBrush1 = (HBRUSH)CreateSolidBrush(RGB(255, 248, 220));
	smokeBrush2 = (HBRUSH)CreateSolidBrush(RGB(255, 228, 255));

	outBrush = (HBRUSH)CreateSolidBrush(RGB(255, 000, 000));
	inBrush = (HBRUSH)CreateSolidBrush(RGB(189, 183, 107));


	myBrush = (HBRUSH)SelectObject(_hdc, smokeBrush2);
	Ellipse(_hdc, m_rect.left+1 , m_rect.top + m_rect.bottom - 40, m_rect.right-1 , m_rect.bottom);
	smokeBrush2 = (HBRUSH)SelectObject(_hdc, smokeBrush1);
	Ellipse(_hdc, m_rect.left + 3, m_rect.top + m_rect.bottom - 40, m_rect.right - 3, m_rect.bottom);
	smokeBrush1 = (HBRUSH)SelectObject(_hdc, outBrush);
	Ellipse(_hdc, m_rect.left + 2, m_rect.top, m_rect.right - 2, m_rect.bottom + 12);
	outBrush = (HBRUSH)SelectObject(_hdc, inBrush);
	Ellipse(_hdc, m_rect.left + 2, m_rect.top - 1, m_rect.right - 2, m_rect.bottom);
	SelectObject(_hdc, myBrush);

	DeleteObject(smokeBrush1);
	DeleteObject(smokeBrush2);
	DeleteObject(inBrush);
	DeleteObject(outBrush);
}

void CBullet::moveUp()
{
	m_fLocalTime += CCore::g_DeltaTime; // 투사체 속도
	m_transform.fY -= m_fSpeed * CCore::g_DeltaTime * 1.1f * m_fLocalTime;
}

void CBullet::dieCheck()
{
	if (m_transform.fY < -50)
	{
		m_bDie = true;
	}
}
