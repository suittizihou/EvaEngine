#include "ComponentDataBase.h"
#include "../../Base/GameObject/GameObject.h"
#include "../../Components/Camera/Camera.h"
#include <iterator>

using namespace EvaEngine;

void ComponentDataBase::FixedUpdate()
{
	for (int i = 0; i < m_FixedUpdateFuncNumber.size(); ++i) {
		m_Components[m_FixedUpdateFuncNumber[i]]->FixedUpdate();
	}
}

void ComponentDataBase::Update()
{
	for (int i = 0; i < m_UpdateFuncNumber.size(); ++i) {
		m_Components[m_UpdateFuncNumber[i]]->Update();
	}
}

void ComponentDataBase::LateUpdate()
{
	for (int i = 0; i < m_LateUpdateFuncNumber.size(); ++i) {
		m_Components[m_LateUpdateFuncNumber[i]]->LateUpdate();
	}
}

void ComponentDataBase::Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command) const
{
	// カメラの数だけ描画する
	//std::vector<std::weak_ptr<Camera>> cameras = Camera::GetAllCamera();
	//for (int cameraNum = 0; cameraNum < cameras.size(); ++cameraNum) {
		for (int i = 0; i < m_DrawFuncNumber.size(); ++i) {
			m_Components[m_DrawFuncNumber[i]]->Draw(Camera::GetMainCamera(), command);
		}
	//}
}

#if _DEBUG
void EvaEngine::ComponentDataBase::OnGUI(const SceneView& sceneView)
{
	for (const auto& component : m_Components) {
		component->OnGUI(sceneView);
	}
}
#endif

void ComponentDataBase::AddComponent(const std::shared_ptr<Component>& component, const int indexNum) {
	// FixedUpdate関数の登録
	if (component->GetFunctionMask() & FunctionMask::FIXED_UPDATE) {
		m_FixedUpdateFuncNumber.push_back(indexNum);
	}
	// Update関数の登録
	if (component->GetFunctionMask() & FunctionMask::UPDATE) {
		m_UpdateFuncNumber.push_back(indexNum);
	}
	// LateUpdate関数の登録
	if (component->GetFunctionMask() & FunctionMask::LATE_UPDATE) {
		m_LateUpdateFuncNumber.push_back(indexNum);
	}
	// Draw関数の登録
	if (component->GetFunctionMask() & FunctionMask::DRAW) {
		m_DrawFuncNumber.push_back(indexNum);
	}
	// コンポーネントの登録
	m_Components.push_back(component);
}

void ComponentDataBase::RemoveComponent(const int index, const UINT mask)
{
	// 末尾のコンポーネントが使用している関数マスクを取得
	UINT endElementMask = m_Components.back()->GetFunctionMask();

	// 消す場所と末尾をクルっと入れ替え
	std::iter_swap(m_Components.begin() + index, m_Components.end() - 1);
	// 末尾を削除
	m_Components.pop_back();

	// 削除前のコンポーネントがあった配列番号を各関数添字配列の末尾に入れる
	// (この削除前の添字の場所(m_Components配列の場所)には削除しないコンポーネントの添字が入っている)
	if (endElementMask & FunctionMask::FIXED_UPDATE) m_FixedUpdateFuncNumber[m_FixedUpdateFuncNumber.size() - 1] = index;
	if (endElementMask & FunctionMask::UPDATE) m_UpdateFuncNumber[m_UpdateFuncNumber.size() - 1] = index;
	if (endElementMask & FunctionMask::LATE_UPDATE) m_LateUpdateFuncNumber[m_LateUpdateFuncNumber.size() - 1] = index;
	if (endElementMask & FunctionMask::DRAW) m_DrawFuncNumber[m_DrawFuncNumber.size() - 1] = index;

	if (mask & FunctionMask::FIXED_UPDATE)
	{
		// 末尾の値を指定の場所にコピー
		m_FixedUpdateFuncNumber[FindItr(m_FixedUpdateFuncNumber, index)] = m_FixedUpdateFuncNumber.back();
		// 末尾を消す
		m_FixedUpdateFuncNumber.pop_back();
	}

	if (mask & FunctionMask::UPDATE)
	{
		// 末尾の値を指定の場所にコピー
		m_UpdateFuncNumber[FindItr(m_UpdateFuncNumber, index)] = m_UpdateFuncNumber.back();
		// 末尾を消す
		m_UpdateFuncNumber.pop_back();
	}

	if (mask & FunctionMask::LATE_UPDATE)
	{
		// 末尾の値を指定の場所にコピー
		m_LateUpdateFuncNumber[FindItr(m_LateUpdateFuncNumber, index)] = m_LateUpdateFuncNumber.back();
		// 末尾を消す
		m_LateUpdateFuncNumber.pop_back();
	}

	if (mask & FunctionMask::DRAW)
	{
		// 末尾の値を指定の場所にコピー
		m_DrawFuncNumber[FindItr(m_DrawFuncNumber, index)] = m_DrawFuncNumber.back();
		// 末尾を消す
		m_DrawFuncNumber.pop_back();
	}
}

__int64 ComponentDataBase::FindItr(const std::vector<int>& vec, int value)
{
	return std::distance(vec.begin(), std::find(vec.begin(), vec.end(), value));
}

bool ComponentDataBase::IsGameObjectIDEquals(const std::weak_ptr<GameObject>& obj, const UINT& id)
{
	return obj.lock()->GetObjectID() == id;
}

bool ComponentDataBase::IsGameObjectIDEquals(const std::weak_ptr<GameObject>& obj1, const std::weak_ptr<GameObjectBase>& obj2)
{
	return obj1.lock()->GetObjectID() == obj2.lock()->GetObjectID();
}

void ComponentDataBase::RemoveAllComponent()
{
	m_FixedUpdateFuncNumber.clear();
	m_UpdateFuncNumber.clear();
	m_LateUpdateFuncNumber.clear();
	m_DrawFuncNumber.clear();
	m_Components.clear();
	m_ComponentID = 0;
}
