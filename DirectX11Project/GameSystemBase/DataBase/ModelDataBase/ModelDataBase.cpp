#include "ModelDataBase.h"
#include "../../../Utility/ModelUtility/ModelLoaderUtility/VRMModelLoader/VRMModelLoader.h"

int ModelDataBase::AddModelData(const My3DLib::ModelData& model)
{
    m_Models[modelCount] = model;
    modelCount += 1;
    return modelCount - 1;
}

My3DLib::ModelData ModelDataBase::GetModel(const int modelHandle)
{
    //return LoadModelDataMemory(m_Models[modelHandle]);
    return m_Models[modelHandle];
}

void ModelDataBase::DeleteModel(const int modelHandle)
{
    m_Models.erase(modelHandle);
}

My3DLib::ModelData ModelDataBase::LoadModelDataMemory(const My3DLib::ModelData& model)
{
    VRMModelLoader m_VrmModelLoader;
    return m_VrmModelLoader.MakeModelDataMemory(model);
}
