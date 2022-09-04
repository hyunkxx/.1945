#pragma once
#include "CObj.h"

enum SHIP_ID
{
	SHIP_ONE = 0,
	SHIP_TWO,
	SHIP_TRD,
	SHIP_END
};

class CShipBase : public CObj
{
	friend class CCollisionMgr;
	friend class CInputManager;
public:
	CShipBase();
	CShipBase(Transform _transform);
	CShipBase(float _xPos, float _yPos, float _fScale);
	virtual ~CShipBase();
public:
	void Initalize() override;
	void Update(float _fDeltaTime) override;
	void Render(HDC _hdc);
public:
	void SetShipList(CObj** _pShip)
	{
		m_pCopyShip = _pShip;
	};

	void  SetLowSpeed(float _fSpeed) { m_fLowSpeed = _fSpeed; }
	float GetLowSpeed() { return m_fLowSpeed; }

	void  SetBulletOne(list<CObj*>* _pBulletList);
	void  SetBulletTwo(list<CObj*>* _pBulletList);
	void  SetBulletTrd(list<CObj*>* _pBulletList);

	UINT GetCurHealth() { return m_nCurHealth; }
	UINT GetMaxHealth() { return m_nMaxHealth; }
	void SetCurHealth(UINT _nCurHealth) { m_nCurHealth = _nCurHealth; }
	void SetMaxHealth(UINT _nMaxHealth) { m_nMaxHealth = _nMaxHealth; }

	UINT GetCurShield() { return m_nCurShield; }
	UINT GetMaxShield() { return m_nMaxShield; }
	void SetCurShield(UINT _nCurShield) { m_nCurShield = _nCurShield; }
	void SetMaxShield(UINT _nMaxShield) { m_nMaxShield = _nMaxShield; }

	void SetActive(bool _value) { m_bActive = _value; }
	bool IsSwaping() { return m_bSwapping; }
	bool IsDie() { return m_bIsDie; }
public:
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void CreateBullet();
	bool bIsAttackCheck() { return m_bAttackAble; };

	void SetID(SHIP_ID _eID) { m_eShipID = _eID; }
	SHIP_ID GetID() { return m_eShipID; }

	void Die();
	void Recycle();
public:
	void ChangeShip();
	void Swap(float _fDeltaTime);
	void SyncPositionY(float _fDeltaTime);
public:
	void TickRecovery(const float _fDuration, const int _value);
	void HitDamage(int _iDamage);
	void AddHeal(int _value) { m_nCurHealth += _value; }
	void AddShield(int _value) { m_nCurShield += _value; }

	void UnActiveShip(float _fDeltaTime);

	void LocalSetting(float _lAttack, float _cAttack , float _lSpeed, float _cSpeed,float _lDelay,float _cDelay, float _projSpeed)
	{
		m_projectileSpeed = _projSpeed;

		m_fLowAttack = _lAttack;
		m_fCurAttack = _cAttack;

		m_fLowAttackDelay = _lDelay;
		m_fCurAttackDelay = _cDelay;

		m_fLowSpeed = _lSpeed;
		m_fCurSpeed = _cSpeed;
	}
public: // PLTOYA
	void Skill();
private:
	//진입&복귀할 오른쪽 포인트
	POINT m_EntryPoint;
	POINT m_LocalPos;

	CObj** m_pCopyShip;
	SHIP_ID m_eShipID;

	list<CObj*>* m_pBulletList_one;
	list<CObj*>* m_pBulletList_two;
	list<CObj*>* m_pBulletList_trd;

	float m_fLocalTime;

	ULONGLONG attackTimer;

	int m_nCurHealth;
	int m_nMaxHealth;

	int m_nCurShield;
	int m_nMaxShield;

	ULONGLONG swapTimer;
	float m_fSwapDelay;
	float m_fSwapSpeed;
	bool m_bSwapping;
	bool m_bActive;

	ULONGLONG shieldTick;
	bool m_bTick;

	//비행기별로 세팅할 변수들
	float m_projectileSpeed;

	bool  m_bIsDie;
	bool  m_bAttackAble;

	//CurAttack - LowAttack
	float m_fLowAttack;
	float m_fCurAttack; 

	//CurDelay - LowDelay;
	float m_fLowAttackDelay;
	float m_fCurAttackDelay;

	//CurSpeed - LowSpeed;
	float m_fLowSpeed;
	float m_fCurSpeed;
};


//class CShip : public CShipBase
//{
//public:
//	CShip();
//	CShip(Transform _transform);
//	CShip(float _xPos, float _yPos, float _fScale);
//	virtual ~CShip();
//public:
//	void Render(HDC _hdc) override;
//};
