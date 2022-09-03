#include "pch.h"
#include "CSkill3.h"

#include "CCore.h"




CSkill3::CSkill3()
{
	m_hwnd = CCore::g_HWND;
	m_MousePos = { -1000,-1000 };
}

void CSkill3::Update(float _fDeltaTime)
{
	if (m_isDead)
		return;

	// 스킬 총 시간
	if (m_localTime > 5.1f)
		m_isDead = true;
	
	float dt = _fDeltaTime;
	m_localTime += dt;

	POINT	ptMouse{};

	GetCursorPos(&ptMouse);		// 마우스의 포지션을 얻어오는 함수(스크린 좌표)
	ScreenToClient(m_hwnd, &ptMouse);	// 스크린 상의 마우스 좌표를 클라이언트 영역의 좌표로 변환하는 함수

	m_MousePos.X_COM = (float)ptMouse.x;
	m_MousePos.Y_COM = (float)ptMouse.y;

	Update_Rect_S(m_MouseRECT, m_MousePos, m_Radi);

	if (m_dir && m_angle < 3.141592f * 0.25f)
		m_angle += 2.f * dt;
	else
	{
		m_dir = false;
		m_angle -= 2.f * dt;
		if(m_angle<0.f- 3.141592f * 0.25f)
			m_dir = true;
	}
		
	for (int i = 0; i < 4; ++i)
	{
		m_AimPos[i][0].X_COM = m_MousePos.X_COM + (m_Radi - 50.f) * cosf(m_angle + (i * (3.141592f * 0.5f)));
		m_AimPos[i][0].Y_COM = m_MousePos.Y_COM + (m_Radi - 50.f) * sinf(m_angle + (i * (3.141592f * 0.5f)));
		m_AimPos[i][1].X_COM = m_MousePos.X_COM + (m_Radi + 50.f) * cosf(m_angle + (i * (3.141592f * 0.5f)));
		m_AimPos[i][1].Y_COM = m_MousePos.Y_COM + (m_Radi + 50.f) * sinf(m_angle + (i * (3.141592f * 0.5f)));
	}
	
	/*
	m_AimPos[1][0] = m_MousePos;
	m_AimPos[1][0].X_COM -= m_Radi;
	m_AimPos[1][1] = m_AimPos[1][0];
	m_AimPos[1][1].X_COM -= m_Radi;

	m_AimPos[2][0] = m_MousePos;
	m_AimPos[2][0].Y_COM += m_Radi;
	m_AimPos[2][1] = m_AimPos[2][0];
	m_AimPos[2][1].Y_COM += m_Radi;

	m_AimPos[3][0] = m_MousePos;
	m_AimPos[3][0].X_COM += m_Radi;
	m_AimPos[3][1] = m_AimPos[3][0];
	m_AimPos[3][1].X_COM += m_Radi;
	*/
	


	ShowCursor(false);

	CollTime += dt;

	if (m_localTime < 3.25f)
	{
		if (CollTime > 0.25f && GetAsyncKeyState(MK_LBUTTON) & 0x0001)
		{
			m_Booms.push_back({ m_MousePos , m_MouseRECT, m_Radi, 0.f});
			CollTime = 0;
		}
	}
		
	for (auto& boom : m_Booms)
	{
		boom.localTime += dt;
		boom.pos.Y_COM += 100.f*dt;
		if (boom.localTime < 1.f)
			boom.raid -= dropSpeed * boom.localTime;
		else
			boom.raid += boomSpeed * dt;

		Update_Rect_S(boom.rect, boom.pos, boom.raid);
	}
}

void CSkill3::Render(HDC _hdc)
{
	// 마이브러쉬, 회색, 노란색, 투명
	

	//MoveToEx(hdc, (int)m_turretPos.X_COM, (int)m_turretPos.Y_COM, nullptr);
	//LineTo(hdc, m_barrelPos[i].X_COM, m_barrelPos[i].Y_COM);

	for (auto& boom : m_Booms)
		Ellipse(_hdc, boom.rect.left, boom.rect.top, boom.rect.right, boom.rect.bottom);




	if (m_localTime > 3.25f)
		return;

	// 투명
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, myBrush);

	Ellipse(_hdc, m_MouseRECT.left, m_MouseRECT.top, m_MouseRECT.right, m_MouseRECT.bottom);

	SelectObject(_hdc, oldBrush);
	DeleteObject(myBrush);

	for (int i = 0; i < 4; ++i)
	{
		MoveToEx(_hdc, (int)m_AimPos[i][0].X_COM, (int)m_AimPos[i][0].Y_COM, nullptr);
		LineTo(_hdc, m_AimPos[i][1].X_COM, m_AimPos[i][1].Y_COM);
	}
}
