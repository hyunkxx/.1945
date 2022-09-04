#pragma once
class CObj;
class CBullet;
class CUISystem;

class CCore
{
public:
	CCore();
	~CCore();
public:
	static float g_DeltaTime;
	static RECT g_clientRect;
	static int g_nCurShipIndex;
	static int g_nNextShipIndex;
	static HWND	g_HWND;
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
	CObj*		m_pShip[3];
	list<CObj*> m_pBulletList;

// PLTOYA
public:
	static class CSkill* GetSkillInst() { return m_pSkill; }
	static void		     SetSkill(CSkill* _Skill) { m_pSkill = _Skill; }
private:
	static CSkill* m_pSkill;
private:
	HBITMAP m_hBit;
	HDC     m_subDC;
private:
	float	m_localTime = 0;

private:
	class CLogo* m_logo=nullptr;


	// 여기서부터 진건 추가

	// 몬스터 타입 , 각 타입의 스폰 포인트
public:
	void CreateEnemy(int _iType, int _iPoint, int _iStage);

private:
	list<CObj*>		m_pEnemyList;
	CObj*			m_pEnemy = nullptr;
	list<CObj*>		m_pEnemyBulletList;

	int      m_iStage_Count = 0;
	int      m_iStage = 1;
	float    m_LocalTime_E = 0.f;


private:
	list<CObj*>		m_pItemList;

};

