#pragma once

struct Transform
{
	float fX;
	float fY;
	float fScale;

	Transform()
		:fX(0.f), fY(0.f), fScale(50.f) {}

	Transform(float _xPos, float _yPos, float _fScale)
		:fX(_xPos), fY(_yPos), fScale(_fScale) {}
};

class CObj
{
public:
	CObj();
	CObj(Transform _transform);
	CObj(float _xPos, float _yPos, float _fScale);
	virtual ~CObj();
public:
	static int ObjectTotalCount;
public:
	virtual		void Initalize()			   PURE;
	virtual		void Update(float _fDeltaTime) PURE;
	virtual		void Render(HDC _hdc)		   PURE;
public:
	RECT GetRect() { return m_rect; }
	void SetRect()
	{
		m_rect.left = static_cast<LONG>(m_transform.fX - m_transform.fScale * 0.5f);
		m_rect.top = static_cast<LONG>(m_transform.fY - m_transform.fScale * 0.5f);
		m_rect.right = static_cast<LONG>(m_transform.fX + m_transform.fScale * 0.5f);
		m_rect.bottom = static_cast<LONG>(m_transform.fY + m_transform.fScale * 0.5f);
	};

	float GetX() { return m_transform.fX; }
	float GetY() { return m_transform.fY; }
	float GetScale() { return m_transform.fScale; }

	void SetX(float _fX) { m_transform.fX = _fX; }
	void SetY(float _fY) { m_transform.fY = _fY; }
	void SetScale(float _fScale) { m_transform.fY = _fScale; }

	const Transform& GetTransform() { return m_transform; }
	void	  SetTrnasform(Transform _transform) { m_transform = _transform; }
	void	  SetTrnasform(float _xPos, float _yPos, float _fScale)
	{
		m_transform.fX = _xPos, m_transform.fY = _yPos, m_transform.fScale = _fScale;
	}
protected:
	Transform	m_transform;
	RECT		m_rect;
};

