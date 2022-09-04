#pragma once
enum
{
	트럼보점개수 = 51,
};

class CLogo
{
public:
	CLogo();

public:
	void Update(float _fDeltaTime);
	void Rander(HDC _hdc);

private:

	void Scale(float _coef);
	void move(float _x, float _y);

public:
	bool IsDead() { return m_IsDead; }
	void SetDead() { m_IsDead = true; }
	bool m_IsDead = false;
	float m_localTime = 0.f;
	float m_midTime = 0.f;

private:
	POS m_bodyPoints[51];
	POS m_eyePoints[2];
};

