#include "pch.h"
#include "CItem.h"

#include "CShipBase.h"

#include "CCollisionMgr.h"

CItem::CItem(string _szName)
	:m_szName(_szName)
{}

CItem::CItem(string _szName, Transform _transform)
	: m_szName(_szName), CObj(_transform)
{
	
}

CItem::CItem(string _szName, float _xPos, float _yPos, float _fScale)
	: m_szName(_szName), CObj(_xPos, _yPos, _fScale)
{}

void CItem::Initalize()
{}



void CItem::Update(float _fDeltaTime)
{
	auto pPlayer=CCollisionMgr::GetShip();

	float xdis = pPlayer->GetX() - m_transform.fX;
	float ydis = pPlayer->GetY() - m_transform.fY;

	m_transform.fX += xdis * _fDeltaTime;
	m_transform.fY += ydis * _fDeltaTime;

	SetRect();
}


void CItem::Render(HDC _hdc)
{
	Ellipse(_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
	
	TCHAR		szBuff[32] = L"";
	if (m_type == ÆøÅº)
		wsprintf(szBuff, L"B");
	else if(m_type == Æ÷¼Ç)
		wsprintf(szBuff, L"H");
	TextOut(_hdc, m_transform.fX-7.f, m_transform.fY-7.f, szBuff, lstrlen(szBuff));
}

