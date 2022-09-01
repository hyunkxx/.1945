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
	float SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
private:
	float m_fSpeed;
	float m_fLocalTime;
};

