#include "ModelDataBase.h"
#include "../../../Utility/ModelUtility/ModelLoaderUtility/VRMModelLoader/VRMModelLoader.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

EvaEngine::Internal::ModelDataBase::~ModelDataBase()
{
}

int ModelDataBase::AddModelData(const ModelData& model)
{
    m_Models[modelCount] = model;
    modelCount += 1;
    return modelCount - 1;
}

ModelData ModelDataBase::GetModel(const int modelHandle)
{
    //return LoadModelDataMemory(m_Models[modelHandle]);
    return m_Models[modelHandle];
}

void ModelDataBase::DeleteModel(const int modelHandle)
{
    m_Models[modelHandle].Release();
    m_Models.erase(modelHandle);
}

void EvaEngine::Internal::ModelDataBase::AllDeleteModel()
{
    for (auto& model : m_Models) {
        model.second.Release();
    }
    m_Models.clear();
}

ModelData ModelDataBase::LoadModelDataMemory(const ModelData& model)
{
    VRMModelLoader m_VrmModelLoader;
    return m_VrmModelLoader.MakeModelDataMemory(model);
}
