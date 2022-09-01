#include "pch.h"
#include "CCore.h"
#include "CShip.h"
#include "CBullet.h"

CShip::CShip()
	: CObj()
{
}

CShip::CShip(Transform _transform)
	: CObj(_transform)
{
}

CShip::CShip(float _xPos, float _yPos, float _fScale)
	: CObj(_xPos, _yPos, _fScale)
{
}

CShip::~CShip()
{
}

void CShip::Initalize()
{
	m_fCurSpeed = 0.0f;
	m_fMaxSpeed = 10.f;
	m_fLocalTime = 0.0f;
	m_fAttackDelay = 250.f;
	m_bAttackAble = true;
	attackTimer = 0;
}

void CShip::Update(float _fDeltaTime)
{
	if (GetTickCount64() >= attackTimer + m_fAttackDelay)
	{
		m_bAttackAble = true;
		attackTimer = GetTickCount64();
	}

	SetRect();
}

void CShip::Render(HDC _hdc)
{
	Rectangle(_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
}

void CShip::SetBullet(list<CObj*>* _pBulletList)
{
	m_pBulletList = _pBulletList;
}

void CShip::MoveLeft()
{
	if (m_transform.fX <= 0 + m_transform.fScale * 0.5f)
		return;

	float fMoveSpeed = m_fCurSpeed < m_fMaxSpeed ? m_fCurSpeed : m_fMaxSpeed;
	m_transform.fX -= fMoveSpeed * CCore::g_DeltaTime + 0.1f * m_fLocalTime;
}

void CShip::MoveRight()
{
	if (m_transform.fX >= WIDTH - m_transform.fScale * 0.5f)
		return;

	float fMoveSpeed = m_fCurSpeed < m_fMaxSpeed ? m_fCurSpeed : m_fMaxSpeed;
	m_transform.fX += fMoveSpeed * CCore::g_DeltaTime + 0.1f * m_fLocalTime;
}

void CShip::MoveUp()
{
	if (m_transform.fY <= 0 + m_transform.fScale * 0.5f)
		return;

	float fMoveSpeed = m_fCurSpeed < m_fMaxSpeed ? m_fCurSpeed : m_fMaxSpeed;
	m_transform.fY -= (fMoveSpeed * CCore::g_DeltaTime + 0.1f * m_fLocalTime);
}

void CShip::MoveDown()
{
	if (m_transform.fY >= HIGHT - m_transform.fScale * 0.5f)
		return;

	float fMoveSpeed = m_fCurSpeed < m_fMaxSpeed ? m_fCurSpeed : m_fMaxSpeed;
	m_transform.fY += fMoveSpeed * CCore::g_DeltaTime + 0.1f * m_fLocalTime;
}

void CShip::Accelerate()
{
	m_fLocalTime += CCore::g_DeltaTime;
}

void CShip::Decelderate()
{
	m_fLocalTime -= CCore::g_DeltaTime;
}

void CShip::CreateBullet()
{
	attackTimer = GetTickCount64();

	m_bAttackAble = false;


	m_pBulletList->push_back(new CBullet(m_transform.fX - 7, m_transform.fY));
	m_pBulletList->push_back(new CBullet(m_transform.fX + 7, m_transform.fY));
}
