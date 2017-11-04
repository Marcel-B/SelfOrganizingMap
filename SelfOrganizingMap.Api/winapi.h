#pragma once
#include "../SelfOrganizingMap/som.hpp"
#include "sominfo.h"

extern "C" __declspec(dllexport) void* __cdecl GetHandle();
extern "C" __declspec(dllexport) SomInfo __cdecl GetSom();
extern "C" __declspec(dllexport) int __stdcall PlusFive(int number);
