#include "pch.h"
#include "CCore.h"
#include "CShip.h"
#include "CInputManager.h"
#include "CBullet.h"

float CCore::g_DeltaTime;
RECT CCore::g_clientRect;

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
}

void CCore::Update(float _fDeltaTime)
{
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
}

void CCore::Render()
{
	background();
	/* Render */	//CObj->Render(m_hdc);

	for (auto iter = m_pBulletList.begin(); iter != m_pBulletList.end(); iter++)
		(*iter)->Render(m_hdc);

	m_pPlayer->Render(m_hdc);
}

void CCore::Release()
{
	ReleaseDC(m_hWnd, m_hdc);
}

void CCore::background()
{
	HBRUSH myBrush, blueBrush;
	blueBrush = (HBRUSH)CreateSolidBrush(RGB(0, 105, 255));
	myBrush = (HBRUSH)SelectObject(m_hdc, blueBrush);
	Ellipse(m_hdc, 0, 0, WIDTH + 100, HIGHT + 100);
	Rectangle(m_hdc, g_clientRect.left, g_clientRect.top, g_clientRect.right, g_clientRect.bottom);

	SelectObject(m_hdc, myBrush);
	DeleteObject(blueBrush);
}
