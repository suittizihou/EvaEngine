#pragma once

#include <string>
#include <list>
#include <queue>
#include <map>
#include <memory>
#include <stdexcept>
#include "../../Base/Component/Component.h"

namespace EvaEngine {
	namespace Internal {
		class ComponentDataBase {
		public:
			ComponentDataBase() = default;
			~ComponentDataBase() = default;

			// コンポーネントの登録
			template<class T, class... Args>
			std::weak_ptr<T> AddComponent(const std::string& sceneName, const std::weak_ptr<GameObjectBase>& gameObject, Args&& ... args)
			{
				static_assert(std::is_base_of<Component, T>::value == true, "The argument does not inherit from Component.");

				ComponentDesc componentDesc{};
				componentDesc.sceneName = sceneName;
				componentDesc.gameObject = gameObject;
				componentDesc.hashCode = typeid(T).hash_code();
				componentDesc.componentID = m_ComponentID;
				std::shared_ptr<T> component_temp = std::make_shared<T>(args...);
				component_temp->SetComponentDesc(componentDesc);

				// 複数アタッチできないコンポーネントの場合
				if (!component_temp->GetCanMultiAttach()) {
					// 同じコンポーネントが無いかチェック
					for (int i = 0; i < m_Components.size(); ++i) {
						if (!IsGameObjectIDEquals(m_Components[i]->GetGameObject(), gameObject)) continue;
						if (componentDesc.hashCode != m_Components[i]->GetHashCode()) continue;

						throw std::runtime_error("Can't multi attach." + (std::string)typeid(T).name() + " : このコンポーネントは複数アタッチできません");
						return std::weak_ptr<T>();
					}
				}

				// コンポーネントを追加(関数なども登録)
				AddComponent(component_temp, m_Components.size());
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
				for (int i = 0; i < m_Components.size(); ++i) {
					if (!IsGameObjectIDEquals(m_Components[i]->GetGameObject(), gameObjectID)) continue;
					if (hashCode != m_Components[i]->GetHashCode()) continue;

					// 消せないコンポーネントなら早期リターン
					if (!m_Components[i]->GetCanRemove()) {
						throw std::runtime_error(
							"Can't remove component : " +
							(std::string)typeid(T).name() +
							" : " +
							std::to_string(typeid(T).hash_code()) +
							" : このコンポーネントは消せません");
						return;
					}

					// 消す対象の要素番号とFunctionMaskを渡して消す
					RemoveComponent(i, m_Components[i]->GetFunctionMask());
					return;

				}

				throw std::runtime_error(
					"Not found.: Name : " +
					(std::string)typeid(T).name() +
					" : " +
					std::to_string(typeid(T).hash_code()) +
					" : コンポーネントが見つかりませんでした");
			}

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
#if _DEBUG
			void OnGUI();
#endif

		private:
			// コンポーネントを追加
			void AddComponent(const std::shared_ptr<Component>& component, const int indexNum);

			// 消すコンポーネントを後ろに持ってったり消す数をカウントしたり
			void RemoveComponent(const int index, const UINT mask);
			// 指定の数字に合った部分の要素番号を取得する
			__int64 FindItr(const std::vector<int>& vec, int value);

			// 指定されたゲームオブジェクトと指定されたIDが同じか確認する(ここにGameObjectのヘッダーを書くと循環参照が発生するためcppに逃がす)
			bool IsGameObjectIDEquals(const std::weak_ptr<GameObject>& obj, const UINT& id);
			bool IsGameObjectIDEquals(const std::weak_ptr<GameObject>& obj1, const std::weak_ptr<GameObjectBase>& obj2);

		private:
			// コンポーネントのデータ
			std::vector<std::shared_ptr<Component>> m_Components;

			// FixedUpdate関数が記入されているコンポーネントが格納されている印字の番号を格納する配列
			std::vector<int> m_FixedUpdateFuncNumber;

			// Update関数が記入されているコンポーネントが格納されている印字の番号を格納する配列
			std::vector<int> m_UpdateFuncNumber;

			// LateUpdate関数が記入されているコンポーネントが格納されている印字の番号を格納する配列
			std::vector<int> m_LateUpdateFuncNumber;

			// Draw関数が記入されているコンポーネントが格納されている印字の番号を格納する配列
			std::vector<int> m_DrawFuncNumber;

			UINT m_ComponentID{};
		};
	}
}