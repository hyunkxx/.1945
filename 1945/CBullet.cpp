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
	

	if (전투기 == m_iEnemyType)
	{
		Ellipse(_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
	}
	else if (고정포탑 == m_iEnemyType)
	{
		//HBRUSH inBrush;
		//inBrush = (HBRUSH)CreateSolidBrush(RGB(204, 255, 255));
		Ellipse(_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
	}
	else if (가미카제 == m_iEnemyType)
	{
		Ellipse(_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
	}
	else
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

	
}

void CBullet::moveUp()
{
	m_fLocalTime += CCore::g_DeltaTime;
	//m_transform.fY -= m_fSpeed * CCore::g_DeltaTime * 1.1f * m_fLocalTime;


	m_transform.fX += m_fSpeed * CCore::g_DeltaTime * 1.1f * m_fLocalTime * cosf(m_angle * PI / 180);
	m_transform.fY -= m_fSpeed * CCore::g_DeltaTime * 1.1f * m_fLocalTime * sinf(m_angle * PI / 180);


	// 진건 추가 - 플레이어 몬스터 총알 같이 쏘는거
	// 여기 좀 수정해야될듯
	//m_transform.fX += m_fSpeed * CCore::g_DeltaTime * cosf(m_angle * PI / 180);
	//m_transform.fY -= m_fSpeed * CCore::g_DeltaTime * sinf(m_angle * PI / 180);
}

void CBullet::dieCheck()
{
	if (m_transform.fY < -50)
		m_IsDead = true;
	if (m_transform.fY > HIGHT+50)
		m_IsDead = true;
	if (m_transform.fX < -50)
		m_IsDead = true;
	if (m_transform.fX > WIDTH+50)
		m_IsDead = true;
}
