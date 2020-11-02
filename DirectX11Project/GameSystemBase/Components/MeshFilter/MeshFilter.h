#pragma once

#include "../../Base/Component/Component.h"
#include "../../DataBase/ModelDataBase/ModelDataBase.h"

class MeshFilter : public Component {
public:
	MeshFilter(const ComponentDesc& componentDesc, const int& modelHandle)
		:Component(componentDesc, 0U, false),
		m_Model(ModelDataBase::Instance().GetModel(modelHandle))
	{}
	
	~MeshFilter() = default;

	ModelData::Model GetModel() { return m_Model; }

private:
	ModelData::Model m_Model{};
};