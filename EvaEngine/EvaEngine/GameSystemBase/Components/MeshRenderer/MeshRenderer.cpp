#include "MeshRenderer.h"

#include <iterator>

#include "../../Base/GameObject/GameObject.h"

#include "../MeshFilter/MeshFilter.h"
#include "../Transform/Transform.h"
#include "../Camera/Camera.h"

#include "../../Manager/DrawManager/DrawManager.h"

using namespace EvaEngine;
using namespace FunctionMask;

MeshRenderer::MeshRenderer(
	const std::weak_ptr<MeshFilter>& meshFilter) :
	Component(DRAW, false),
	m_Model(meshFilter.lock()->GetModel()),
	m_MeshFilter(meshFilter)
{
}

void MeshRenderer::Awake() {
	m_Transform = GetTransform();
}

void MeshRenderer::Draw(const std::weak_ptr<Camera> camera, ID3D11DeviceContext* command)
{
	EvaEngine::Internal::DrawManager::Draw(camera, m_Transform, &m_Model);
}

#if _DEBUG
void EvaEngine::MeshRenderer::OnGUI()
{
}
#endif