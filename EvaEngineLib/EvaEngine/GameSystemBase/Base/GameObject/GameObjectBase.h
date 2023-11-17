#pragma once

#include <memory>
#include "../GameJobs/GameJobs.h"

namespace EvaEngine {

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

		// ObjectIDを返す
		virtual UINT GetObjectID() const = 0;
		// 名前を返す
		virtual std::string GetName() const = 0;
		// タグを返す
		virtual std::string GetTag() const = 0;
	};
}