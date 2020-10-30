#include "ModelDataBase.h"
#include "../ModelLoaderUtility/VRMModelLoader/VRMModelLoader.h"

int ModelDataBase::AddModelData(const ModelData::Model& model)
{
    m_Model[modelCount] = model;
    modelCount += 1;
    return modelCount - 1;
}

ModelData::Model ModelDataBase::GetModel(const int& modelHandle)
{
    return LoadModelDataMemory(m_Model[modelHandle]);
}

void ModelDataBase::DeleteModel(const int& modelHandle)
{
    m_Model.erase(modelHandle);
}

ModelData::Model ModelDataBase::LoadModelDataMemory(const ModelData::Model& model)
{
    VRMModelLoader m_VrmModelLoader;
    return m_VrmModelLoader.MakeModelDataMemory(model);
}
