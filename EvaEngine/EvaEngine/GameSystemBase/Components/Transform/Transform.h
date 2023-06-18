#pragma once

#include "../../../GameSystemBase/Base/Component/Component.h"
#include "../../../Utility/Math/Vector3/Vector3.h"
#include "../../../Utility/Math/Matrix4x4/Matrix4x4.h"
#include "../../../Utility/Math/Quaternion/Quaternion.h"
#include <memory>
#include <list>

namespace EvaEngine {
	// �g�����X�t�H�[���N���X
	class Transform : public Component, public std::enable_shared_from_this<Transform> {
	public:
		// ���W�n�̎w��
		enum class Space {
			Self,   // ���[�J�����W�n
			World   // ���[���h���W�n
		};

		// �R���X�g���N�^
		Transform() :
			Component(FunctionMask::NONE, false, false) {};

#if _DEBUG
		// Editor�p�̕`��֐�
		void OnGUI() override;
		void OnClosedGUI() override;
#endif
		// �f�X�g���N�^
		~Transform();
		// ���[���h��Ԃ� Transform �̐� �O���擾
		Vector3 forward() const;
		// ���[���h��Ԃ� Transform �̐� �O��ݒ�
		void forward(const Vector3& value);
		// ���[���h��Ԃ� Transform �̐� ����擾
		Vector3 back() const;
		// ���[���h��Ԃ� Transform �̐Ԏ� �E���擾
		Vector3 right() const;
		// ���[���h��Ԃ� Transform �̐Ԏ� �E��ݒ�
		void right(const Vector3& value);
		// ���[���h��Ԃ� Transform �̐Ԏ� �����擾
		Vector3 left() const;
		// ���[���h��Ԃ� Transform �̗Ύ� ����擾
		Vector3 up() const;
		// ���[���h��Ԃ� Transform �̗Ύ� ���ݒ�
		void up(const Vector3& value);
		// ���[���h��Ԃ� Transform �̗Ύ� �����擾
		Vector3 down() const;
		// �I�u�W�F�N�g�̃O���[�o���X�P�[�����擾
		Vector3 lossy_scale() const;
		// ���[���h��Ԃ� Transform �̈ʒu���擾
		Vector3 position() const;
		// ���[���h��Ԃ� Transform �̈ʒu��ݒ�
		void position(const Vector3& value);
		void position(float x, float y, float z);
		// ���[���h��Ԃł̈ړ�
		void move(const Vector3& velocity);
		void move(float x, float y, float z);
		// �e�� Transform �I�u�W�F�N�g����Velocity���ړ�
		void local_move(const Vector3& velocity);
		// Quaternion �Ƃ��ĕۑ�����郏�[���h��Ԃł� Transform �̉�]���擾
		Quaternion rotation() const;
		// Quaternion �Ƃ��ĕۑ�����郏�[���h��Ԃł� Transform �̉�]��ݒ�
		void rotation(const Quaternion& value);
		// �I�C���[�p�Ƃ��Ă̊p�x���擾
		Vector3 euler_angles() const;
		// �I�C���[�p�Ƃ��Ă̊p�x��ݒ�
		void euler_angles(const Vector3& value);
		void euler_angles(float x, float y, float z);

		// �Ώۂ� Transform ��ݒ肵�A���̕����ւƌ������܂�
		void look_at(const Transform& target, const Vector3& world_up = Vector3{ 0.0f, 1.0f, 0.0f });
		void look_at(const Vector3& target, const Vector3& world_up = Vector3{ 0.0f, 1.0f, 0.0f });
		// Z ����eulers.z �x��]�AX���� euler.x �x��]�AY����eulers.y �x��]���܂�(���Ԃ͐���������)
		void rotate(const Vector3& eulers, Space relative_to = Space::Self);
		void rotate(float x, float y, float z, Space relative_to = Space::Self);
		// axis ���̎���� angle �x�A��]���܂�
		void rotate(const Vector3& axis, float angle, Space relative_to = Space::Self);
		// ���[���h���W�� point �𒆐S�Ƃ�����(axis)�� angle �x��]�����܂�
		void rotate_around(const Vector3& point, const Vector3& axis, float angle);

		// translation �̕����Ƌ����Ɉړ����܂�
		void translate(const Vector3& translation, Space relative_to = Space::Self);

		// ���[�J�����W���烏�[���h���W�֕ϊ������s��
		Matrix4x4 local_to_world_matrix() const;
		// ���[���h���W���烍�[�J�����W�֕ϊ������s��
		Matrix4x4 world_to_local_matrix() const;

		// ���[�J����Ԃ��烏�[���h��Ԃ� position ��ϊ����܂��B(�X�P�[���E��]�E���s�ړ��j
		Vector3 transform_point(const Vector3& position) const;
		// ���[�J����Ԃ��烏�[���h��Ԃ� vector ��ϊ����܂��B(�X�P�[���E��]�j
		Vector3 transform_vector(const Vector3& vector) const;
		// ���[�J����Ԃ��烏�[���h��Ԃ� direction ��ϊ����܂�(��]�j
		Vector3 transform_direction(const Vector3& direction) const;

		// ���[���h��Ԃ��烍�[�J����Ԃ� position ��ϊ����܂�
		Vector3 inverse_transform_point(const Vector3& position) const;
		// ���[���h��Ԃ��烍�[�J����Ԃ� vector ��ϊ����܂�
		Vector3 inverse_transform_vector(const Vector3& vector) const;
		// ���[���h��Ԃ��烍�[�J����Ԃ� direction ��ϊ����܂�
		Vector3 inverse_transform_direction(const Vector3& direction) const;

		// Transform �̐e���擾
		std::weak_ptr<Transform> parent() const;
		// Transform �̐e��ݒ�
		void parent(std::weak_ptr<Transform> parent);
		// Transform �̐e��ݒ�
		void set_parent(std::weak_ptr<Transform> parent, bool world_position_stays = true);
		// �q���B���擾
		std::list<std::weak_ptr<Transform>> get_children() const;
		// �q�����擾
		std::weak_ptr<Transform> get_child(const UINT index) const;
		// �q���̐����擾
		int get_child_count() const;

		// �e�� Transform �I�u�W�F�N�g���猩�����ΓI�ȃX�P�[�����擾
		Vector3 local_scale() const;
		// �e�� Transform �I�u�W�F�N�g���猩�����ΓI�ȃX�P�[����ݒ�
		void local_scale(const Vector3& value);
		void local_scale(float x, float y, float z);
		// �e�� Transform �I�u�W�F�N�g���猩�����ΓI�Ȉʒu���擾
		Vector3 local_position() const;
		// �e�� Transform �I�u�W�F�N�g���猩�����ΓI�Ȉʒu��ݒ�
		void local_position(const Vector3& value);
		void local_position(float x, float y, float z);
		// �e�� Transform �I�u�W�F�N�g���猩�����ΓI�ȉ�]���擾
		Quaternion local_rotation() const;
		// �e�� Transform �I�u�W�F�N�g���猩�����ΓI�ȉ�]��ݒ�
		void local_rotation(const Quaternion& value);
		void local_rotation(float x, float y, float z, float w);
		// �e�� Transform �I�u�W�F�N�g���猩�����ΓI�ȃI�C���[�p�Ƃ��Ẳ�]�l���擾
		Vector3 local_euler_angles() const;
		// �e�� Transform �I�u�W�F�N�g���猩�����ΓI�ȃI�C���[�p�Ƃ��Ẳ�]�l��ݒ�
		void local_euler_angles(const Vector3& value);
		void local_euler_angles(float x, float y, float z);
		// ���ׂĂ̎q�I�u�W�F�N�g��e�I�u�W�F�N�g����؂藣���܂�
		void detach_children();
		// �e�� Transform ����؂藣��
		void detach_parent();

	private:
		void internal_position(const Vector3& value);
		void internal_position(float x, float y, float z);
		void internal_local_position(const Vector3& value);
		void internal_local_position(float x, float y, float z);

		void internal_rotation(const Quaternion& value);
		void internal_rotation(float x, float y, float z, float w);
		void internal_local_rotation(const Quaternion& value);
		void internal_local_rotation(float x, float y, float z, float w);
		
		void internal_local_scale(const Vector3& value);
		void internal_local_scale(float x, float y, float z);

		// ���[���h���W�n�̍X�V
		void update_world_transform(const std::weak_ptr<Transform>& parent);

	private:
		// �|�W�V���� (���[���h���W�n)
		Vector3 position_{ 0.0f, 0.0f, 0.0f };
		// ��] (���[���h���W�n)
		Quaternion rotation_{ 0.0f, 0.0f, 0.0f, 1.0f };
		// �X�P�[�� (���[���h���W�n)
		Vector3 scale_{ 1.0f, 1.0f, 1.0f };

		// �|�W�V���� (���[�J�����W�n)
		Vector3 local_position_{ 0.0f, 0.0f, 0.0f };
		// ��] (���[�J�����W�n)
		Quaternion local_rotation_{ 0.0f, 0.0f, 0.0f, 1.0f };
		// �X�P�[�� (���[�J�����W�n)
		Vector3 local_scale_{ 1.0f, 1.0f, 1.0f };

		Vector3 internal_euler_rotation{ 0.0f, 0.0f, 0.0f };

		// �e�̃g�����X�t�H�[��
		std::weak_ptr<Transform> parent_;
		// �q�̃g�����X�t�H�[��
		std::list<std::weak_ptr<Transform>> children_;

		bool m_OpenedFlag{ false };
	};
}