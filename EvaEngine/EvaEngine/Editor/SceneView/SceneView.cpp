#if _DEBUG
#include "SceneView.h"

std::weak_ptr<Camera> EvaEngine::SceneView::GetSceneCamera()
{
	return m_SceneCamera;
}
#endif