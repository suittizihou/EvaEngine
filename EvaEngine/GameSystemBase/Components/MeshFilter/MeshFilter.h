#pragma once

#include "../../Base/Component/Component.h"
#include "../../DataBase/ModelDataBase/ModelDataBase.h"

EVAENGINE_API class MeshFilter : public Component {
public:
	MeshFilter(const int& modelHandle)
		:Component(0U, false),
		m_Model(ModelDataBase::Instance().GetModel(modelHandle))
	{}
	
	~MeshFilter() = default;

	My3DLib::ModelData GetModel() { return m_Model; }

private:
	My3DLib::ModelData m_Model{};
};