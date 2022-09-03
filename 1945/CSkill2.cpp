#include "pch.h"
#include "CSkill2.h"

const POS AIR_points[12] =
{
	{ 10,-60 },
	{ 20,-10 },
	{ 60,20 },
	{ 20,20 },
	{ 15,50 },
	{ 30,60 },
	{ -30,60 },
	{ -15,50 },
	{ -20,20 },
	{ -60,20 },
	{ -20,-10 },
	{ -10,-60 },
};


CSkill2::CSkill2()
{
	for (int i = 0; i < 12; ++i)
	{
		m_AIR[i].X_COM = AIR_points[i].X_COM*5;
		m_AIR[i].Y_COM = AIR_points[i].Y_COM*5;
	}

	m_Pos = POS{WIDTH/2,1000};
}

void CSkill2::Update(float _fDeltaTime)
{
	if (m_isDead)
		return;

	// ½ºÅ³ ÃÑ ½Ã°£
	if (m_localTime > 5.5f)
		m_isDead = true;

	float dt = _fDeltaTime;
	m_localTime += dt;
	float a = 1000.f;
	float v0 = -1000.f;

	if (m_localTime > 3.5f)
	{
		m_midTime += dt;
		m_Pos.Y_COM -= 100.f * dt;
		m_Pos.Y_COM += 0.5f* -10.f * m_midTime * m_midTime;
	}
	else if (m_Pos.Y_COM < 510.f )
	{
		m_Pos.Y_COM -= 100.f*dt;
	}
	else
		m_Pos.Y_COM = 1000 + v0 * m_localTime + 0.5f * a * m_localTime * m_localTime;

	for (int i = 0; i < 12; ++i)
	{
		m_AIR[i].X_COM = 5*AIR_points[i].X_COM + m_Pos.X_COM;
		m_AIR[i].Y_COM = 5*AIR_points[i].Y_COM + m_Pos.Y_COM;
	}

}

void CSkill2::Render(HDC _hdc)
{
	HDC hdc = _hdc;

	POINT air[12];
	for (int i = 0; i < 12; ++i)
	{
		air[i].x = m_AIR[i].X_COM;
		air[i].y = m_AIR[i].Y_COM;
	}
	Polygon(hdc, air, 12);
}
