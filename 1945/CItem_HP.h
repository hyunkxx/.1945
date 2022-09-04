#pragma once
#include "CItem.h"
class CItem_HP :
    public CItem
{

public:
    CItem_HP(string _szName, Transform _transform);
    virtual ~CItem_HP() {};

};

