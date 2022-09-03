#include "pch.h"
#include "CObj.h"
#include "CUISystem.h"
#include "CShipBase.h"

WCHAR* CUISystem::m_szObjectCount;
 
CShipBase* CUISystem::m_pCopyShip[SHIP_COUNT];

RECT CUISystem::hpBackSize[3];
RECT CUISystem::hpFrontSize[3];

RECT CUISystem::ShieldBackSize[3];
RECT CUISystem::ShieldFrontSize[3];

void CUISystem::ConnectShip(CObj** m_pShip)
{
	m_pCopyShip[0] = static_cast<CShipBase*>(m_pShip[0]);
	m_pCopyShip[1] = static_cast<CShipBase*>(m_pShip[1]);
	m_pCopyShip[2] = static_cast<CShipBase*>(m_pShip[2]);
}

void CUISystem::Update(float _fDeltaTime)
{
	m_szObjectCount = new WCHAR[TEXT_LENGTH];
	wsprintf(m_szObjectCount, L"Object Count %d", (int)CObj::ObjectTotalCount);

	//Transform playerPosition = m_pPlayer->GetTransform();
	
	for(int i = 0 ; i < SHIP_END ; i ++)
		setBar(static_cast<SHIP_ID>(i));
}

void CUISystem::Render(HDC _hdc)
{
	SetBkMode(_hdc, TRANSPARENT);
	//Font setting
	TextOut(_hdc, 10, 10, m_szObjectCount, lstrlen(m_szObjectCount));

	WCHAR* hp1 = new TCHAR[TEXT_LENGTH];
	WCHAR* hp2 = new TCHAR[TEXT_LENGTH];
	WCHAR* hp3 = new TCHAR[TEXT_LENGTH];

	wsprintf(hp1, L" HP [ %d / %d ]", m_pCopyShip[0]->GetCurHealth(), m_pCopyShip[0]->GetMaxHealth());
	wsprintf(hp2, L" HP [ %d / %d ]", m_pCopyShip[1]->GetCurHealth(), m_pCopyShip[1]->GetMaxHealth());
	wsprintf(hp3, L" HP [ %d / %d ]", m_pCopyShip[2]->GetCurHealth(), m_pCopyShip[2]->GetMaxHealth());

	//HP  1
	TextOut(_hdc, 10, 100, hp1, lstrlen(hp1));
	//HP  2
	TextOut(_hdc, 10, 120, hp2, lstrlen(hp2));
	//HP  3
	TextOut(_hdc, 10, 140, hp3, lstrlen(hp3));

	drawBar(_hdc);
}

void CUISystem::drawBar(HDC _hdc)
{
	HBRUSH myBrush, hpBrush , shieldBrush , redBrush , warnningBrush, lockBrush;
	redBrush	= (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	hpBrush		= (HBRUSH)CreateSolidBrush(RGB(000, 255, 153));
	shieldBrush = (HBRUSH)CreateSolidBrush(RGB(102, 255, 255));

	warnningBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 102));
	lockBrush = (HBRUSH)CreateSolidBrush(RGB(051, 051, 051));

	for (int i = 0; i < SHIP_END; i++)
	{
		//HP 배경 & 게이지
		if (m_pCopyShip[i]->IsDie())
		{
			//죽었다?
			myBrush = (HBRUSH)SelectObject(_hdc, lockBrush);
			Rectangle(_hdc, hpBackSize[i].left, hpBackSize[i].top, hpBackSize[i].right, hpBackSize[i].bottom);
			Rectangle(_hdc, hpFrontSize[i].left, hpFrontSize[i].top, hpFrontSize[i].right, hpFrontSize[i].bottom);
			//쉴드 배경 & 게이지
			Rectangle(_hdc, ShieldBackSize[i].left, ShieldBackSize[i].top, ShieldBackSize[i].right, ShieldBackSize[i].bottom);
			Rectangle(_hdc, ShieldFrontSize[i].left, ShieldFrontSize[i].top, ShieldFrontSize[i].right, ShieldFrontSize[i].bottom);
			lockBrush = (HBRUSH)SelectObject(_hdc, myBrush);
		}
		else
		{
			Rectangle(_hdc, hpBackSize[i].left, hpBackSize[i].top, hpBackSize[i].right, hpBackSize[i].bottom);

			if( m_pCopyShip[i]->GetCurHealth() >= 70)
			{
				myBrush = (HBRUSH)SelectObject(_hdc, hpBrush);
				Rectangle(_hdc, hpFrontSize[i].left, hpFrontSize[i].top, hpFrontSize[i].right, hpFrontSize[i].bottom);
				hpBrush = (HBRUSH)SelectObject(_hdc, myBrush);
			}
			else if (m_pCopyShip[i]->GetCurHealth() <= 40)
			{
				myBrush = (HBRUSH)SelectObject(_hdc, redBrush);
				Rectangle(_hdc, hpFrontSize[i].left, hpFrontSize[i].top, hpFrontSize[i].right, hpFrontSize[i].bottom);
				redBrush = (HBRUSH)SelectObject(_hdc, myBrush);
			}
			else
			{
				myBrush = (HBRUSH)SelectObject(_hdc, warnningBrush);
				Rectangle(_hdc, hpFrontSize[i].left, hpFrontSize[i].top, hpFrontSize[i].right, hpFrontSize[i].bottom);
				warnningBrush = (HBRUSH)SelectObject(_hdc, myBrush);
			}


			//쉴드 배경 & 게이지
			Rectangle(_hdc, ShieldBackSize[i].left, ShieldBackSize[i].top, ShieldBackSize[i].right, ShieldBackSize[i].bottom);
			myBrush = (HBRUSH)SelectObject(_hdc, shieldBrush);
			Rectangle(_hdc, ShieldFrontSize[i].left, ShieldFrontSize[i].top, ShieldFrontSize[i].right, ShieldFrontSize[i].bottom);
			(HBRUSH)SelectObject(_hdc, myBrush);
		}
	}

	(HBRUSH)SelectObject(_hdc, myBrush);

	DeleteObject(redBrush);
	DeleteObject(hpBrush);
	DeleteObject(shieldBrush);
	DeleteObject(redBrush);
	DeleteObject(warnningBrush);
	DeleteObject(lockBrush);
}

void CUISystem::setBar(SHIP_ID _eID)
{
	enum {
		WIN_OFFSET = 50, //창과 HP BAR의 간격
		BAR_OFFSET = 3,   //HP 게이지와 바의 간격
		BAR_HIGHT = 14
	};

	switch (_eID)
	{
	case SHIP_ONE:
		ShieldBackSize[0].left = WIN_OFFSET - BAR_OFFSET;
		ShieldBackSize[0].top = HIGHT - WIN_OFFSET - BAR_OFFSET + 4;
		ShieldBackSize[0].right = ShieldBackSize[0].left + BAR_OFFSET + m_pCopyShip[0]->GetMaxShield();
		ShieldBackSize[0].bottom = ShieldBackSize[0].top + BAR_OFFSET + BAR_HIGHT;

		ShieldFrontSize[0].left = WIN_OFFSET;
		ShieldFrontSize[0].top = HIGHT - WIN_OFFSET + 3;
		ShieldFrontSize[0].right = ShieldBackSize[0].left + m_pCopyShip[0]->GetCurShield();
		ShieldFrontSize[0].bottom = ShieldBackSize[0].top + BAR_HIGHT;

		hpBackSize[0].left = WIN_OFFSET - BAR_OFFSET;
		hpBackSize[0].top = HIGHT - WIN_OFFSET - BAR_OFFSET + BAR_HIGHT + 5;
		hpBackSize[0].right = hpBackSize[0].left + BAR_OFFSET + m_pCopyShip[0]->GetMaxHealth();
		hpBackSize[0].bottom = hpBackSize[0].top + BAR_OFFSET + BAR_HIGHT - 1;

		hpFrontSize[0].left = WIN_OFFSET;
		hpFrontSize[0].top = hpBackSize[0].top + BAR_OFFSET;
		hpFrontSize[0].right = hpBackSize[0].left + m_pCopyShip[0]->GetCurHealth();
		hpFrontSize[0].bottom = hpBackSize[0].top + BAR_HIGHT;
		break;
	case SHIP_TWO:
		ShieldBackSize[1].left = WIN_OFFSET * 4 - BAR_OFFSET;
		ShieldBackSize[1].top = HIGHT - WIN_OFFSET - BAR_OFFSET + 4;
		ShieldBackSize[1].right = ShieldBackSize[1].left + BAR_OFFSET + m_pCopyShip[1]->GetMaxShield();
		ShieldBackSize[1].bottom = ShieldBackSize[1].top + BAR_OFFSET + BAR_HIGHT;

		ShieldFrontSize[1].left = WIN_OFFSET * 4;
		ShieldFrontSize[1].top = HIGHT - WIN_OFFSET + 3;
		ShieldFrontSize[1].right = ShieldBackSize[1].left + m_pCopyShip[1]->GetCurShield();
		ShieldFrontSize[1].bottom = ShieldBackSize[1].top + BAR_HIGHT;

		hpBackSize[1].left = WIN_OFFSET * 4 - BAR_OFFSET;
		hpBackSize[1].top = HIGHT - WIN_OFFSET - BAR_OFFSET + BAR_HIGHT + 5;
		hpBackSize[1].right = hpBackSize[1].left + BAR_OFFSET + m_pCopyShip[1]->GetMaxHealth();
		hpBackSize[1].bottom = hpBackSize[1].top + BAR_OFFSET + BAR_HIGHT - 1;

		hpFrontSize[1].left = WIN_OFFSET * 4;
		hpFrontSize[1].top = hpBackSize[1].top + BAR_OFFSET;
		hpFrontSize[1].right = hpBackSize[1].left + m_pCopyShip[1]->GetCurHealth();
		hpFrontSize[1].bottom = hpBackSize[1].top + BAR_HIGHT;
		break;
	case SHIP_TRD:
		ShieldBackSize[2].left = WIN_OFFSET * 7 - BAR_OFFSET;
		ShieldBackSize[2].top = HIGHT - WIN_OFFSET - BAR_OFFSET + 4;
		ShieldBackSize[2].right = ShieldBackSize[2].left + BAR_OFFSET + m_pCopyShip[2]->GetMaxShield();
		ShieldBackSize[2].bottom = ShieldBackSize[2].top + BAR_OFFSET + BAR_HIGHT;

		ShieldFrontSize[2].left = WIN_OFFSET * 7;
		ShieldFrontSize[2].top = HIGHT - WIN_OFFSET + 3;
		ShieldFrontSize[2].right = ShieldBackSize[2].left + m_pCopyShip[2]->GetCurShield();
		ShieldFrontSize[2].bottom = ShieldBackSize[2].top + BAR_HIGHT;

		hpBackSize[2].left = WIN_OFFSET * 7 - BAR_OFFSET;
		hpBackSize[2].top = HIGHT - WIN_OFFSET - BAR_OFFSET + BAR_HIGHT + 5;
		hpBackSize[2].right = hpBackSize[2].left + BAR_OFFSET + m_pCopyShip[2]->GetMaxHealth();
		hpBackSize[2].bottom = hpBackSize[2].top + BAR_OFFSET + BAR_HIGHT - 1;

		hpFrontSize[2].left = WIN_OFFSET * 7;
		hpFrontSize[2].top = hpBackSize[2].top + BAR_OFFSET;
		hpFrontSize[2].right = hpBackSize[2].left + m_pCopyShip[2]->GetCurHealth();
		hpFrontSize[2].bottom = hpBackSize[2].top + BAR_HIGHT;
		break;
	}
}
 