#pragma once

#include <functional>
#include <list>
#include <d3d11.h>
#include <memory>
#include <bitset>

#pragma comment(lib,"d3d11.lib")

namespace EvaEngine {

	class GameObject;

	class GameJobs {
	public:
		GameJobs() {};
		virtual ~GameJobs() = default;

		// ゲームオブジェクトの追加
		std::weak_ptr<GameObject> Instantiate(const std::string& tag = "None", const std::u8string& name = u8"GameObject");

		// 所属するシーン名を設定
		void SetSceneName(const std::u8string& sceneType);
		// 所属するシーン名を返す
		std::u8string GetSceneName();

	private:
		std::u8string m_SceneName{};

	private:
		GameJobs(const GameJobs&);
		void operator=(const GameJobs& obj);
	};
}