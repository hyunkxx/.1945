#include "pch.h"
#include "CLogo.h"

POS THRUMBO_points[51] =
{
	{ 90, -225 },
	{ 100, -230 },
	{ 150, -210 },
	{ 170, -190 },
	{ 165, -180 },
	{ 170, -170 },
	{ 180, -160 },
	{ 200, -155 },
	{ 170, -150 },
	{ 160, -155 },
	{ 140, -170 },
	{ 130, -160 },
	{ 150, -140 },
	{ 155, -125 },
	{ 150, -115 },
	{ 140, -125 },
	{ 120, -130 },
	{ 100, -120 },
	{ 100, -110 },
	{ 145, -85 },
	{ 165, -30 },
	{ 160, 10 },
	{ 170, 50 },
	{ 120, 40 },
	{ 50, 20 },
	{ 0, 10 },

	{ -100, 20 },
	{ -120, 50 },
	{ -150, 20 },
	{ -170, -30 },
	{ -160, -60 },
	{ -170, -30 },
	{ -159, 0 },
	{ -170, 20 },
	{ -200, 30 },
	{ -190, 0 },
	{ -205, -20 },
	{ -190, -60 },
	{ -170, -80 },
	{ -140, -100 },
	{ -80, -110 },

	{ 0, -105 },
	{ 30, -120 },
	{ 10, -160 },
	{ 30, -180 },
	{ 100, -190 },
	{ 110, -180 },
	{ 130, -190 },
	{ 105, -210 },
	{ 60, -210 },
	{ 90, -225 }
};

POS THRUMBOEYE_points[2] =
{
	{ 115, -155 },
	{ 130, -140 }
};

CLogo::CLogo()
{
	for (int i = 0; i < 트럼보점개수; ++i)
		m_bodyPoints[i] = THRUMBO_points[i];

	m_eyePoints[0] = THRUMBOEYE_points[0];
	m_eyePoints[1] = THRUMBOEYE_points[1];
}

void CLogo::Update(float _fDeltaTime)
{	
	m_localTime += _fDeltaTime;
	if (m_localTime > 1.3f)
		m_IsDead = true;
	move(0, 0);
	Scale(1.15f);
	move(WIDTH / 2, 50.f + HIGHT / 2);

}

void CLogo::Rander(HDC _hdc)
{
	MoveToEx(_hdc, m_bodyPoints[0].X_COM, m_bodyPoints[0].Y_COM, nullptr);
	for (int i = 1; i < 트럼보점개수; ++i)
		LineTo(_hdc, m_bodyPoints[i].X_COM, m_bodyPoints[i].Y_COM);
	//LineTo(hdc, m_bodyPoints[0].x, m_bodyPoints[0].y);

	Ellipse(_hdc, m_eyePoints[0].X_COM, m_eyePoints[0].Y_COM, m_eyePoints[1].X_COM, m_eyePoints[1].Y_COM);
}


void CLogo::Scale(float _coef)
{
	for (int i = 0; i < 트럼보점개수; ++i)
	{
		m_bodyPoints[i].X_COM *= _coef;
		m_bodyPoints[i].Y_COM *= _coef;
	}

	m_eyePoints[0].X_COM *= _coef;
	m_eyePoints[0].Y_COM *= _coef;
	m_eyePoints[1].X_COM *= _coef;
	m_eyePoints[1].Y_COM *= _coef;
	

}

void CLogo::move(float _x, float _y)
{
	for (int i = 0; i < 트럼보점개수; ++i)
	{
		m_bodyPoints[i].X_COM += _x;
		m_bodyPoints[i].Y_COM += _y;
	}

	m_eyePoints[0].X_COM += _x;
	m_eyePoints[0].Y_COM += _y;
	m_eyePoints[1].X_COM += _x;
	m_eyePoints[1].Y_COM += _y;
}
