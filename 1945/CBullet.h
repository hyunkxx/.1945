#pragma once

#include "CObj.h"

class CBullet : public CObj
{
public:
	CBullet(float _xPos, float _yPos);
	~CBullet();
public:
	void Initalize() override;
	void Update(float _fDeltaTime)	override;
	void Render(HDC _hdc)			override;
public:
	float GetSpeed() { return m_fSpeed; }
	void  SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	bool  IsDie() { return m_bDie; }
private:
	void moveUp();
	void dieCheck();
private:
	float m_fSpeed;
	float m_fLocalTime;
	bool  m_bDie;


	// 여기서 부터 진건 수정
public:
	void	InitEnemy(float _angle, int _type)
	{
		m_angle = _angle;
		m_iEnemyType = _type;
		SetSpeed(500.f);
	}

private:
	// 몬스터 총알 발사 패턴을 분류해줄 맴버 변수
	float		m_angle = 90.f; // 90.f면 위로 쏨 아래로 쏘려면 270.f
	int         m_iEnemyType;


};

