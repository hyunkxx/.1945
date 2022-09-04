#pragma once

#include "CObj.h"

class IUsable
{
public:
	void Use(); //»ç¿ë?
	int  Hit(); //´ê¾ÒÀ»‹š?
};

class CItem : public CObj
{
public:
	CItem(string _szName);
	CItem(string _szName,Transform _transform);
	CItem(string _szName,float _xPos, float _yPos, float _fScale);
	virtual ~CItem() {};
public:
	string		GetName() { return m_szName; }
	void		SetName(string _szName) { m_szName =  _szName; }

	void		Initalize() override;
	void		Update(float _fDeltaTime);
	void		Render(HDC _hdc) override;
private:
	string m_szName;
};


class CPowerUpItem : public CItem, IUsable
{
public:

public:

private:
};


class CHitItem : public CItem, IUsable
{
public:

public:

private:
};