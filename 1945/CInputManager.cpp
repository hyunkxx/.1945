#include "pch.h"
#include "CInputManager.h"
#include "CCore.h"
#include "CShipBase.h"

CShipBase* CInputManager::pOwner;

void CInputManager::Possess(CShipBase* _pShip)
{
	pOwner = _pShip;
	pOwner->SetActive(true);
}

void CInputManager::UnPossess()
{
	pOwner->SetActive(false);
}

void CInputManager::Update(float _fDeltaTime)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 && pOwner)
	{
		if(pOwner->m_bActive)
			pOwner->MoveLeft();
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && pOwner)
	{
		if (pOwner->m_bActive)
			pOwner->MoveRight();
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000 && pOwner)
	{
		if (pOwner->m_bActive)
			pOwner->MoveUp();
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000 && pOwner)
	{
		if (pOwner->m_bActive)
			pOwner->MoveDown();
	}

	if (pOwner->bIsAttackCheck())
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000 && pOwner)
			pOwner->CreateBullet();
	}

	//PLTOYA
	if (GetAsyncKeyState('Q') & 0x8001 && pOwner)
	{
		if(pOwner->m_bActive)
			pOwner->Skill();
	}

	if (GetAsyncKeyState(VK_TAB) & 0x0001 && pOwner)
	{
	
		if (!pOwner->IsSwaping())
		{
			pOwner->ChangeShip();
		}
	}

	//Hit
	if (GetAsyncKeyState(VK_F11) & 0x0001 && pOwner)
	{
		if(pOwner->m_bActive)
			pOwner->HitDamage(5);
	}
}
