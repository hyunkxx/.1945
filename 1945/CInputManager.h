#pragma once

class CShipBase;

class CInputManager
{
public:
	CInputManager() = delete;
	~CInputManager() = delete;
public:
	static void Possess(CShipBase* _pShip);
	static void UnPossess();
	static void Update(float _fDeltaTime);
public:
	static CShipBase* pOwner;
};

