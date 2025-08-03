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

std::shared_ptr<ModelData> ModelLoader::Load(const std::u8string& fileName)
{
    std::vector<std::u8string> fileSplit{ StringAssist::Split(fileName, u8".") };

    if (fileSplit.size() == 0) DebugLog::LogError(u8"Please enter with extension.");

    std::u8string modelType = fileSplit[fileSplit.size() - 1];

    std::shared_ptr<ModelData> model = std::make_shared<ModelData>(fileName);
    
    auto start = std::chrono::system_clock::now();

    if (modelType == u8"fbx") {
        FBXModelLoader fbxModelLoader{};
        fbxModelLoader.LoadModel(fileName, model);
    }
    else if (modelType == u8"vrm") {
        VRMModelLoader vrmModelLoader{};
        vrmModelLoader.LoadModel(fileName, model);
    }
    else if (modelType == u8"obj") {
        OBJModelLoader objModelLoader{};
        objModelLoader.LoadModel(fileName, model);
    }

    auto end = std::chrono::system_clock::now();
    DebugLog::Log(fileName + u8" : model loading time = " + StringAssist::to_u8string(std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) + "ms."));

    DebugLog::Log(fileName + u8" : number of loaded meshes = " + StringAssist::to_u8string(std::to_string(model->meshes.size()) + "."));
    DebugLog::Log(fileName + u8" : number of loaded materials = " + StringAssist::to_u8string(std::to_string(model->materials.size()) + "."));

    return model;
}