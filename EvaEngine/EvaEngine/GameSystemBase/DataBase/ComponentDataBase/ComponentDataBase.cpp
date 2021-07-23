#include "ComponentDataBase.h"
#include "../../Base/GameObject/GameObject.h"
#include "../../Components/Camera/Camera.h"
#include <iterator>

using namespace EvaEngine::Internal;

void ComponentDataBase::FixedUpdate()
{
	for (int i = 0; i < m_FixedUpdateFuncNumber.size(); ++i) {
		m_Components[m_FixedUpdateFuncNumber[i]]->FixedUpdate();
	}
}

void ComponentDataBase::Update()
{
	for (int i = 0; i < m_UpdateFuncNumber.size(); ++i) {
		m_Components[m_UpdateFuncNumber[i]]->Update();
	}
}

void ComponentDataBase::LateUpdate()
{
	for (int i = 0; i < m_LateUpdateFuncNumber.size(); ++i) {
		m_Components[m_LateUpdateFuncNumber[i]]->LateUpdate();
	}
}

void ComponentDataBase::Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command) const
{
	// �J�����̐������`�悷��
	//std::vector<std::weak_ptr<Camera>> cameras = Camera::GetAllCamera();
	//for (int cameraNum = 0; cameraNum < cameras.size(); ++cameraNum) {
		for (int i = 0; i < m_DrawFuncNumber.size(); ++i) {
			// ���O�̃����_�[�^�[�Q�b�g�r���[�ɐ؂�ւ�
			//command->OMSetRenderTargets(1, &mpRTV, pDSV);
			//command->ClearRenderTargetView(mpRTV, clearColor);
			//command->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);

			m_Components[m_DrawFuncNumber[i]]->Draw(Camera::GetMainCamera(), command);
		}
	//}
}

#if _DEBUG
void ComponentDataBase::OnGUI()
{
	for (const auto& component : m_Components) {
		component->OnGUI();
	}
}
#endif

void ComponentDataBase::AddComponent(const std::shared_ptr<Component>& component, const int indexNum) {
	// FixedUpdate�֐��̓o�^
	if (component->GetFunctionMask() & FunctionMask::FIXED_UPDATE) {
		m_FixedUpdateFuncNumber.push_back(indexNum);
	}
	// Update�֐��̓o�^
	if (component->GetFunctionMask() & FunctionMask::UPDATE) {
		m_UpdateFuncNumber.push_back(indexNum);
	}
	// LateUpdate�֐��̓o�^
	if (component->GetFunctionMask() & FunctionMask::LATE_UPDATE) {
		m_LateUpdateFuncNumber.push_back(indexNum);
	}
	// Draw�֐��̓o�^
	if (component->GetFunctionMask() & FunctionMask::DRAW) {
		m_DrawFuncNumber.push_back(indexNum);
	}
	// �R���|�[�l���g�̓o�^
	m_Components.push_back(component);
}

void ComponentDataBase::RemoveComponent(const int index, const UINT mask)
{
	// �����̃R���|�[�l���g���g�p���Ă���֐��}�X�N���擾
	UINT endElementMask = m_Components.back()->GetFunctionMask();

	// �����ꏊ�Ɩ������N�����Ɠ���ւ�
	std::iter_swap(m_Components.begin() + index, m_Components.end() - 1);
	// �������폜
	m_Components.pop_back();

	// �폜�O�̃R���|�[�l���g���������z��ԍ����e�֐��Y���z��̖����ɓ����
	// (���̍폜�O�̓Y���̏ꏊ(m_Components�z��̏ꏊ)�ɂ͍폜���Ȃ��R���|�[�l���g�̓Y���������Ă���)
	if (endElementMask & FunctionMask::FIXED_UPDATE) m_FixedUpdateFuncNumber[m_FixedUpdateFuncNumber.size() - 1] = index;
	if (endElementMask & FunctionMask::UPDATE) m_UpdateFuncNumber[m_UpdateFuncNumber.size() - 1] = index;
	if (endElementMask & FunctionMask::LATE_UPDATE) m_LateUpdateFuncNumber[m_LateUpdateFuncNumber.size() - 1] = index;
	if (endElementMask & FunctionMask::DRAW) m_DrawFuncNumber[m_DrawFuncNumber.size() - 1] = index;

	if (mask & FunctionMask::FIXED_UPDATE)
	{
		// �����̒l���w��̏ꏊ�ɃR�s�[
		m_FixedUpdateFuncNumber[FindItr(m_FixedUpdateFuncNumber, index)] = m_FixedUpdateFuncNumber.back();
		// ����������
		m_FixedUpdateFuncNumber.pop_back();
	}

	if (mask & FunctionMask::UPDATE)
	{
		// �����̒l���w��̏ꏊ�ɃR�s�[
		m_UpdateFuncNumber[FindItr(m_UpdateFuncNumber, index)] = m_UpdateFuncNumber.back();
		// ����������
		m_UpdateFuncNumber.pop_back();
	}

	if (mask & FunctionMask::LATE_UPDATE)
	{
		// �����̒l���w��̏ꏊ�ɃR�s�[
		m_LateUpdateFuncNumber[FindItr(m_LateUpdateFuncNumber, index)] = m_LateUpdateFuncNumber.back();
		// ����������
		m_LateUpdateFuncNumber.pop_back();
	}

	if (mask & FunctionMask::DRAW)
	{
		// �����̒l���w��̏ꏊ�ɃR�s�[
		m_DrawFuncNumber[FindItr(m_DrawFuncNumber, index)] = m_DrawFuncNumber.back();
		// ����������
		m_DrawFuncNumber.pop_back();
	}
}

__int64 ComponentDataBase::FindItr(const std::vector<int>& vec, int value)
{
	return std::distance(vec.begin(), std::find(vec.begin(), vec.end(), value));
}

bool ComponentDataBase::IsGameObjectIDEquals(const std::weak_ptr<GameObject>& obj, const UINT& id)
{
	return obj.lock()->GetObjectID() == id;
}

bool ComponentDataBase::IsGameObjectIDEquals(const std::weak_ptr<GameObject>& obj1, const std::weak_ptr<GameObjectBase>& obj2)
{
	return obj1.lock()->GetObjectID() == obj2.lock()->GetObjectID();
}

void ComponentDataBase::RemoveAllComponent()
{
	m_FixedUpdateFuncNumber.clear();
	m_UpdateFuncNumber.clear();
	m_LateUpdateFuncNumber.clear();
	m_DrawFuncNumber.clear();
	m_Components.clear();
	m_ComponentID = 0;
}
