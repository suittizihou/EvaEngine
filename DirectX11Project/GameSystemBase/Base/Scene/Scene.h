#ifndef SCENE_H_
#define SCENE_H_

#include "../../Manager/ComponentManager/ComponentManager.h"
#include "../../Manager/GameObjectManager/GameObjectManager.h"

#include "SceneType.h"

class Scene {
public:
	Scene(const SceneType& sceneType) : m_SceneType(sceneType) {};
	virtual ~Scene() = default;

public:
	virtual void Initialize() = 0;

	// XVˆ—
	virtual void Update() {
		ComponentManager::Instance().FixedUpdate(m_SceneType);
		ComponentManager::Instance().Update(m_SceneType);
		ComponentManager::Instance().LateUpdate(m_SceneType);
		ComponentManager::Instance().RunRemoveComponents(m_SceneType);
	};

	// •`‰æˆ—
	virtual void Draw() { };

	std::weak_ptr<GameObject> AddGameObject(const std::string& name = "GameObject", const std::string& tag = "None");

protected:
	SceneType m_SceneType{};
};

#endif