#include "pch.h"
#include "CCore.h"
#include "CShipBase.h"
#include "CInputManager.h"
#include "CBullet.h"
#include "CSkill.h"
#include "CUISystem.h"

float CCore::g_DeltaTime;
RECT CCore::g_clientRect;
HWND CCore::g_HWND;

int CCore::g_nCurShipIndex;
int CCore::g_nNextShipIndex;
//PLTOYA
CSkill* CCore::m_pSkill = nullptr;

CCore::CCore()
	: m_hdc(0)
	, m_hWnd(0)
	, m_hBit(0)
	, m_subDC(0)
	, m_hInstance(0)
{
	for (int i = 0; i < SHIP_COUNT; i++)
		m_pShip[i] = nullptr;
}

CCore::~CCore()
{
	Release();
}

void CCore::Initalize(HWND _hWnd, HINSTANCE _hInstance, RECT _clientRect)
{
	g_HWND = _hWnd;
	m_hWnd = _hWnd;
	m_hdc = GetDC(m_hWnd);
	m_hInstance = _hInstance;
	g_clientRect = _clientRect;

	for (int i = 0; i < SHIP_COUNT; i++)
	{
		m_pShip[i] = new CShipBase(WIDTH - WIDTH, HIGHT * 0.8f, 40.f);
	}

	m_pShip[CCore::g_nCurShipIndex]->SetX(WIDTH / 2);

	for (int i = 0; i < SHIP_COUNT; i++)
	{
		static_cast<CShipBase*>(m_pShip[i])->SetShipList(m_pShip);
	}

	for (auto* ship : m_pShip)
		static_cast<CShipBase*>(ship)->Initalize();

	int i = 0;
	for (auto* ship : m_pShip)
	{
		static_cast<CShipBase*>(ship)->SetID(SHIP_ID(i));
		i++;
	}

	//static_cast<CShipBase*>(m_pShip[0])->SetCurHealth(100);
	//static_cast<CShipBase*>(m_pShip[1])->SetCurHealth(100);
	//static_cast<CShipBase*>(m_pShip[2])->SetCurHealth(100);

	CInputManager::Possess(static_cast<CShipBase*>(m_pShip[g_nCurShipIndex]));
	
	for (int i = 0; i < SHIP_COUNT; i++)
		CUISystem::ConnectShip(m_pShip);

	for (auto* elem : m_pBulletList)
	{
		elem->Initalize();
	}

	for (auto* iter : m_pShip)
		static_cast<CShipBase*>(iter)->SetBullet(&m_pBulletList);

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

	for (auto iter = m_pBulletList.begin() ; iter != m_pBulletList.end() ; )
	{
		(*iter)->Update(_fDeltaTime);

		if (static_cast<CBullet*>((*iter))->IsDie())
		{
			delete (*iter);
			iter = m_pBulletList.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	for (int i = 0 ;  i < SHIP_COUNT ; i++)
		m_pShip[i]->Update(_fDeltaTime);


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

	CUISystem::Update(_fDeltaTime);
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
	Rectangle(m_subDC, WIDTH / 2 - 90, 0, WIDTH / 2 + 90, 700);
	SelectObject(m_subDC, myBrush);
	DeleteObject(tempBrush);

	tempBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
	myBrush = (HBRUSH)SelectObject(m_subDC, tempBrush);
	Rectangle(m_subDC, WIDTH / 2 - 5, static_cast<int>(-45 + 400.f * m_localTime), WIDTH / 2 + 5, static_cast < int>(0 +   400.f * m_localTime));
	Rectangle(m_subDC, WIDTH / 2 - 5, static_cast<int>(45  + 400.f * m_localTime), WIDTH  / 2 + 5, static_cast < int>(90 + 400.f * m_localTime));
	Rectangle(m_subDC, WIDTH / 2 - 5, static_cast<int>(135 + 400.f * m_localTime), WIDTH / 2 + 5, static_cast < int>(180 + 400.f * m_localTime));
	Rectangle(m_subDC, WIDTH / 2 - 5, static_cast<int>(225 + 400.f * m_localTime), WIDTH / 2 + 5, static_cast < int>(270 + 400.f * m_localTime));
	Rectangle(m_subDC, WIDTH / 2 - 5, static_cast<int>(315 + 400.f * m_localTime), WIDTH / 2 + 5, static_cast < int>(360 + 400.f * m_localTime));
	Rectangle(m_subDC, WIDTH / 2 - 5, static_cast<int>(405 + 400.f * m_localTime), WIDTH / 2 + 5, static_cast < int>(450 + 400.f * m_localTime));
	Rectangle(m_subDC, WIDTH / 2 - 5, static_cast<int>(495 + 400.f * m_localTime), WIDTH / 2 + 5, static_cast < int>(540 + 400.f * m_localTime));
	Rectangle(m_subDC, WIDTH / 2 - 5, static_cast<int>(585 + 400.f * m_localTime), WIDTH / 2 + 5, static_cast < int>(630 + 400.f * m_localTime));
	Rectangle(m_subDC, WIDTH / 2 - 5, static_cast<int>(675 + 400.f * m_localTime), WIDTH / 2 + 5, static_cast < int>(720 + 400.f * m_localTime));

	SelectObject(m_subDC, myBrush);
	DeleteObject(tempBrush);

	// PLTOYA
	if (m_pSkill && !m_pSkill->IsDead())
		m_pSkill->Render(m_subDC);

	/* Render */	//CObj->Render(m_hdc);
	for (auto* elem : m_pBulletList)
		elem->Render(m_subDC);

	for (auto& iter : m_pShip)
		iter->Render(m_subDC);

	//UI > Render
	CUISystem::Render(m_subDC);

	BitBlt(m_hdc, 0, 0, WIDTH, HIGHT, m_subDC, 0, 0, SRCCOPY);
}

void CCore::Release()
{
	ReleaseDC(m_hWnd, m_hdc);


	for (auto& iter : m_pShip)
		delete iter;

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
