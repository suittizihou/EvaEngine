#if _DEBUG
#include "SceneView.h"

std::weak_ptr<EvaEngine::Camera> EvaEngine::Editor::Internal::SceneView::GetSceneCamera()
{
	return m_SceneCamera;
}
#endif