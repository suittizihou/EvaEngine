#include "ModelLoader.h"
#include "../../../StringAssist/StringAssist.h"
#include "../../../../GameSystemBase/DataBase/ModelDataBase/ModelDataBase.h"

int ModelLoader::Load(const std::string& fileName)
{
    std::vector<std::string> fileSplit = StringAssist::split(fileName, '.');

    if (fileSplit.size() == 0) std::runtime_error("Šg’£Žq•t‚«‚Å“ü—Í‚µ‚Ä‚­‚¾‚³‚¢");

    std::string modelType = fileSplit[fileSplit.size() - 1];

    My3DLib::Model model{};
    
    if (modelType == "fbx") {
        FBXModelLoader m_FbxModelLoader{};
        model = m_FbxModelLoader.LoadModel(fileName.c_str());
    }
    else if (modelType == "vrm") {
        VRMModelLoader m_VrmModelLoader{};
        model = m_VrmModelLoader.LoadModel(fileName.c_str());
    }

    return ModelDataBase::Instance().AddModelData(model);
}