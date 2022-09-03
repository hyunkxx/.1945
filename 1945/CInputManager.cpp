#include "pch.h"
#include "CInputManager.h"
#include "CShip.h"

CShip* CInputManager::pOwner;

void CInputManager::Possess(CShip* _pShip)
{
	pOwner = _pShip;
}

void CInputManager::UnPossess()
{
	pOwner = nullptr;
}

void CInputManager::Update(float _fDeltaTime)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 && pOwner)
	{
		pOwner->Accelerate();
		pOwner->MoveLeft();
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x0000 && pOwner)
		pOwner->Decelderate();



	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && pOwner)
	{
		pOwner->Accelerate();
		pOwner->MoveRight();
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x0000 && pOwner)
		pOwner->Decelderate();



	if (GetAsyncKeyState(VK_UP) & 0x8000 && pOwner)
	{
		pOwner->Accelerate();
		pOwner->MoveUp();
	}
	if (GetAsyncKeyState(VK_UP) & 0x0000 && pOwner)
		pOwner->Decelderate();



	if (GetAsyncKeyState(VK_DOWN) & 0x8000 && pOwner)
	{
		pOwner->Accelerate();
		pOwner->MoveDown();
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
}
