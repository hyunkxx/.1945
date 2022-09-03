#pragma once

#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <cmath>
#include <list>
#include <vector>
#include <queue>

#include "Define.h"
#include "def_Skill.h"


static float Lerp(float A, float B, float Alpha)
{
    return A * (1 - Alpha) + B * Alpha;
}

using namespace std;
