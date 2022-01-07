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

	namespace Internal {
		class ComponentDataBase;
	}

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
		friend Internal::ComponentDataBase;

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
		virtual void Draw(const std::weak_ptr<Camera>& camera, ID3D11DeviceContext* command) {}

#if _DEBUG
		// Editor用の描画
		virtual void OnGUI() {};
		// 閉じている時呼ばれる処理
		virtual void OnClosedGUI() {}
#endif

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
		const GUID& GetComponentID() const;
		// 文字列でIDを返す
		std::string GetComponentIDString();
		// どの関数を呼び出すかのマスクを返す
		UINT GetFunctionMask() const;
		// 自身が登録されている配列番号を返す
		UINT GetIndex() const;
		// コンポーネントの名前を返す
		std::string GetComponentName() const;

	private:
		// コンポーネントに必要なデータを設定
		void SetComponentDesc(const ComponentDesc& componentDesc);
		// コンポーネントが登録されている配列番号を設定
		void SetIndex(const UINT index);

	private:
		std::weak_ptr<GameObject> m_GameObject;
		std::weak_ptr<Transform> m_Transform;
		size_t m_HashCode{};
		GUID m_GUID{};
		UINT m_FunctionMask{};
		UINT m_Index{}; // ComponentDataBaseに登録されている自身の配列番号
		bool m_CanMultiAttach{ true };
		bool m_CanRemove{ true };
		std::string m_ComponentName{ "None" };
	};
}