#pragma once

#include <string>
#include <list>
#include <queue>
#include <map>
#include <memory>
#include <stdexcept>
#include <functional>
#include "../../Base/Component/Component.h"
#include "../../DataBase/ComponentDataBase/ComponentDataBase.h"
#include "../../Base/GameObject/GameObjectBase.h"

namespace EvaEngine {

	class ComponentManager {
	private:
		ComponentManager() = default;
		ComponentManager(const ComponentManager&);
		ComponentManager& operator=(const ComponentManager&);
		~ComponentManager() = default;

	public:
		static ComponentManager& Instance() {
			static ComponentManager componentManager;
			return componentManager;
		}

		// コンポーネントデータベースをシーンに追加
		void AddComponentDataBase(const std::string& sceneName);

		// コンポーネントの登録
		template<class T, class... Args>
		std::weak_ptr<T> AddComponent(const std::string& sceneName, const std::weak_ptr<GameObjectBase>& gameObject, Args&& ... args)
		{
			return m_ComponentList[sceneName]->AddComponent<T>(sceneName, gameObject, args...);
		}

		// コンポーネントの取得
		template<class T>
		std::weak_ptr<T> GetComponent(const std::string& sceneName, const UINT& gameObjectID)
		{
			return m_ComponentList[sceneName]->GetComponent<T>(gameObjectID);
		}

		// コンポーネントを削除
		template<class T>
		void RemoveComponent(const std::string& sceneName, const UINT& gameObjectID)
		{
			m_ComponentList[sceneName]->RemoveComponent<T>(gameObjectID);
		}

		// 保持しているコンポーネントを全部削除
		void RemoveAllComponent(const std::string& sceneName);

		// FixedUpdate関数を回す
		void FixedUpdate(const std::string& sceneName);
		// Update関数を回す
		void Update(const std::string& sceneName);
		// LateUpdate関数を回す
		void LateUpdate(const std::string& sceneName);
		// Draw関数を回す
		void Draw(
			const std::string& sceneName,
			const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command);

#if _DEBUG
		// Editor用の描画
		void OnGUI(std:: string& sceneName, SceneView* sceneView, EditorCommand* editorCommand);
#endif

	private:
		// コンポーネントのリスト(firstはオブジェクトID)
		std::map<std::string,		// GameObjectID
			std::shared_ptr<ComponentDataBase>> m_ComponentList;

		UINT m_ComponentID{};
	};
}