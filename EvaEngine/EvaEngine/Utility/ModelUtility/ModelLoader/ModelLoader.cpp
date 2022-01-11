#include "ModelLoader.h"
#include "../..//StringAssist/StringAssist.h"
#include "../../../GameSystemBase/DataBase/ModelDataBase/ModelDataBase.h"

#include "../ModelLoaderUtility/FBXModelLoader/FBXModelLoader.h"
#include "../ModelLoaderUtility/VRMModelLoader/VRMModelLoader.h"
#include "../ModelLoaderUtility/OBJModelLoader/OBJModelLoader.h"

#include "../../../System/DebugLog/DebugLog.h"

#include <chrono>

using namespace EvaEngine;
using namespace EvaEngine::Internal;

std::shared_ptr<ModelData> ModelLoader::Load(const std::string& fileName)
{
    std::vector<std::string> fileSplit{ StringAssist::Split(fileName, ".") };

    if (fileSplit.size() == 0) DebugLog::LogError("拡張子付きで入力してください");

    std::string modelType = fileSplit[fileSplit.size() - 1];

    std::shared_ptr<ModelData> model = std::make_shared<ModelData>(fileName);
    
    auto start = std::chrono::system_clock::now();

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

    auto end = std::chrono::system_clock::now();
    DebugLog::Log(fileName + " : モデル読み込み時間 = " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) + "ms");

    DebugLog::Log(fileName + " : 読み込みメッシュ数 = " + std::to_string(model->meshes.size()));
    DebugLog::Log(fileName + " : 読み込みマテリアル数 = " + std::to_string(model->materials.size()));

    return model;
}