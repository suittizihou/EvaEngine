#pragma once

#include <memory>

#include "../GameJobs/GameJobs.h"
#include "ComponentDesc.h"

#if _DEBUG
#include "../../../Editor/EditorCommand/EditorCommand.h"
#endif

namespace EvaEngine {

	class Transform;
	class Camera;

	// 使用する関数を示すビットフラグ
	namespace FunctionMask {
		const UINT NONE(0 << 0);
		//const UINT AWAKE				(1 << 0);
		//const UINT START				(1 << 1);
		const UINT FIXED_UPDATE(1 << 2);
		const UINT UPDATE(1 << 3);
		const UINT LATE_UPDATE(1 << 4);
		const UINT DRAW(1 << 5);
	}

	class Component : public GameJobs {
	public:
		Component(
			const UINT& functionMask,
			const bool canMultiAttach = true,
			const bool canRemove = true);
		virtual ~Component() = default;

	protected:
		virtual void Init() {}

	public:
		// Active状態じゃなくても呼ばれる
		virtual void Awake() {}
		// Active状態になったら呼ばれる
		virtual void Start() {}
		// 固定フレームで呼ばれる(作れるかは微妙)
		virtual void FixedUpdate() {}
		// 毎フレーム呼ばれる
		virtual void Update() {}
		// Updateの後に呼ばれる
		virtual void LateUpdate() {}
		// 上記全ての処理が終わったタイミングで呼ばれる
		virtual void Draw(const std::weak_ptr<Camera> camera, const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command) {}

#if _DEBUG
		// Editor用の描画
		virtual void OnGUI() {};
#endif

		// コンポーネントに必要なデータを設定
		void SetComponentDesc(const ComponentDesc& componentDesc);

		// このコンポーネントに紐づいているオブジェクトを返す
		std::weak_ptr<GameObject> GetGameObject() const;
		// トランスフォームを返す
		std::weak_ptr<Transform> GetTransform() const;
		// 複数アタッチできるコンポーネントか返す
		bool GetCanMultiAttach() const;
		// このコンポーネントは消せるか
		bool GetCanRemove() const;
		// コンポーネントのハッシュ値を返す(何型のコンポーネントか識別用)
		size_t GetHashCode() const;
		// コンポーネントのIDを返す(固有のID)
		UINT GetComponentID() const;
		// どの関数を呼び出すかのマスクを返す
		UINT GetFunctionMask() const;

	private:
		std::weak_ptr<GameObject> m_GameObject;
		std::weak_ptr<Transform> m_Transform;
		size_t m_HashCode{};
		UINT m_ComponentID{};
		UINT m_FunctionMask{};
		bool m_CanMultiAttach{ true };
		bool m_CanRemove{ true };
	};
}