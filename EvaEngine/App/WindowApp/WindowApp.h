#pragma once
#include <Windows.h>

#ifdef EVAENGINE_EXPORTS
#define EVAENGINE_API __declspec(dllexport)
#else
#define EVAENGINE_API __declspec(dllimport)
#endif

class WindowApp {
public:
	EVAENGINE_API static HRESULT Init();
	EVAENGINE_API static int Update();
};