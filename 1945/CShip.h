#pragma once
#include "CObj.h"

class CShip : public CObj
{
public:
	CShip();
	CShip(Transform _transform);
	CShip(float _xPos, float _yPos, float _fScale);
	virtual ~CShip();
public:

public:
	void Initalize() override;
	void Update(float _fDeltaTime) override;
	void Render(HDC _hdc)		   override;
public:
	void  SetCurSpeed(float _fSpeed) { m_fCurSpeed = _fSpeed; }
	float GetCurSpeed() { return m_fCurSpeed; }

	void  SetMaxSpeed(float _fSpeed) { m_fMaxSpeed = _fSpeed; }
	float GetMaxSpeed() { return m_fMaxSpeed; }

	void  SetBullet(list<CObj*>* _pBulletList);
public:
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void Accelerate();
	void Decelderate();

	void CreateBullet();
	bool bIsAttackCheck() { return m_bAttackAble; };


public: // PLTOYA
	void Skill();

private:
	float m_fLocalTime;

	float m_fCurSpeed;
	float m_fMaxSpeed;

	float m_fAttackDelay;
	bool  m_bAttackAble;

	ULONGLONG attackTimer;
	list<CObj*>* m_pBulletList;
	//0���� �ʱ�ȭ �� 0���� �������ִ� ���� ���������϶� ��Ÿ������ 
	//����Ÿ�ӿ� ������Ű�� ����Ÿ���� ������ �� ����Ÿ���� ���ؾ���.
};

