#pragma once
#include <iostream>     // std::cout, std::fixed
#include <iomanip>      // std::setprecision
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
#define DLL_EXPORT   __declspec( dllexport )
#define SQUARE(a) (float) (a * a)
#define FLOAT_PI (float) M_PI

#define FLOAT_PRECISION 0

#define NORTH_PRIME 0.00F
#define NORTH 360.00F
#define SOUTH 180.00F
#define EAST 90.00F
#define WEST 270.00F

#define IsNegative(x) (bool) (x < 0.00F)
#define IsZero(x) (bool) (x == 0.00F)

using namespace std;
using namespace json;
