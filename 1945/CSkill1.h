#pragma once
#include "CSkill.h"
class CSkill1 :
	public CSkill
{
public:
	CSkill1();
	virtual ~CSkill1() {}

public:
	virtual void Update(float _fDeltaTime) override;
	virtual void Render(HDC _hdc) override;

private:
	void SetRect(int i)
	{
		m_Boom_ltrb[i].left = static_cast<LONG>(m_Boom[i].X_COM - m_Scale[i] * 0.5f);
		m_Boom_ltrb[i].top = static_cast<LONG>(m_Boom[i].Y_COM - m_Scale[i] * 0.5f);
		m_Boom_ltrb[i].right = static_cast<LONG>(m_Boom[i].X_COM + m_Scale[i] * 0.5f);
		m_Boom_ltrb[i].bottom = static_cast<LONG>(m_Boom[i].Y_COM + m_Scale[i] * 0.5f);
	};

private:
	POS		m_B2_left[3];
	POS		m_B2_right[3];

	POS		m_Boom[8];
	RECT	m_Boom_ltrb[8];
	float	m_Scale[8];
};

