#if _DEBUG
#include "SceneView.h"

std::weak_ptr<EvaEngine::Camera> EvaEngine::SceneView::GetSceneCamera()
{
	return m_SceneCamera;
}
#endif