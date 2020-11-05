#include "ModelLoader.h"
#include "../../../StringAssist/StringAssist.h"
#include "../../../../GameSystemBase/DataBase/ModelDataBase/ModelDataBase.h"

int ModelLoader::Load(const std::string& fileName)
{
    std::vector<std::string> fileSplit = StringAssist::split(fileName, '.');

    if (fileSplit.size() == 0) std::runtime_error("拡張子付きで入力してください");

    std::string modelType = fileSplit[fileSplit.size() - 1];

    My3DLib::ModelData::Model model;
    
    if (modelType == "fbx") {
        FBXModelLoader m_FbxModelLoader{};
        model = m_FbxModelLoader.LoadFbxFile(fileName.c_str());
    }
    else if (modelType == "vrm") {
        VRMModelLoader m_VrmModelLoader{};
        model = m_VrmModelLoader.LoadModel(fileName.c_str());
    }

    return ModelDataBase::Instance().AddModelData(model);
}