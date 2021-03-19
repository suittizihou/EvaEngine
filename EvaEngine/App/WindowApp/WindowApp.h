#pragma once
#include <Windows.h>

#ifdef EVAENGINE_EXPORTS
#define __declspec(dllexport)
#else
#define __declspec(dllimport)
#endif

class WindowApp {
public:
	static HRESULT Init();
	static int Update();
};