#pragma once

#include <vector>
#include <memory>
#include <guiddef.h>

#include "../GameJobs/GameJobs.h"

namespace EvaEngine {
	class Component;

	class GameObjectBase : public GameJobs, public std::enable_shared_from_this<GameObjectBase> {
	public:
		GameObjectBase(const std::string& sceneName) :
			GameJobs()
		{
			SetSceneName(sceneName);
		};
		virtual ~GameObjectBase() = default;

		// ����������
		virtual void Initialize() = 0;

		// ���g��weak_ptr��Ԃ�
		std::weak_ptr<GameObjectBase> GetGameObject() { return shared_from_this(); }
		// �������Ă���S�R���|�[�l���g��Ԃ�
		virtual std::vector<std::weak_ptr<Component>> GetAllComponents() = 0;

		// ObjectID��Ԃ�
		virtual const GUID& GetObjectID() const = 0;
		// ���O��Ԃ�
		virtual std::string GetName() const = 0;
		// �^�O��Ԃ�
		virtual std::string GetTag() const = 0;
	};
}