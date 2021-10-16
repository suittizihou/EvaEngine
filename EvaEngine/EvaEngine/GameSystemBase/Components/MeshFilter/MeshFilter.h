#pragma once

#include "../../Base/Component/Component.h"
#include "../../Manager/ModelManager/ModelManager.h"

namespace EvaEngine {
	class MeshFilter : public Component {
	public:
		MeshFilter(const int& modelHandle)
			:Component(0U, false),
			m_Model(ModelManager::Instance().GetModel(modelHandle))
		{}

		~MeshFilter() = default;

#if _DEBUG
		void OnGUI() override;
#endif

		std::weak_ptr<ModelData> GetModel() { return m_Model; }

	private:
		std::weak_ptr<ModelData> m_Model;
	};
}