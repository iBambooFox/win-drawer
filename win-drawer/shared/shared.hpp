#pragma once

#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

using uint_t = unsigned int;
using ulong_t = unsigned long;
using uchar_t = unsigned char;
using void_t = void*;
using char_t = const wchar_t*;

#define PARAMS uint_t w, ulong_t l

#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <string>
#include <vector>

#pragma comment( lib, "gdiplus.lib" )

#include "utilities/drawing.hpp"
#include "utilities/window.hpp"