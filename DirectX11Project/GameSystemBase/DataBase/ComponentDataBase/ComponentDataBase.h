#pragma once

#include <string>
#include <list>
#include <queue>
#include <map>
#include <memory>
#include <stdexcept>
#include "../../Base/Component/Component.h"

class ComponentDataBase {
public:
	ComponentDataBase() = default;
	~ComponentDataBase() = default;

	// コンポーネントの登録
	template<class T, class... Args>
	std::weak_ptr<T> AddComponent(const SceneType& sceneType, const std::weak_ptr<GameObjectBase>& gameObject, Args&& ... args)
	{
		ComponentDesc componentDesc{};
		componentDesc.sceneType = sceneType;
		componentDesc.gameObject = gameObject;
		componentDesc.hashCode = typeid(T).hash_code();
		componentDesc.componentID = m_ComponentID;
		std::shared_ptr<T> component_temp = std::make_shared<T>(args...);
		component_temp->SetComponentDesc(componentDesc);

		// 複数アタッチできないコンポーネントの場合
		if (!component_temp->GetCanMultiAttach()) {
			// 同じコンポーネントが無いかチェック
			for (const auto& component : m_ComponentList[gameObject.lock()->GetObjectID()]) {
				if (componentDesc.hashCode == component->GetHashCode()) {
					throw std::runtime_error("Can't multi attach." + (std::string)typeid(T).name() + " : このコンポーネントは複数アタッチできません");
					return std::weak_ptr<T>();
				}
			}
		}

		// コンポーネントを追加(関数なども登録)
		AddComponent(gameObject, component_temp);
		// コンポーネントIDをインクリメント
		m_ComponentID += 1;

		// コンポーネントの初期関数を呼ぶ
		component_temp->Awake();
		component_temp->Start();


		// 参照を返す
		return component_temp;
	}

	// コンポーネントの取得
	template<class T>
	std::weak_ptr<T> GetComponent(const UINT& gameObjectID)
	{
		// コンポーネント検索
		for (const auto& component : m_ComponentList[gameObjectID]) {
			// 指定したコンポーネントのIDと同じIDの物が見つかればそれを返す
			if (typeid(T).hash_code() == component->GetHashCode()) {
				// dynamic_castを使用していないのは型変換チェックによる速度低下を防ぐため
				return std::static_pointer_cast<T>(component);
			}
		}

		throw std::runtime_error(
			"Not found. : Name : " +
			(std::string)typeid(T).name() +
			" : " +
			std::to_string(typeid(T).hash_code()) +
			" : コンポーネントが見つかりませんでした");
		return std::weak_ptr<T>();
	}

	// コンポーネントを削除
	template<class T>
	void RemoveComponent(const UINT& gameObjectID)
	{
		size_t hashCode = typeid(T).hash_code();
		for (const auto& component : m_ComponentList[gameObjectID]) {
			// 同じIDがあったら
			if (hashCode == component->GetHashCode()) {
				// 消せないコンポーネントなら早期リターン
				if (!component->GetCanRemove()) {
					throw std::runtime_error(
						"Can't remove component : " +
						(std::string)typeid(T).name() +
						" : " +
						std::to_string(typeid(T).hash_code()) +
						" : このコンポーネントは消せません");
					return;
				}

				// 消す対象のオブジェクトIDとコンポーネントのハッシュ値をQueueに追加
				std::map<UINT, size_t> removeList{ { gameObjectID, hashCode } };
				m_RemoveHashQueue.push(removeList);
				return;
			}
		}

		throw std::runtime_error(
			"Not found.: Name : " +
			(std::string)typeid(T).name() +
			" : " +
			std::to_string(typeid(T).hash_code()) +
			" : コンポーネントが見つかりませんでした");
	}

	// 削除依頼が出てるコンポーネントを消す
	void RunRemoveComponents();
	// 保持しているコンポーネントを全部削除
	void RemoveAllComponent();

	// FixedUpdate関数を回す
	void FixedUpdate();
	// Update関数を回す
	void Update();
	// LateUpdate関数を回す
	void LateUpdate();
	// Draw関数を回す
	void Draw(
		const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command) const;

private:
	template<class T>
	void AddComponent(const std::weak_ptr<GameObjectBase>& gameObject, std::shared_ptr<T> component) {
		// FixedUpdate関数の登録
		if (component->GetFunctionMask() & FunctionMask::FIXED_UPDATE) {
			m_FixedUpdateFunctionList[gameObject.lock()->GetObjectID()][m_ComponentID] = [=]()
				->void { return component->FixedUpdate(); };
		}
		// Update関数の登録
		if (component->GetFunctionMask() & FunctionMask::UPDATE) {
			m_UpdateFunctionList[gameObject.lock()->GetObjectID()][m_ComponentID] = [=]()
				->void { return component->Update(); };
		}
		// LateUpdate関数の登録
		if (component->GetFunctionMask() & FunctionMask::LATE_UPDATE) {
			m_LateUpdateFunctionList[gameObject.lock()->GetObjectID()][m_ComponentID] = [=]()
				->void { return component->LateUpdate(); };
		}
		// Draw関数の登録
		if (component->GetFunctionMask() & FunctionMask::DRAW) {
			m_DrawFunctionList[gameObject.lock()->GetObjectID()][m_ComponentID] = [=](const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command)
				->void { return component->Draw(command); };
		}
		// コンポーネントの登録
		m_ComponentList[gameObject.lock()->GetObjectID()].push_back(component);
	}


private:
	// コンポーネントのリスト(firstはオブジェクトID)
	std::map<UINT,		// GameObjectID
		std::list<std::shared_ptr<Component>>> m_ComponentList;

	// FixedUpdate関数のリスト
	std::map <UINT,	// GameObjectID
		std::map<UINT,	// ComponentID
		std::function<void()>>> m_FixedUpdateFunctionList;

	// Update関数のリスト
	std::map<UINT,		// GameObjectID
		std::map<UINT,	// ComponentID
		std::function<void()>>> m_UpdateFunctionList;

	// LateUpdate関数のリスト
	std::map<UINT,		// GameObjectID
		std::map<UINT,	// ComponentID
		std::function<void()>>> m_LateUpdateFunctionList;

	// Draw関数のリスト
	std::map<UINT,		// GameObjectID
		std::map<UINT,	// ComponentID
		std::function<void(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>&)>>> m_DrawFunctionList;

	// 削除予定のハッシュキュー
	std::queue<std::map<UINT, size_t>> m_RemoveHashQueue;

	UINT m_ComponentID{};
};