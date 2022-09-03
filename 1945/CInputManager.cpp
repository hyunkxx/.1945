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
<<<<<<< Updated upstream
		pOwner->Accelerate();
		pOwner->MoveLeft();
=======
		if(pOwner->m_bActive)
			pOwner->MoveLeft();
>>>>>>> Stashed changes
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x0000 && pOwner)
		pOwner->Decelderate();


	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && pOwner)
	{
<<<<<<< Updated upstream
		pOwner->Accelerate();
		pOwner->MoveRight();
=======
		if (pOwner->m_bActive)
			pOwner->MoveRight();
>>>>>>> Stashed changes
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x0000 && pOwner)
		pOwner->Decelderate();


	if (GetAsyncKeyState(VK_UP) & 0x8000 && pOwner)
	{
<<<<<<< Updated upstream
		pOwner->Accelerate();
		pOwner->MoveUp();
=======
		if (pOwner->m_bActive)
			pOwner->MoveUp();
>>>>>>> Stashed changes
	}
	if (GetAsyncKeyState(VK_UP) & 0x0000 && pOwner)
		pOwner->Decelderate();


	if (GetAsyncKeyState(VK_DOWN) & 0x8000 && pOwner)
	{
<<<<<<< Updated upstream
		pOwner->Accelerate();
		pOwner->MoveDown();
=======
		if (pOwner->m_bActive)
			pOwner->MoveDown();
>>>>>>> Stashed changes
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x0000 && pOwner)
		pOwner->Decelderate();



	if (pOwner->bIsAttackCheck())
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000 && pOwner)
			pOwner->CreateBullet();
	}

	//PLTOYA
	if (GetAsyncKeyState('1') & 0x8001 && pOwner)
		pOwner->Skill();

	//체인지 시 조종 불가능 혹은 대기 쿨타임 만들어야함
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
