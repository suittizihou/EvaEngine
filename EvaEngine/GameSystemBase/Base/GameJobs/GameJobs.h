#pragma once

#include <wrl/client.h>
#include <functional>
#include <list>
#include <d3d11.h>
#include <memory>
#include <bitset>

#pragma comment(lib,"d3d12.lib")

#include "../Scene/SceneType.h"

#ifdef EVAENGINE_EXPORTS
#define __declspec(dllexport)
#else
#define __declspec(dllimport)
#endif

class GameObject;

class GameJobs {
public:
	GameJobs() {};
	virtual ~GameJobs() = default;

	// ゲームオブジェクトの追加
	std::weak_ptr<GameObject> AddGameObject();

	// 所属するシーンを設定
	void SetSceneType(const SceneType& sceneType);
	// 所属するシーンを返す
	SceneType GetSceneType();

private:
	SceneType m_SceneType{};

private:
	GameJobs (const GameJobs&);
	void operator=(const GameJobs& obj);
};