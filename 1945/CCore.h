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

// PLTOYA
public:
	static HWND g_HWND;
	static class CSkill* GetSkillInst() { return m_pSkill; }
	static void		     SetSkill(CSkill* _Skill) { m_pSkill = _Skill; }
private:
	static CSkill* m_pSkill;
private:
	HBITMAP m_hBit;
	HDC     m_subDC;
private:
	float	m_localTime = 0;
//



};

