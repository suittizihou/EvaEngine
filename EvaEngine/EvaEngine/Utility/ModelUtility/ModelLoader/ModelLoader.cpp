#include "ModelLoader.h"
#include "../..//StringAssist/StringAssist.h"
#include "../../../GameSystemBase/DataBase/ModelDataBase/ModelDataBase.h"

#include "../ModelLoaderUtility/FBXModelLoader/FBXModelLoader.h"
#include "../ModelLoaderUtility/VRMModelLoader/VRMModelLoader.h"
#include "../ModelLoaderUtility/OBJModelLoader/OBJModelLoader.h"

#include "../../../System/DebugLog/DebugLog.h"

using namespace EvaEngine;

int ModelLoader::Load(const std::string& fileName)
{
    std::vector<std::string> fileSplit{ StringAssist::split(fileName, '.') };

    if (fileSplit.size() == 0) DebugLog::LogError("Šg’£Žq•t‚«‚Å“ü—Í‚µ‚Ä‚­‚¾‚³‚¢");

    std::string modelType = fileSplit[fileSplit.size() - 1];

    ModelData model{};
    
    if (modelType == "fbx") {
        FBXModelLoader fbxModelLoader{};
        model = fbxModelLoader.LoadModel(fileName.c_str());
    }
    else if (modelType == "vrm") {
        VRMModelLoader vrmModelLoader{};
        model = vrmModelLoader.LoadModel(fileName.c_str());
    }
    else if (modelType == "obj") {
        OBJModelLoader objModelLoader{};
        model = objModelLoader.LoadModel(fileName.c_str());
    }

    return ModelDataBase::Instance().AddModelData(model);
}