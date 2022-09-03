#pragma once
#include "CSkill.h"
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
	float	m_midTime=0.f;
	float	m_v=0.f;

	float	m_fSpeed;
	float	m_fAngle;
};

