#pragma once
#include "CObj.h"

class CItem : public CObj
{
public:
    CItem(string _szName);
    CItem(string _szName, Transform _transform);
    CItem(string _szName, float _xPos, float _yPos, float _fScale);
    virtual ~CItem() {};
public:
    string      GetName() { return m_szName; }
    void        SetName(string _szName) { m_szName = _szName; }
    TYPE_ITEM   GetItemType() { return m_type; }

    void        Initalize() override;
    void        Update(float _fDeltaTime) override;
    void        Render(HDC _hdc) override;


private:



protected:
    string      m_szName;
    TYPE_ITEM   m_type;
    float       m_speed;

};
