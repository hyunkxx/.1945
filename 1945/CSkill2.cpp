#include "pch.h"
#include "CSkill2.h"
#include "CCollisionMgr.h"

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
		m_AIR[i].X_COM = AIR_points[i].X_COM * 5;
		m_AIR[i].Y_COM = AIR_points[i].Y_COM * 5;
	}

	m_Pos = POS{ WIDTH / 2,1000 };


	// 포탑
	m_turretPos = m_Pos;
	m_turretRadi = 50.f;
	Update_Rect_S(m_turretRECT, m_turretPos, m_turretRadi);

	m_disBarrel = 50.f;

	m_barrelAngle[0] = 0.f;
	m_barrelAngle[1] = 3.141592f * 0.5f;
	m_barrelAngle[2] = 3.141592f;
	m_barrelAngle[3] = 3.141592f * 1.5f;

	POS pos{ WIDTH / 2,1200 };
	float radius = WIDTH / 1.5f;
	m_Collision = { pos,radius };
}

void CSkill2::Update(float _fDeltaTime)
{
	if (m_isDead)
		return;

	//DeleteEnemy();
	
	

	// 스킬 총 시간
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
		m_Pos.Y_COM += 0.5f * -10.f * m_midTime * m_midTime;
	}
	else if (m_Pos.Y_COM < 510.f)
	{
		m_Pos.Y_COM -= 100.f * dt;
	}
	else
		m_Pos.Y_COM = 1000 + v0 * m_localTime + 0.5f * a * m_localTime * m_localTime;

	for (int i = 0; i < 12; ++i)
	{
		m_AIR[i].X_COM = 5 * AIR_points[i].X_COM + m_Pos.X_COM;
		m_AIR[i].Y_COM = 5 * AIR_points[i].Y_COM + m_Pos.Y_COM;
	}


	

	m_turretPos = m_Pos;
	for (int i = 0; i < 4; ++i)
		m_barrelPos[i] = m_Pos;
	Update_Rect_S(m_turretRECT, m_turretPos, m_turretRadi);

	for (int i = 0; i < 4; ++i)
	{
		m_barrelAngle[i] += 3.f * dt * m_localTime;
		m_barrelPos[i].X_COM += m_disBarrel * cosf(m_barrelAngle[i]);
		m_barrelPos[i].Y_COM -= m_disBarrel * sinf(m_barrelAngle[i]);
	}


	for (int i = 0; i < 4; ++i)
		for (auto& bullet : m_bullets[i])
		{
			bullet.localTime += dt;

			bullet.pos.Y_COM -= 300.f * dt;

			bullet.pos.X_COM += 2500.f * dt * bullet.localTime * cosf(bullet.angle);
			bullet.pos.Y_COM -= 2500.f * dt * bullet.localTime * sinf(bullet.angle);
			Update_Rect_S(bullet.rect, bullet.pos, m_bulletRadi);
		}


	m_fireTime += dt;

	if (m_fireTime > m_FT_Boundery)
	{
		for (int i = 0; i < 4; ++i)
		{
			Update_Rect_S(m_bulletRECT, m_barrelPos[i], m_bulletRadi);
			m_bullets[i].push_back({ m_barrelPos[i],m_bulletRECT, m_barrelAngle[i],0.f });
		}

		m_fireTime = 0;

		if (m_localTime > 1.6f)
			m_FT_Boundery = 0.07f;
		if (m_localTime > 1.9f)
			m_FT_Boundery = 0.04f;
		if (m_localTime > 2.3f)
			m_FT_Boundery = 0.02f;

		if (m_localTime > 2.5f)
			m_FT_Boundery = 0.01f;
	}

	m_Collision.pos.Y_COM = m_Pos.Y_COM+100.f;
	//m_Collision.radius += m_localTime*10.f;
	CCollisionMgr::Collision_Cheak(m_Collision);
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

	Ellipse(hdc, m_turretRECT.left, m_turretRECT.top, m_turretRECT.right, m_turretRECT.bottom);

	for (int i = 0; i < 4; ++i)
	{
		MoveToEx(hdc, (int)m_turretPos.X_COM, (int)m_turretPos.Y_COM, nullptr);
		LineTo(hdc, m_barrelPos[i].X_COM, m_barrelPos[i].Y_COM);
	}

	for (int i = 0; i < 4; ++i)
		for (auto& bullet : m_bullets[i])
			Ellipse(hdc, bullet.rect.left, bullet.rect.top, bullet.rect.right, bullet.rect.bottom);
}
