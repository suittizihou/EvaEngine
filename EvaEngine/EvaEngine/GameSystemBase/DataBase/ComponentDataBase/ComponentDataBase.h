#pragma once

#include <string>
#include <list>
#include <queue>
#include <map>
#include <memory>
#include <stdexcept>
#include "../../../Utility/GUIDUtility/GUIDUtility.h"
#include "../../Base/Component/Component.h"
#include "../../../System/DebugLog/DebugLog.h"
#include "../../../Utility/TypeIDAssist/TypeIDAssist.h"
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "dxgi.lib")

namespace EvaEngine {
	namespace Internal {
		class ComponentDataBase {
		public:
			ComponentDataBase() = default;
			~ComponentDataBase() = default;

			// コンポーネントの登録
			template<class T, class... Args>
			std::weak_ptr<T> AddComponent(const std::u8string& sceneName, const std::weak_ptr<GameObjectBase>& gameObject, Args&& ... args)
			{
				ComponentDesc componentDesc{};
				componentDesc.componentName = TypeIDAssist<T>::GetClassName();
				componentDesc.sceneName = sceneName;
				componentDesc.gameObject = gameObject;
				componentDesc.hashCode = typeid(T).hash_code();

				if (GUIDUtility::Create(&componentDesc.guid, StringAssist::to_u8string("ComponentDataBase  " + componentDesc.componentName + " failed to generate guid.")) == false)
				{
					return std::weak_ptr<T>();
				}

				std::shared_ptr<T> component_temp = std::make_shared<T>(args...);
				component_temp->SetComponentDesc(componentDesc);

				// 複数アタッチできないコンポーネントの場合
				if (!component_temp->GetCanMultiAttach()) {
					// 同じコンポーネントが無いかチェック
					for (const auto& component : gameObject.lock()->GetAllComponents()) {
						if (component.lock()->GetHashCode() != component_temp->GetHashCode()) continue;

						DebugLog::LogError(StringAssist::to_u8string("Can't multi attach." + (std::string)typeid(T).name() + " : This component cannot be attached multiple times."));
						return std::weak_ptr<T>();
					}
				}

				// コンポーネントを追加(関数なども登録)
				AddComponent(component_temp, m_Components.size());

				// コンポーネントの初期関数を呼ぶ
				component_temp->Awake();
				component_temp->Start();


				// 参照を返す
				return component_temp;
			}

			// コンポーネントの取得
			template<class T>
			std::weak_ptr<T> GetComponent(const std::weak_ptr<GameObjectBase>& gameObject)
			{
				size_t hashCode = typeid(T).hash_code();

				for (const auto& component : gameObject.lock()->GetAllComponents()) {
					// 指定したコンポーネントとハッシュ値が違う場合はコンティニュー
					if (hashCode != component.lock()->GetHashCode()) continue;
					// dynamic_castを使用していないのは型変換チェックによる速度低下を防ぐため
					return std::static_pointer_cast<T>(component.lock());
				}

				DebugLog::LogError(
					StringAssist::to_u8string(
					"Not found. : Name : " +
					(std::string)typeid(T).name() +
					" : " +
					std::to_string(typeid(T).hash_code()) +
					" : Component not found."));
				return std::weak_ptr<T>();
			}

			// コンポーネントの取得
			template<class T>
			std::weak_ptr<T> GetComponent(const GUID& gameObjectID)
			{
				size_t hashCode = typeid(T).hash_code();

				// コンポーネント検索
				for (int i = 0; i < m_Components.size(); ++i) {
					// ゲームオブジェクトIDが違う場合はスキップ
					if (!IsGameObjectIDEquals(m_Components[i]->GetGameObject(), gameObjectID)) continue;

					// 指定したコンポーネントとハッシュ値が違う場合はコンティニュー
					if (hashCode != m_Components[i]->GetHashCode()) continue;
					// dynamic_castを使用していないのは型変換チェックによる速度低下を防ぐため
					return std::static_pointer_cast<T>(m_Components[i]);
				}

				DebugLog::LogError(
					StringAssist::to_u8string(
					"Not found. : Name : " +
					(std::string)typeid(T).name() +
					" : " +
					std::to_string(typeid(T).hash_code()) +
					" : Component not found."));
				return std::weak_ptr<T>();
			}

			// コンポーネントを削除
			template<class T>
			void RemoveComponent(const std::weak_ptr<GameObjectBase>& gameObject)
			{
				size_t hashCode = typeid(T).hash_code();

				for (const auto& component : gameObject.lock()->GetAllComponents()) {
					if (hashCode != component.lock()->GetHashCode()) continue;

					// 消せないコンポーネントなら早期リターン
					if (!component.lock()->GetCanRemove()) {
						DebugLog::LogError(
							StringAssist::to_u8string(
							"Can't remove component : " +
							(std::string)typeid(T).name() +
							" : " +
							std::to_string(typeid(T).hash_code()) +
							" : This component cannot be removed."));
						return;
					}

					// 実際に消す
					RemoveComponent(component);
					return;
				}

				DebugLog::LogError(
					StringAssist::to_u8string(
					"Not found.: Name : " +
					(std::string)typeid(T).name() +
					" : " +
					std::to_string(typeid(T).hash_code()) +
					" : Component not found."));
			}

			//// コンポーネントを削除
			//template<class T>
			//void RemoveComponent(const GUID& gameObjectID)
			//{
			//	size_t hashCode = typeid(T).hash_code();
			//	for (int i = 0; i < m_Components.size(); ++i) {
			//		if (!IsGameObjectIDEquals(m_Components[i]->GetGameObject(), gameObjectID)) continue;
			//		if (hashCode != m_Components[i]->GetHashCode()) continue;

			//		// 消せないコンポーネントなら早期リターン
			//		if (!m_Components[i]->GetCanRemove()) {
			//			DebugLog::LogError(
			//				u8"Can't remove component : " +
			//				(std::string)typeid(T).name() +
			//				" : " +
			//				std::to_string(typeid(T).hash_code()) +
			//				" : This component cannot be removed.");
			//			return;
			//		}


			//		// 消す対象の要素番号とFunctionMaskを渡して消す
			//		RemoveComponent(i, m_Components[i]->GetFunctionMask());
			//	}

			//	DebugLog::LogError(
			//		u8"Not found.: Name : " +
			//		(std::string)typeid(T).name() +
			//		" : " +
			//		std::to_string(typeid(T).hash_code()) +
			//		" : Component not found.");
			//}

			// 保持しているコンポーネントを全部削除
			void RemoveAllComponent();

			// FixedUpdate関数を回す
			void FixedUpdate();
			// Update関数を回す
			void Update();
			// Update関数を回す(Editor上でも動く)
			void ExecuteEditorUpdate();
			// LateUpdate関数を回す
			void LateUpdate();
			// Draw関数を回す
			void Draw(ID3D11DeviceContext* command) const;
#if _DEBUG
			// シーンビュー用描画関数
			void DrawSceneView(ID3D11DeviceContext* command) const;
			// ComponentのOnGUIを呼び出す用
			void OnGUI();
#endif

		private:
			// コンポーネントを追加
			void AddComponent(const std::shared_ptr<Component>& component, const int indexNum);

			// 消すコンポーネントを後ろに持ってったり消す数をカウントしたり
			void RemoveComponent(const std::weak_ptr<Component>& component);
			void RemoveComponent(const UINT& index, const UINT& mask);
			// 指定の数字に合った部分の要素番号を取得する
			__int64 FindItr(const std::vector<int>& vec, int value);

			// 指定されたゲームオブジェクトと指定されたIDが同じか確認する(ここにGameObjectのヘッダーを書くと循環参照が発生するためcppに逃がす)
			bool IsGameObjectIDEquals(const std::weak_ptr<GameObject>& obj, const GUID& id);
			bool IsGameObjectIDEquals(const std::weak_ptr<GameObject>& obj1, const std::weak_ptr<GameObjectBase>& obj2);

		private:
			// コンポーネントのデータ
			std::vector<std::shared_ptr<Component>> m_Components;

			// FixedUpdate関数が記入されているコンポーネントが格納されている印字の番号を格納する配列
			std::vector<int> m_FixedUpdateFuncNumber;

			// Update関数が記入されているコンポーネントが格納されている印字の番号を格納する配列
			std::vector<int> m_UpdateFuncNumber;

			// Editor上でも更新されるフラグが立っているUpdate関数が記述されたコンポーネントが格納されている印字の番号を格納する配列
			std::vector<int> m_ExecuteEditUpdateFuncNumber;

			// LateUpdate関数が記入されているコンポーネントが格納されている印字の番号を格納する配列
			std::vector<int> m_LateUpdateFuncNumber;

			// Draw関数が記入されているコンポーネントが格納されている印字の番号を格納する配列
			std::vector<int> m_DrawFuncNumber;
		};
	}
}