#include "ComponentDataBase.h"

void ComponentDataBase::FixedUpdate()
{
	auto tempFunc = m_FixedUpdateFunctionList;
	for (const auto& components : tempFunc) {
		for (const auto& fixedUpdateFunc : components.second) {
			fixedUpdateFunc.second();
		}
	}
}

void ComponentDataBase::Update()
{
	auto tempFunc = m_UpdateFunctionList;
	for (const auto& components : tempFunc) {
		for (const auto& updateFunc : components.second) {
			updateFunc.second();
		}
	}
}

void ComponentDataBase::LateUpdate()
{
	auto tempFunc = m_LateUpdateFunctionList;
	for (const auto& components : tempFunc) {
		for (const auto& lateUpdateFunc : components.second) {
			lateUpdateFunc.second();
		}
	}
}

void ComponentDataBase::Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command, const ModelApp& modelApp) const
{
	auto tempFunc = m_DrawFunctionList;
	for (const auto& components : tempFunc) {
		for (const auto& drawFunc : components.second) {
			drawFunc.second(command, modelApp);
		}
	}
}

void ComponentDataBase::RunRemoveComponents()
{
	while (!m_RemoveHashQueue.empty()) {
		for (const auto& removeMap : m_RemoveHashQueue.front()) {
			std::queue<std::shared_ptr<Component>> tempQueue;
			for (const auto& component : m_ComponentList[removeMap.first]) {
				if (component->GetHashCode() == removeMap.second) {
					// コンポーネントを消すキューに追加
					tempQueue.push(component);
				}
			}
			// 消すリストに追加されたコンポーネントを削除
			while (!tempQueue.empty())
			{
				if (tempQueue.front()->GetFunctionMask() & FunctionMask::FIXED_UPDATE) {
					m_FixedUpdateFunctionList[removeMap.first].erase(tempQueue.front()->GetComponentID());
				}
				if (tempQueue.front()->GetFunctionMask() & FunctionMask::UPDATE) {
					m_UpdateFunctionList[removeMap.first].erase(tempQueue.front()->GetComponentID());
				}
				if (tempQueue.front()->GetFunctionMask() & FunctionMask::LATE_UPDATE) {
					m_LateUpdateFunctionList[removeMap.first].erase(tempQueue.front()->GetComponentID());
				}
				if (tempQueue.front()->GetFunctionMask() & FunctionMask::DRAW) {
					m_DrawFunctionList[removeMap.first].erase(tempQueue.front()->GetComponentID());
				}
				m_ComponentList[removeMap.first].remove(tempQueue.front());

				// 削除したら削除キューから削除
				tempQueue.pop();
			}
		}
		// 削除したら削除キューから削除
		m_RemoveHashQueue.pop();
	}
}

void ComponentDataBase::RemoveAllComponent()
{
	m_FixedUpdateFunctionList.clear();
	m_UpdateFunctionList.clear();
	m_LateUpdateFunctionList.clear();
	m_DrawFunctionList.clear();
	m_ComponentList.clear();
	m_ComponentID = 0;
}
