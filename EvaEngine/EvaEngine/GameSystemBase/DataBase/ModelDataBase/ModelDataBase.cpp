#include "ModelDataBase.h"
#include "../../../Utility/GUIDUtility/GUIDUtility.h"
#include "../../../Utility/ModelUtility/ModelLoader/ModelLoader.h"
#include "../../../Utility/ModelUtility/ModelLoaderUtility/VRMModelLoader/VRMModelLoader.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

void ModelDataBase::LoadModelData(const std::shared_ptr<EvaEngine::ModelData>& model, GUID* guid)
{
    std::string name = model->GetFileName();
    if (GUIDUtility::Create(guid, "ModelDataBaseÇ…ÇƒÇÃGUIDê∂ê¨Ç…é∏îsÇµÇ‹ÇµÇΩÅB") == false) return;
    m_Models[*guid] = model;
}

void ModelDataBase::LoadModelData(const std::string& fileName, GUID* guid)
{
    LoadModelData(ModelLoader::Load(fileName), guid);
}

std::weak_ptr<ModelData> ModelDataBase::GetModel(const GUID& guid)
{
    //return LoadModelDataMemory(m_Models[modelHandle]);
    return m_Models[guid];
}

void ModelDataBase::DeleteModel(const GUID& guid)
{
    m_Models[guid]->Release();
    m_Models.erase(guid);
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