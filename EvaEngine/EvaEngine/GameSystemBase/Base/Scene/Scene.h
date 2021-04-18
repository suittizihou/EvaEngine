#pragma once

#include "../../Manager/GameObjectManager/GameObjectManager.h"
#include "../../../GameSystemBase/Components/ComponentHeaders.h"

namespace EvaEngine {
	class Scene {
	public:
		Scene(const std::string& sceneName, const UINT sceneID) : 
			m_SceneName{ sceneName },
			m_SceneID{ sceneID }
		{};
		virtual ~Scene() = default;

	public:
		// シーンの初期化
		virtual void Initialize() = 0;

		// シーンのアップデート
		virtual void SceneUpdate() = 0;

		// 固定更新処理
		void FixedUpdate();

		// 更新処理
		void Update();

		// 遅延更新処理
		void LateUpdate();

		// 描画処理
		void Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command);

#if _DEBUG
		// Editor用の描画処理
		void OnGUI(const SceneView& sceneView);
#endif

		// 名前で検索
		std::weak_ptr<GameObject> Find(const std::string& name);
		// タグで検索してゲームオブジェクトを一つ持ってくる
		std::weak_ptr<GameObject> FindGameObjectWithTag(const std::string& tag);
		// タグで検索してヒットしたゲームオブジェクトを全部持ってくる
		std::vector<std::weak_ptr<GameObject>> FindGameObjectsWithTag(const std::string& tag);

		// シーン名の取得
		std::string GetSceneName() const;
		// シーンのIDを取得
		UINT GetSceneID() const;

		// ゲームオブジェクトの追加
		std::weak_ptr<GameObject> AddGameObject(const std::string& tag = "None", const std::string& name = "GameObject");

	protected:
		std::string m_SceneName{};
		UINT m_SceneID{};
	};
}