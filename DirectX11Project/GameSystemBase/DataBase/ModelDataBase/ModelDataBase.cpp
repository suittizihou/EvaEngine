#include "ModelDataBase.h"
#include "../../../Utility/ModelUtility/ModelLoaderUtility/VRMModelLoader/VRMModelLoader.h"

int ModelDataBase::AddModelData(const My3DLib::ModelData::Model& model)
{
    m_Model[modelCount] = model;
    modelCount += 1;
    return modelCount - 1;
}

My3DLib::ModelData::Model ModelDataBase::GetModel(const int modelHandle)
{
    return LoadModelDataMemory(m_Model[modelHandle]);
}

void ModelDataBase::DeleteModel(const int modelHandle)
{
    m_Model.erase(modelHandle);
}

My3DLib::ModelData::Model ModelDataBase::LoadModelDataMemory(const My3DLib::ModelData::Model& model)
{
    VRMModelLoader m_VrmModelLoader;
    return m_VrmModelLoader.MakeModelDataMemory(model);
}
