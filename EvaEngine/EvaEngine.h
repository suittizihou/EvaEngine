#pragma once

#pragma comment(lib, "EvaEngine.lib")

#include "EvaEngine/App/MainApp/MainApp.h"
#include "EvaEngine/GameSystemBase/Base/GameBase/GameBase.h"
#include "EvaEngine/GameSystemBase/Components/ComponentHeaders.h"
#include "EvaEngine/GameSystemBase/Base/GameJobs/GameJobs.h"
#include "EvaEngine/GameSystemBase/Base/GameObject/GameObject.h"
#include "EvaEngine/GameSystemBase/Base/Component/Component.h"
#include "EvaEngine/GameSystemBase/Base/Component/ComponentDesc.h"
#include "EvaEngine/GameSystemBase/Base/Scene/Scene.h"
#include "EvaEngine/GameSystemBase/Manager/SceneManager/SceneManager.h"
#include "EvaEngine/Utility/Time/Time.h"
#include "EvaEngine/Utility/ShaderUtility/ShaderLoader/ShaderLoader.h"
#include "EvaEngine/Utility/ModelUtility/ModelLoader/ModelLoader.h"
#include "EvaEngine/Utility/Mesh/Mesh.h"
#include "EvaEngine/Utility/Math/Math.h"
#include "EvaEngine/Utility/Material/Material.h"
#include "EvaEngine/Utility/Input/Input.h"
#include "EvaEngine/System/DebugLog/DebugLog.h"
#include "EvaEngine/Setting/Window/Window.h"