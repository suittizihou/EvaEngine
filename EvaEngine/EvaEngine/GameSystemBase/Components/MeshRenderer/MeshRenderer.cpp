#include "MeshRenderer.h"

#include <iterator>

#include "../../Base/GameObject/GameObject.h"

#include "../MeshFilter/MeshFilter.h"
#include "../Transform/Transform.h"
#include "../Camera/Camera.h"

#include "../../Manager/DrawManager/DrawManager.h"

//#include <chrono>

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

void MeshRenderer::Draw(const std::weak_ptr<Camera>& camera, ID3D11DeviceContext* command)
{
	//std::chrono::system_clock::time_point start, end;
	//start = std::chrono::system_clock::now();
	EvaEngine::Internal::DrawManager::Draw(camera, m_Transform, m_Model);
	//end = std::chrono::system_clock::now();
	//double elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

#if _DEBUG
void EvaEngine::MeshRenderer::OnGUI()
{
}
#endif