#include "pch.h"
#include "CSkill1.h"


const POS B2_o[3] =
{
	//WIDTH 500
	//HIGHT 700

	{0,-30},
	{-180,50},
	{180,50}
};

const POS BOOM[8] =
{
	{WIDTH / 2 - 65, HIGHT - 550},{WIDTH / 2 + 50, HIGHT - 520},
	{WIDTH / 2 - 50, HIGHT - 400},{WIDTH / 2 + 60, HIGHT - 300},
	{WIDTH / 2 - 40, HIGHT - 250},{WIDTH / 2 + 50, HIGHT - 200},
	{WIDTH / 2 - 70, HIGHT - 150},{WIDTH / 2 + 40, HIGHT - 100}
};

CSkill1::CSkill1()
{
	for (int i = 0; i < 3; ++i)
	{
		m_B2_left[i].X_COM = B2_o[i].X_COM + WIDTH / 2 - 50;
		m_B2_left[i].Y_COM = B2_o[i].Y_COM + HIGHT + 30;

		m_B2_right[i].X_COM = B2_o[i].X_COM + WIDTH / 2 + 50;
		m_B2_right[i].Y_COM = B2_o[i].Y_COM + HIGHT + 100;
	}

	memcpy(m_Boom, BOOM, sizeof(m_Boom));

	memset(m_Boom_ltrb, 0, sizeof(m_Boom_ltrb));
	memset(m_Scale, 0, sizeof(m_Scale));

}

void CSkill1::Update(float _fDeltaTime)
{
	if (m_isDead)
		return;

	// ½ºÅ³ ÃÑ ½Ã°£
	if (m_localTime > 4.5f)
		m_isDead = true;

	float dt = _fDeltaTime;
	m_localTime += dt;
	float a = 0.25f;

	for (int i = 0; i < 3; ++i)
	{
		m_B2_left[i].Y_COM -= a * m_localTime * m_localTime;
		m_B2_right[i].Y_COM -= a * m_localTime * m_localTime;
	}

	for (int i = 0; i < 8; ++i)
		m_Boom[i].Y_COM += 30.f * dt;

	if (m_localTime < 1.75f)
		return;
	m_Scale[6] += 400.f * dt;
	SetRect(6);
	if (m_localTime < 2.f)
		return;
	m_Scale[7] += 500.f * dt;
	SetRect(7);
	if (m_localTime < 2.25f)
		return;
	m_Scale[4] += 700.f * dt;
	SetRect(4);
	if (m_localTime < 2.5f)
		return;
	m_Scale[5] += 600.f * dt;
	SetRect(5);
	if (m_localTime < 2.75f)
		return;
	m_Scale[3] += 500.f * dt;
	SetRect(3);
	if (m_localTime < 3.f)
		return;
	m_Scale[2] += 500.f * dt;
	SetRect(2);
	if (m_localTime < 3.25f)
		return;
	m_Scale[0] += 800.f * dt;
	SetRect(0);
	if (m_localTime < 3.5f)
		return;
	m_Scale[1] += 1000.f * dt;
	SetRect(1);
}

void CSkill1::Render(HDC _hdc)
{
	HDC hdc = _hdc;

	for (int i = 7; i >= 0; --i)
		Ellipse(_hdc, m_Boom_ltrb[i].left, m_Boom_ltrb[i].top, m_Boom_ltrb[i].right, m_Boom_ltrb[i].bottom);


	POINT B2_left[3];
	for (int i = 0; i < 3; ++i)
	{
		B2_left[i].x = m_B2_left[i].X_COM;
		B2_left[i].y = m_B2_left[i].Y_COM;
	}
	Polygon(hdc, B2_left, 3);


	POINT B2_right[3];
	for (int i = 0; i < 3; ++i)
	{
		B2_right[i].x = m_B2_right[i].X_COM;
		B2_right[i].y = m_B2_right[i].Y_COM;
	}
	Polygon(hdc, B2_right, 3);



}


