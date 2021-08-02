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

	// �g�p����֐��������r�b�g�t���O
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
		// Active��Ԃ���Ȃ��Ă��Ă΂��
		virtual void Awake() {}
		// Active��ԂɂȂ�����Ă΂��
		virtual void Start() {}
		// �Œ�t���[���ŌĂ΂��(���邩�͔���)
		virtual void FixedUpdate() {}
		// ���t���[���Ă΂��
		virtual void Update() {}
		// Update�̌�ɌĂ΂��
		virtual void LateUpdate() {}
		// ��L�S�Ă̏������I������^�C�~���O�ŌĂ΂��
		virtual void Draw(const std::weak_ptr<Camera> camera, const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command) {}

#if _DEBUG
		// Editor�p�̕`��
		virtual void OnGUI() {};
#endif

		// �R���|�[�l���g�ɕK�v�ȃf�[�^��ݒ�
		void SetComponentDesc(const ComponentDesc& componentDesc);

		// ���̃R���|�[�l���g�ɕR�Â��Ă���I�u�W�F�N�g��Ԃ�
		std::weak_ptr<GameObject> GetGameObject() const;
		// �g�����X�t�H�[����Ԃ�
		std::weak_ptr<Transform> GetTransform() const;
		// �����A�^�b�`�ł���R���|�[�l���g���Ԃ�
		bool GetCanMultiAttach() const;
		// ���̃R���|�[�l���g�͏����邩
		bool GetCanRemove() const;
		// �R���|�[�l���g�̃n�b�V���l��Ԃ�(���^�̃R���|�[�l���g�����ʗp)
		size_t GetHashCode() const;
		// �R���|�[�l���g��ID��Ԃ�(�ŗL��ID)
		UINT GetComponentID() const;
		// �ǂ̊֐����Ăяo�����̃}�X�N��Ԃ�
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