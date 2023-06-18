#pragma once

#include <guiddef.h>
#include "../../Base/Component/Component.h"
#include "../../Manager/ModelManager/ModelManager.h"

namespace EvaEngine {
	class MeshFilter : public Component {
	public:
		MeshFilter(const GUID& guid)
			:Component(0U, false),
			m_Model(ModelManager::Instance().GetModel(guid))
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