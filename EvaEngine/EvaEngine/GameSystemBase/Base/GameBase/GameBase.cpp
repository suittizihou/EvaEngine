#include "GameBase.h"
//#include "../../../System/DebugLog/DebugLog.h"
#include "../../../Setting/Window/Window.h"
#include "../../../App/WindowApp/WindowApp.h"
//#include "../../../App/DirectX11App/DirectX11App.h"
//#include "../../Manager/DrawManager/DrawManager.h"
//#include "../../../App/EvaEngineApp/EvaEngineApp.h"

EvaEngine::GameBase* EvaEngine::GameBase::m_GameBase{ nullptr };

EvaEngine::GameBase::GameBase(const unsigned int windowWidth, const unsigned int windowHeight)
{
	EvaEngine::Internal::Window::g_WindowRight = windowWidth;
	EvaEngine::Internal::Window::g_WindowBottom = windowHeight;
	m_GameBase = this;
}

EvaEngine::GameBase* EvaEngine::GameBase::Instance()
{
	return m_GameBase;
}
