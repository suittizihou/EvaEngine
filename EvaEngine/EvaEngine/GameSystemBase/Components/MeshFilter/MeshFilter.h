#pragma once

#include "../../Base/Component/Component.h"
#include "../../DataBase/ModelDataBase/ModelDataBase.h"

namespace EvaEngine {
	class MeshFilter : public Component {
	public:
		MeshFilter(const int& modelHandle)
			:Component(0U, false),
			m_Model(EvaEngine::Internal::ModelDataBase::Instance().GetModel(modelHandle))
		{}

		~MeshFilter() = default;

#if _DEBUG
		void OnGUI(EvaEngine::Editor::Internal::SceneView* sceneView, EvaEngine::Editor::Internal::EditorCommand* editorCommand) override {}
#endif

		ModelData GetModel() { return m_Model; }

	private:
		ModelData m_Model{};
	};
}