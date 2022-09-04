#pragma once
#include "CSkill.h"


struct VBULLET
{
	POS		pos;
	RECT	rect;
	float	angle;
	float	localTime;
	float	speed;
};

class CSkill2 :
	public CSkill
{
public:
	CSkill2();
	virtual ~CSkill2() {}

public:
	virtual void Update(float _fDeltaTime) override;
	virtual void Render(HDC _hdc) override;

private:
	POS		m_AIR[12];
	POS		m_Pos;
	float	m_midTime = 0.f;
	float	m_v = 0.f;


	// Æ÷Å¾
private:
	POS		m_turretPos;
	float	m_turretRadi;
	RECT	m_turretRECT;

	float	m_disBarrel;
	POS		m_barrelPos[4];
	float	m_barrelAngle[4];

	float	m_fireTime = 0.f;
	float	m_FT_Boundery = 0.1f;

private:
	list<VBULLET>	m_bullets[4];
	float			m_bulletRadi = 5.f;
	RECT			m_bulletRECT;
};

