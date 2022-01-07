#include "ComponentDataBase.h"
#include "../../Base/GameObject/GameObject.h"
#include "../../Components/Camera/Camera.h"
#include "../../Manager/DrawManager/DrawManager.h"
#include "../../../App/EditorApp/EditorApp.h"
#include "../../../Editor/SceneView/SceneView.h"
#include "../../../Editor/EditorApplication/EditorApplication.h"
#include <iterator>

using namespace EvaEngine::Internal;

void ComponentDataBase::FixedUpdate()
{
	for (int i = 0, size = m_FixedUpdateFuncNumber.size(); i < size; ++i) {
		if (m_Components[m_FixedUpdateFuncNumber[i]]->GetGameObject().lock()->ActiveSelf() == false) continue;

		m_Components[m_FixedUpdateFuncNumber[i]]->FixedUpdate();
	}
}

void ComponentDataBase::Update()
{
	for (int i = 0, size = m_UpdateFuncNumber.size(); i < size; ++i) {
		if (m_Components[m_UpdateFuncNumber[i]]->GetGameObject().lock()->ActiveSelf() == false) continue;

		m_Components[m_UpdateFuncNumber[i]]->Update();
	}
}

void ComponentDataBase::LateUpdate()
{
	for (int i = 0, size = m_LateUpdateFuncNumber.size(); i < size; ++i) {
		if (m_Components[m_LateUpdateFuncNumber[i]]->GetGameObject().lock()->ActiveSelf() == false) continue;

		m_Components[m_LateUpdateFuncNumber[i]]->LateUpdate();
	}
}

void ComponentDataBase::Draw(ID3D11DeviceContext* command) const
{
#if _DEBUG
	// �V�[���r���[�̕`��
	DrawSceneView(command);
#endif

	// �J�����̐������`�悷��
	auto cameras = Camera::GetAllCamera();
	for (int cameraNum = 0, size = cameras.size(); cameraNum < size; ++cameraNum) {
		if (cameras[cameraNum].lock()->GetGameObject().lock()->ActiveSelf() == false) continue;

		// �`��J�n����
		cameras[cameraNum].lock()->SetRenderTarget();
		// �`��J�n
		for (int i = 0, size = m_DrawFuncNumber.size(); i < size; ++i) {
			if (m_Components[m_DrawFuncNumber[i]]->GetGameObject().lock()->ActiveSelf() == false) continue;

			m_Components[m_DrawFuncNumber[i]]->Draw(cameras[cameraNum], command);
		}
	}
}

#if _DEBUG
void EvaEngine::Internal::ComponentDataBase::DrawSceneView(ID3D11DeviceContext* command) const
{
	auto sceneViewCamera = EvaEngine::Editor::Internal::EditorApp::GetSceneView().lock()->GetSceneCamera();
	sceneViewCamera.lock()->SetRenderTarget();
	for (int i = 0, size = m_DrawFuncNumber.size(); i < size; ++i) {
		m_Components[m_DrawFuncNumber[i]]->Draw(sceneViewCamera, command);
	}
}

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
	// ���g���o�^����Ă���R���|�[�l���g�̔z��ԍ���ݒ�
	component->SetIndex(indexNum);
	// �R���|�[�l���g�̓o�^
	m_Components.push_back(component);
}

void ComponentDataBase::RemoveComponent(const std::weak_ptr<Component>& component)
{
	UINT index = component.lock()->GetIndex();
	UINT mask = component.lock()->GetFunctionMask();

	// �����̃R���|�[�l���g���g�p���Ă���֐��}�X�N���擾
	UINT endElementMask = m_Components.back()->GetFunctionMask();

	// �����ꏊ�Ɩ������N�����Ɠ���ւ�
	std::iter_swap(m_Components.begin() + index, m_Components.end() - 1);
	// �������폜
	m_Components.pop_back();
	
	// ���݂̔z��ԍ���ݒ�
	m_Components[index]->SetIndex(index);

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

void ComponentDataBase::RemoveComponent(const UINT& index, const UINT& mask)
{
	// �����̃R���|�[�l���g���g�p���Ă���֐��}�X�N���擾
	UINT endElementMask = m_Components.back()->GetFunctionMask();

	// �����ꏊ�Ɩ������N�����Ɠ���ւ�
	std::iter_swap(m_Components.begin() + index, m_Components.end() - 1);
	// �������폜
	m_Components.pop_back();
	
	// ���݂̔z��ԍ���ݒ�
	m_Components[index]->SetIndex(index);

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

bool ComponentDataBase::IsGameObjectIDEquals(const std::weak_ptr<GameObject>& obj, const GUID& id)
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
}
