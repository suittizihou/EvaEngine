#include "ModelLoader.h"
#include "../..//StringAssist/StringAssist.h"
#include "../../../GameSystemBase/DataBase/ModelDataBase/ModelDataBase.h"

#include "../ModelLoaderUtility/FBXModelLoader/FBXModelLoader.h"
#include "../ModelLoaderUtility/VRMModelLoader/VRMModelLoader.h"
#include "../ModelLoaderUtility/OBJModelLoader/OBJModelLoader.h"

#include "../../../System/DebugLog/DebugLog.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

std::shared_ptr<ModelData> ModelLoader::Load(const std::string& fileName)
{
    std::vector<std::string> fileSplit{ StringAssist::Split(fileName, ".") };

    if (fileSplit.size() == 0) DebugLog::LogError(u8"拡張子付きで入力してください");

    std::string modelType = fileSplit[fileSplit.size() - 1];

    std::shared_ptr<ModelData> model = std::make_shared<ModelData>();
    
    if (modelType == "fbx") {
        FBXModelLoader fbxModelLoader{};
        fbxModelLoader.LoadModel(fileName.c_str(), model);
    }
    else if (modelType == "vrm") {
        VRMModelLoader vrmModelLoader{};
        vrmModelLoader.LoadModel(fileName.c_str(), model);
    }
    else if (modelType == "obj") {
        OBJModelLoader objModelLoader{};
        objModelLoader.LoadModel(fileName.c_str(), model);
    }

    DebugLog::Log(fileName + u8" : 読み込みメッシュ数 = " + std::to_string(model->meshes.size()));
    DebugLog::Log(fileName + u8" : 読み込みマテリアル数 = " + std::to_string(model->materials.size()));

    return model;
}