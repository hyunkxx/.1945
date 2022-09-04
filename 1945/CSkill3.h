#pragma once
#include "CSkill.h"

struct BOOM
{
    POS		pos;
    RECT	rect;
    float   raid;
    float	localTime;

};

class CSkill3 :
    public CSkill
{
public:
    CSkill3();
    virtual ~CSkill3() {}


public:
    virtual void Update(float _fDeltaTime) override;
    virtual void Render(HDC _hdc) override;

private:
    HWND    m_hwnd;
    POS     m_MousePos;
    RECT    m_MouseRECT;
    POS     m_MouseAimPos[4];
    float   m_Radi = 100.f;

private:
    POS     m_AimPos[4][2];

    float   m_angle = 0.f;
    bool    m_dir = true;

private:
    float CollTime = 0.f;

    list<BOOM>  m_Booms;

    float	dropSpeed = 0.135f;
    float   boomSpeed = 400.f;
};

