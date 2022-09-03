#pragma once

#include "CShipBase.h"

class CUISystem
{
public:
	CUISystem()  = delete;
	~CUISystem() = delete;
public:
	static void ConnectShip(CObj** m_pShip);
	static void Update(float _fDeltaTime);
	static void Render(HDC _hdc);

	static CShipBase* m_pCopyShip[SHIP_COUNT];
private: 
	//static CShipBase* m_pOne;
	//static CShipBase* m_pTwo;
	//static CShipBase* m_pTrd;

	static WCHAR* m_szObjectCount;

	static RECT hpBackSize[3];
	static RECT hpFrontSize[3];

	static RECT ShieldBackSize[3];
	static RECT ShieldFrontSize[3];

private:
	static void drawBar(HDC _hdc);
	static void setBar(SHIP_ID _eID);
};

