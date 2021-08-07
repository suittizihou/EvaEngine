#include "ModelDataBase.h"
#include "../../../Utility/ModelUtility/ModelLoader/ModelLoader.h"
#include "../../../Utility/ModelUtility/ModelLoaderUtility/VRMModelLoader/VRMModelLoader.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

int ModelDataBase::AddModelData(const std::shared_ptr<EvaEngine::ModelData>& model)
{
    m_Models[modelCount] = model;
    modelCount += 1;
    return modelCount - 1;
}

int ModelDataBase::AddModelData(const std::string& fileName)
{
    return AddModelData(ModelLoader::Load(fileName));
}

std::weak_ptr<ModelData> ModelDataBase::GetModel(const int modelHandle)
{
    //return LoadModelDataMemory(m_Models[modelHandle]);
    return m_Models[modelHandle];
}

void ModelDataBase::DeleteModel(const int modelHandle)
{
    m_Models[modelHandle]->Release();
    m_Models.erase(modelHandle);
}

void ModelDataBase::DeleteAllModel()
{
    for (auto& model : m_Models) {
        model.second->Release();
    }
    m_Models.clear();
}

//ModelData ModelDataBase::LoadModelDataMemory(const std::shared_ptr<EvaEngine::ModelData>& model)
//{
//    VRMModelLoader m_VrmModelLoader;
//    return m_VrmModelLoader.MakeModelDataMemory(model);
//}