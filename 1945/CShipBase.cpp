#include "pch.h"
#include "CCore.h"
#include "CShipBase.h"
#include "CBullet.h"
#include "CInputManager.h"
#include "CSkill1.h"
#include "CSkill2.h"
#include "CSkill3.h"


CShipBase::CShipBase()
	: CObj()
{
	Initalize();
}


CShipBase::CShipBase(Transform _transform)
	: CObj(_transform)
{
	Initalize();
}

CShipBase::CShipBase(float _xPos, float _yPos, float _fScale)
	: CObj(_xPos, _yPos, _fScale)
{
	Initalize();
}

CShipBase::~CShipBase()
{
}

void CShipBase::Initalize()
{	
	//����&������ ������ ����Ʈ
	m_EntryPoint.x = WIDTH+200;
	m_EntryPoint.y = HIGHT;

	m_nMaxHealth = 100;
	m_nCurHealth = m_nMaxHealth;

	m_nMaxShield = 100;
	m_nCurShield = m_nMaxShield;

	m_fCurSpeed = 150.f;
	m_fLocalTime = 0.0f;
	m_fAttackDelay = 100.f;
	
	m_bAttackAble = true;
	attackTimer = 0;

	m_bSwapping = false;
	m_bActive = false;
	m_fSwapDelay = 800.f;
	m_fSwapSpeed = 600.f;
	swapTimer = 0;

	m_bTick = false;
	m_bIsDie = false;
}

void CShipBase::Update(float _fDeltaTime)
{
	//��Ȱ��ȭ �� Ship�鿡 ���õ� ���������� ƽ & Ȱ��ȭ�� Ship�� Y��ġ ����ȭ
	UnActiveShip(_fDeltaTime);

	//�Ѿ� �߻�� ������(100.f)
	if (GetTickCount64() >= attackTimer + m_fAttackDelay)
	{
		m_bAttackAble = true;
		attackTimer = GetTickCount64();
	}		

	if (m_bSwapping)
	{
		if (GetTickCount64() - swapTimer >= m_fSwapDelay)
		{
			//���� ������ �ð� ���޽� ����� �̵�
			m_bSwapping = false;

			CCore::g_nCurShipIndex = ++CCore::g_nCurShipIndex % 3;

			//�ð� ���޽� m_bActive false , ����� ȹ��
			CInputManager::UnPossess();
			CInputManager::Possess(static_cast<CShipBase*>(m_pCopyShip[CCore::g_nCurShipIndex % 3]));
		}
		
		else if(GetTickCount64() - swapTimer <= m_fSwapDelay)
		{
			//�����ϴ� �ð����� ���� �Ұ���
			m_bAttackAble = false;

			//���ҽð����� g_nCurShipIndex�� 2���� ū��� �ε����� 2�� �ʰ��Ұ��
			if (CCore::g_nCurShipIndex >= 2)
			{
				//Enter
				static_cast<CShipBase*>(m_pCopyShip[0])->Swap(_fDeltaTime);
				//Return
				static_cast<CShipBase*>(m_pCopyShip[CCore::g_nCurShipIndex % 3])->Swap(_fDeltaTime);
			}
			else
			{	
				//Enter
				static_cast<CShipBase*>(m_pCopyShip[CCore::g_nCurShipIndex + 1 % 3])->Swap(_fDeltaTime);
				//Return
				static_cast<CShipBase*>(m_pCopyShip[CCore::g_nCurShipIndex % 3])->Swap(_fDeltaTime);
			}
		}
	}

	SetRect();
}

void CShipBase::Render(HDC _hdc)
{
	WCHAR* buffer[3];

	for(int i = 0 ; i < 3 ; i++)
		buffer[i] = new WCHAR[TEXT_LENGTH];

	int i = 0;
	for(int i = 0 ; i < SHIP_COUNT ; i++)
	{
		wsprintf(buffer[i], L"CurIndex %d  ID %d   Active %d  Attackable %d  Swapping  %d"
			, CCore::g_nCurShipIndex,m_eShipID, m_bActive, m_bAttackAble,m_bSwapping);
	}

	switch (m_eShipID)
	{
	case SHIP_ONE:
		Rectangle(_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
		TextOut(_hdc, 10, 30, buffer[0], lstrlen(buffer[0]));
		break;
	case SHIP_TWO:
		Rectangle(_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
		TextOut(_hdc, 10, 50, buffer[1], lstrlen(buffer[1]));
		break;
	case SHIP_TRD:
		Ellipse(_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
		TextOut(_hdc, 10, 70, buffer[2], lstrlen(buffer[2]));
		break;
	}
}

void CShipBase::SetBullet(list<CObj*>* _pBulletList)
{
	m_pBulletList = _pBulletList;
}
void CShipBase::CreateBullet()
{
	attackTimer = GetTickCount64();

	m_bAttackAble = false;

	m_pBulletList->push_back(new CBullet(m_transform.fX - 7, m_transform.fY));
	m_pBulletList->push_back(new CBullet(m_transform.fX + 7, m_transform.fY));
}

void CShipBase::MoveLeft()
{
	if (m_transform.fX <= 0 + m_transform.fScale * 0.5f)
		return;

	m_transform.fX -= m_fCurSpeed * CCore::g_DeltaTime;
}
void CShipBase::MoveRight()
{
	if (m_transform.fX >= WIDTH - m_transform.fScale * 0.5f)
		return;

	m_transform.fX += m_fCurSpeed * CCore::g_DeltaTime;
}
void CShipBase::MoveUp()
{
	if (m_transform.fY <= 0 + m_transform.fScale * 0.5f)
		return;

	m_transform.fY -= m_fCurSpeed * CCore::g_DeltaTime;
}
void CShipBase::MoveDown()
{
	if (m_transform.fY >= HIGHT - m_transform.fScale * 0.5f)
		return;

	m_transform.fY += m_fCurSpeed * CCore::g_DeltaTime;
}

void CShipBase::ChangeShip()
{
	CInputManager::UnPossess();
	m_fLocalTime = 0.0f;
	if (!m_bSwapping)
	{
		swapTimer = GetTickCount64();
		m_bSwapping = true;
		m_LocalPos.x = static_cast<LONG>(m_pCopyShip[CCore::g_nCurShipIndex]->GetX());
		m_LocalPos.y = static_cast<LONG>(m_pCopyShip[CCore::g_nCurShipIndex]->GetY());
	}
}

void CShipBase::Swap(float _fDeltaTime)
{
	if (this == m_pCopyShip[CCore::g_nCurShipIndex])
	{
		//����
		m_transform.fY = Lerp(m_transform.fY, static_cast<float>(m_EntryPoint.y), _fDeltaTime);
		m_transform.fX = Lerp(m_transform.fX, static_cast<float>(m_EntryPoint.x), _fDeltaTime);
	}
	else
	{
		//����
		m_transform.fY = Lerp(m_transform.fY,  300 ,_fDeltaTime); 
		m_transform.fX = Lerp(m_transform.fX, -350 ,_fDeltaTime);
	}
}

void CShipBase::SyncPositionY(float _fDeltaTime)
{
	m_transform.fY = Lerp(m_transform.fY,
		static_cast<CShipBase*>(m_pCopyShip[CCore::g_nCurShipIndex])->GetY(), _fDeltaTime);
	m_transform.fX = Lerp(m_transform.fX, static_cast<float>(m_EntryPoint.x), _fDeltaTime);

	if (m_transform.fX > static_cast<float>(m_EntryPoint.x))
		m_transform.fX = static_cast<float>(m_EntryPoint.x);

}
void CShipBase::TickRecovery(const float _fDuration,const int _value)
{
	if (!m_bTick)
	{
		shieldTick = GetTickCount64();
		m_bTick = true;
	}

	if (GetTickCount64() >= _fDuration + shieldTick)
	{
		if (m_nCurShield < m_nMaxShield)
		{
			if (m_nCurShield + _value < m_nMaxShield)
				m_nCurShield += _value;
			else
				m_nCurShield = m_nMaxShield;
		}

		m_bTick = false;
		shieldTick = GetTickCount64();
	}
}
void CShipBase::HitDamage(int _iDamage)
{
	int offset;
	if (m_nCurShield > 0)
	{
		if (m_nCurShield < _iDamage)
		{
			offset = _iDamage - m_nCurShield;
			m_nCurShield = 0;
		}
		else
		{
			m_nCurShield -= _iDamage;
			goto CHEACK;
		}
	}

	if (m_nCurHealth >= _iDamage)
	{
		m_nCurHealth -= _iDamage;
	}
	else
		m_nCurHealth = 0;

CHEACK:
	if (m_nCurHealth <= 0)
		m_bIsDie = true;
}

void CShipBase::UnActiveShip(float _fDeltaTime)
{
	if (this == m_pCopyShip[CCore::g_nCurShipIndex])
		return;

	SyncPositionY(_fDeltaTime);
	TickRecovery(1000.f, 10);
}

//PLTOYA
void CShipBase::Skill()
{
	if (CCore::GetSkillInst())
		return;
	 
	CCore::SetSkill(new CSkill3);
}
