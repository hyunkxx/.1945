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


	// ���⼭ ���� ���� ����
public:
	void	InitEnemy(float _angle, int _type)
	{
		m_angle = _angle;
		m_iEnemyType = _type;
		SetSpeed(500.f);
	}

private:
	// ���� �Ѿ� �߻� ������ �з����� �ɹ� ����
	float		m_angle = 90.f; // 90.f�� ���� �� �Ʒ��� ����� 270.f
	int         m_iEnemyType;


};

