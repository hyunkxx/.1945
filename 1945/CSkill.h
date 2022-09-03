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
	void Update_Rect_S(RECT& _rect, POS& _pos, float _radius)
	{
		_rect.left = long(_pos.X_COM - _radius);
		_rect.top = long(_pos.Y_COM - _radius);
		_rect.right = long(_pos.X_COM + _radius);
		_rect.bottom = long(_pos.Y_COM + _radius);
	}

private:

protected:
	bool			m_isDead;
	float			m_localTime;	// 지역시간

};

