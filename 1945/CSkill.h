#pragma once



class CSkill
{
public:
	CSkill()
		: m_isDead(false), m_localTime(0.f)
	{}
	virtual ~CSkill() {}

public:
	bool IsDead() { return m_isDead; }
	virtual void Update(float _fDeltaTime) = 0;
	virtual void Render(HDC _hdc) = 0;

protected:
	void Rotate(POS& _pos, float _rad);
	void Scale(POS& _pos, float _coef);
	void move(POS& _pos, float _x, float _y);

private:

protected:
	bool			m_isDead;
	float			m_localTime;	// 지역시간

};