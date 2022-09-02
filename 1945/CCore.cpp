#include "pch.h"
#include "CCore.h"
#include "CShip.h"
#include "CInputManager.h"
#include "CBullet.h"

#include "CSkill.h"

float CCore::g_DeltaTime;
RECT CCore::g_clientRect;

//PLTOYA
CSkill* CCore::m_pSkill = nullptr;

CCore::CCore()
	: m_hdc(0)
	, m_hWnd(0)
	, m_hInstance(0)
	, m_pPlayer(nullptr)
{
}

CCore::~CCore()
{
	Release();
}

void CCore::Initalize(HWND _hWnd, HINSTANCE _hInstance, RECT _clientRect)
{
	m_hWnd = _hWnd;
	m_hdc = GetDC(m_hWnd);
	m_hInstance = _hInstance;
	g_clientRect = _clientRect;

	/* Object */
	m_pPlayer = new CShip(WIDTH * 0.5f, HIGHT * 0.8f, 40.f);
	CInputManager::Possess(static_cast<CShip*>(m_pPlayer));

	/* Initalize Call */
	m_pPlayer->Initalize();

	for (auto* elem : m_pBulletList)
	{
		elem->Initalize();
	}

	static_cast<CShip*>(m_pPlayer)->SetBullet(&m_pBulletList);

	//PLTOYA
	m_hBit = CreateCompatibleBitmap(m_hdc, WIDTH, HIGHT);
	m_subDC = CreateCompatibleDC(m_hdc);

	HBITMAP hDefaultBitmap = (HBITMAP)SelectObject(m_subDC, m_hBit);
	DeleteObject(hDefaultBitmap);

	//
}

void CCore::Update(float _fDeltaTime)
{
	//PLTOYA
	Rectangle(m_subDC, -1, -1, WIDTH + 1, HIGHT + 1);
	
	g_DeltaTime = _fDeltaTime;
	CInputManager::Update(_fDeltaTime);

	for (auto iter = m_pBulletList.begin() ; iter != m_pBulletList.end() ; ++iter)
	{
		(*iter)->Update(_fDeltaTime);

		if (static_cast<CBullet*>((*iter))->IsDie())
		{
			delete[] (*iter);
			iter = m_pBulletList.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	m_pPlayer->Update(_fDeltaTime);

	// PLTOYA
	if (m_pSkill && !m_pSkill->IsDead())
	{
		m_pSkill->Update(_fDeltaTime);
		if (m_pSkill->IsDead())
		{
			delete m_pSkill;
			m_pSkill = nullptr;
		}
	}
}

void CCore::Render()
{
	background();
	// PLTOYA
	m_localTime += g_DeltaTime;
	if (-45 + 200.f * m_localTime > 45.0001f)
		m_localTime = 0;

	HBRUSH myBrush, tempBrush;
	tempBrush = (HBRUSH)CreateSolidBrush(RGB(80, 80, 80));
	myBrush = (HBRUSH)SelectObject(m_subDC, tempBrush);
	Rectangle(m_subDC, WIDTH / 2 - 45, 0, WIDTH / 2 + 45, 700);
	SelectObject(m_subDC, myBrush);
	DeleteObject(tempBrush);

	tempBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
	myBrush = (HBRUSH)SelectObject(m_subDC, tempBrush);
	Rectangle(m_subDC, WIDTH / 2 - 5, -45 + 200.f * m_localTime, WIDTH / 2 + 5, 0 + 200.f * m_localTime);
	Rectangle(m_subDC, WIDTH / 2 - 5, 45 + 200.f * m_localTime, WIDTH / 2 + 5, 90 + 200.f * m_localTime);
	Rectangle(m_subDC, WIDTH / 2 - 5, 135 + 200.f * m_localTime, WIDTH / 2 + 5, 180 + 200.f * m_localTime);
	Rectangle(m_subDC, WIDTH / 2 - 5, 225 + 200.f * m_localTime, WIDTH / 2 + 5, 270 + 200.f * m_localTime);
	Rectangle(m_subDC, WIDTH / 2 - 5, 315 + 200.f * m_localTime, WIDTH / 2 + 5, 360 + 200.f * m_localTime);
	Rectangle(m_subDC, WIDTH / 2 - 5, 405 + 200.f * m_localTime, WIDTH / 2 + 5, 450 + 200.f * m_localTime);
	Rectangle(m_subDC, WIDTH / 2 - 5, 495 + 200.f * m_localTime, WIDTH / 2 + 5, 540 + 200.f * m_localTime);
	Rectangle(m_subDC, WIDTH / 2 - 5, 585 + 200.f * m_localTime, WIDTH / 2 + 5, 630 + 200.f * m_localTime);
	Rectangle(m_subDC, WIDTH / 2 - 5, 675 + 200.f * m_localTime, WIDTH / 2 + 5, 720 + 200.f * m_localTime);

	SelectObject(m_subDC, myBrush);
	DeleteObject(tempBrush);

	/* Render */	//CObj->Render(m_hdc);
	for (auto* elem : m_pBulletList)
		elem->Render(m_subDC);

	m_pPlayer->Render(m_subDC);

	// PLTOYA
	if (m_pSkill && !m_pSkill->IsDead())
		m_pSkill->Render(m_subDC);
	BitBlt(m_hdc, 0, 0, WIDTH, HIGHT, m_subDC, 0, 0, SRCCOPY);

}

void CCore::Release()
{
	ReleaseDC(m_hWnd, m_hdc);

	//PLTOYA
	DeleteDC(m_subDC);
	DeleteObject(m_hBit);
}

void CCore::background()
{
	HBRUSH myBrush, blueBrush;
	blueBrush = (HBRUSH)CreateSolidBrush(RGB(0, 105, 255));
	myBrush = (HBRUSH)SelectObject(m_subDC, blueBrush);
	//Ellipse(m_hdc, 0, 0, WIDTH + 100, HIGHT + 100);
	Rectangle(m_subDC, g_clientRect.left, g_clientRect.top, g_clientRect.right, g_clientRect.bottom);

	SelectObject(m_subDC, myBrush);
	DeleteObject(blueBrush);
}
