#pragma once

#include "../../Base/Component/Component.h"
#include "../../DataBase/ModelDataBase/ModelDataBase.h"

class MeshFilter : public Component {
public:
	MeshFilter(const int& modelHandle)
		:Component(0U, false),
		m_Model(ModelDataBase::Instance().GetModel(modelHandle))
	{}
	
	~MeshFilter() = default;

	My3DLib::Model GetModel() { return m_Model; }

private:
	My3DLib::Model m_Model{};
};