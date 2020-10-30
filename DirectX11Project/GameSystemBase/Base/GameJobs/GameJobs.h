#ifndef GAME_JOBS_H_
#define GAME_JOBS_H_

#include <wrl/client.h>
#include <functional>
#include <list>
#include <d3d11.h>
#include <memory>
#include <bitset>

#pragma comment(lib,"d3d12.lib")

#include "../Scene/SceneType.h"

class ModelApp;
class GameObject;

class GameJobs {
public:
	GameJobs(const SceneType& sceneType) :
	m_SceneType(sceneType)
	{};
	virtual ~GameJobs() = default;

	std::weak_ptr<GameObject> AddGameObject();

	// èäëÆÇ∑ÇÈÉVÅ[ÉìÇï‘Ç∑
	SceneType GetSceneType();

private:
	SceneType m_SceneType{};

private:
	GameJobs (const GameJobs&);
	void operator=(const GameJobs& obj);
};
#endif