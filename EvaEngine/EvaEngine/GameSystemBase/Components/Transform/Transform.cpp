#include "Transform.h"
#include "../../../Utility/Math/Mathf/Mathf.h"

using namespace EvaEngine;

Transform::~Transform()
{
	// 子オブジェクトを切り離す
	detach_children();
	// 親オブジェクトから切り離す
	detach_parent();
}

Vector3 Transform::forward() const
{
	return rotation_ * Vector3::forward();
}

void Transform::forward(const Vector3& value)
{
	rotation(Quaternion::look_rotation(value));
}

Vector3 Transform::back() const
{
	return rotation_ * Vector3::back();
}

Vector3 Transform::right() const
{
	return rotation_ * Vector3::right();
}

void Transform::right(const Vector3& value)
{
	rotation(Quaternion::from_to_rotation(Vector3::right(), value));
}

Vector3 Transform::left() const
{
	return rotation_ * Vector3::left();
}

Vector3 Transform::up() const
{
	return rotation_ * Vector3::up();
}

void Transform::up(const Vector3& value)
{
	rotation(Quaternion::from_to_rotation(Vector3::up(), value));
}

Vector3 Transform::down() const
{
	return rotation_ * Vector3::down();
}

Vector3 Transform::lossy_scale() const
{
	return scale_;
}

Vector3 Transform::position() const
{
	return position_;
}

void Transform::position(const Vector3& value)
{
	if (!parent_.expired()) {
		local_position(parent_.lock()->inverse_transform_point(value));
	}
	else {
		local_position(value);
	}
}

void Transform::move(const Vector3& velocity)
{
	position(position_ + velocity);
}

void Transform::local_move(const Vector3& velocity)
{
	local_position(local_position_ + velocity);
}

Quaternion Transform::rotation() const
{
	return rotation_;
}

void Transform::rotation(const Quaternion& value)
{
	if (!parent_.expired()) {
		local_rotation(Quaternion::inverse(parent_.lock()->rotation()) * value);
	}
	else {
		local_rotation(value);
	}
}

Vector3 Transform::euler_angles() const
{
	return rotation_.euler_angles();
}

void Transform::euler_angles(const Vector3& value)
{
	rotation(Quaternion::euler(value));
}

void Transform::look_at(const Transform& target, const Vector3& world_up)
{
	look_at(target.position(), world_up);
}

void Transform::look_at(const Vector3& target, const Vector3& world_up)
{
	rotation(Quaternion::look_rotation(target - position_, world_up));
}

void Transform::rotate(const Vector3& eulers, Space relative_to)
{
	rotate(eulers.x, eulers.y, eulers.z, relative_to);
}

void Transform::rotate(float x, float y, float z, Space relative_to)
{
	Quaternion euler_rot = Quaternion::euler(x, y, z);
	if (relative_to == Space::Self) {
		local_rotation(local_rotation_ * euler_rot);
	}
	else {
		rotation(euler_rot * rotation_);
	}
}

void Transform::rotate(const Vector3& axis, float angle, Space relative_to)
{
	if (relative_to == Space::Self) {
		local_rotation(local_rotation_ * Quaternion::angle_axis(angle, axis));
	}
	else {
		rotation(Quaternion::angle_axis(angle, axis) * rotation_);
	}
}

void Transform::rotate_around(const Vector3& point, const Vector3& axis, float angle)
{
	Quaternion q = Quaternion::angle_axis(angle, axis);
	position(point + q * (position_ - point));
	rotation(q * rotation_);
}

void Transform::translate(const Vector3& translation, Space relative_to)
{
	if (relative_to == Space::World) {
		position(position_ + transform_direction(translation));
	}
	else {
		position(position_ + translation);
	}
}

Matrix4x4 Transform::local_to_world_matrix() const
{
	return Matrix4x4::TRS(position_, rotation_, scale_);
}

Matrix4x4 Transform::world_to_local_matrix() const
{
	return local_to_world_matrix().inverse();
}

Vector3 Transform::transform_point(const Vector3& position) const
{
	// 計算順番
	// 拡大縮小 -> 回転 -> 平行移動
	return rotation_ * Vector3::scale(position, scale_) + position_;
}

Vector3 Transform::transform_vector(const Vector3& vector) const
{
	return rotation_ * Vector3::scale(vector, scale_);
}

Vector3 Transform::transform_direction(const Vector3& direction) const
{
	return rotation_ * direction;
}

Vector3 Transform::inverse_transform_point(const Vector3& position) const
{
	Vector3 result = position;
	result -= position_;
	result = Quaternion::inverse(rotation_) * result;
	result.x /= scale_.x;
	result.y /= scale_.y;
	result.z /= scale_.z;
	return result;
}

Vector3 Transform::inverse_transform_vector(const Vector3& vector) const
{
	Vector3 result = vector;
	result = Quaternion::inverse(rotation_) * result;
	result.x /= scale_.x;
	result.y /= scale_.y;
	result.z /= scale_.z;
	return result;

}

Vector3 Transform::inverse_transform_direction(const Vector3& direction) const
{
	return Quaternion::inverse(rotation_) * direction;
}

std::weak_ptr<Transform> Transform::parent() const
{
	return parent_;
}

void Transform::parent(std::weak_ptr<Transform> parent)
{
	set_parent(parent, true);
}

void Transform::set_parent(std::weak_ptr<Transform> parent, bool world_position_stays)
{
	// 現在の親から切り離す
	detach_parent();
	// 新しい親を設定
	parent_ = parent;
	if (!parent_.expired()) {
		if (world_position_stays) {
			// 現在のワールド空間を保つか？
			local_rotation_ = Quaternion::inverse(parent_.lock()->rotation()) * rotation_;
			local_position_ = parent_.lock()->inverse_transform_point(position_);
		}
		else {
			// 現在のローカル空間を更新せずにワールド空間を更新
			update_world_transform(parent_.lock().get());
		}
		// 自分自身を親の子に登録
		parent.lock()->children_.push_back(this);
	}
	else {
		// 親がいなければ、ローカル空間はワールド空間と同じ
		local_rotation_ = rotation_;
		local_position_ = position_;
		local_scale_ = scale_;
	}

}

Vector3 Transform::local_scale() const
{
	return local_scale_;
}

void Transform::local_scale(const Vector3& value)
{
	local_scale_ = value;
	// ワールド空間を更新
	update_world_transform(parent_.lock().get());
}

Vector3 Transform::local_position() const
{
	return local_position_;
}

void Transform::local_position(const Vector3& value)
{
	local_position_ = value;
	// ワールド空間を更新
	update_world_transform(parent_.lock().get());
}

Quaternion Transform::local_rotation() const
{
	return local_rotation_;
}

void Transform::local_rotation(const Quaternion& value)
{
	local_rotation_ = value;
	// ワールド空間を更新
	update_world_transform(parent_.lock().get());
}

Vector3 Transform::local_euler_angles() const
{
	return local_rotation_.euler_angles();
}

void Transform::local_euler_angles(const Vector3& value)
{
	local_rotation(Quaternion::euler(value));
}

void Transform::detach_children()
{
	// 自身の親を子の親に変更する
	for (auto child : children_) {
		child->parent(parent_);
	}
}

void Transform::detach_parent()
{
	if (!parent_.expired()) {
		// 親のリストから自身を削除
		parent_.lock()->children_.remove(this);
		parent_ = std::weak_ptr<Transform>();
	}
}

void Transform::update_world_transform(const Transform* parent)
{
	if (parent != nullptr) {
		// ワールド空間の更新
		position_ = parent->transform_point(local_position_);
		rotation_ = parent->rotation_ * local_rotation_;
		scale_ = Vector3::scale(parent->scale_, local_scale_);
	}
	else {
		// 親がいなければローカル座標とワールド座標は同じ
		position_ = local_position_;
		rotation_ = local_rotation_;
		scale_ = local_scale_;
	}
	// 子供のワールド座標を更新
	for (auto child : children_) {
		child->update_world_transform(this);
	}
}