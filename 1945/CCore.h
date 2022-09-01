#pragma once
class CObj;
class CBullet;

class CCore
{
public:
	CCore();
	~CCore();
public:
	static float g_DeltaTime;
	static RECT g_clientRect;
public:
	void Initalize(HWND _hWnd, HINSTANCE _hInstance, RECT _clientRect);
	void Update(float _fDeltaTime);
	void Render();
	void Release();
private:
	void background();
public:

	HDC				m_hdc;
	HWND			m_hWnd;
	HINSTANCE		m_hInstance;

private: /* Object */
	CObj* m_pPlayer;
	list<CObj*> m_pBulletList;
private:

};

