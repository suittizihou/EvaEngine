#include "TextureManager.h"
#include "../../../System/DebugLog/DebugLog.h"
#include "../../../Utility/GUIDUtility/GUIDUtility.h"
#include "../../../Utility/Texture/Texture/Texture.h"

const GUID& EvaEngine::TextureManager::LoadTexture(const std::string& fileName)
{
	GUID guid{ GUID_NULL };
	if (GUIDUtility::Create(&guid, "TextureManagerにて " + fileName + " のGUID生成に失敗しました。")) {

	}

	return guid;
}
