#pragma once

#include <wrl/client.h>
#include <functional>
#include <list>
#include <d3d11.h>
#include <memory>
#include <bitset>

#pragma comment(lib,"d3d12.lib")

namespace EvaEngine {

	class GameObject;

	class GameJobs {
	public:
		GameJobs() {};
		virtual ~GameJobs() = default;

		// ゲームオブジェクトの追加
		std::weak_ptr<GameObject> AddGameObject();

		// 所属するシーンを設定
		void SetSceneName(const std::string& sceneType);
		// 所属するシーンを返す
		std::string GetSceneType();

	private:
		std::string m_SceneName{};

	private:
		GameJobs(const GameJobs&);
		void operator=(const GameJobs& obj);
	};
}