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

		// 初期化処理
		virtual void Initialize() = 0;

		// 自身のweak_ptrを返す
		std::weak_ptr<GameObjectBase> GetGameObject() { return shared_from_this(); }
		// 所持している全コンポーネントを返す
		virtual std::vector<std::weak_ptr<Component>> GetAllComponents() = 0;

		// ObjectIDを返す
		virtual const GUID& GetObjectID() const = 0;
		// 名前を返す
		virtual std::string GetName() const = 0;
		// タグを返す
		virtual std::string GetTag() const = 0;
	};
}