#pragma once

class CShip;

class CInputManager
{
public:
	CInputManager() = delete;
	~CInputManager() = delete;
public:
	static void Possess(CShip* _pShip);
	static void UnPossess();
	static void Update(float _fDeltaTime);
public:
	static CShip* pOwner;
};

