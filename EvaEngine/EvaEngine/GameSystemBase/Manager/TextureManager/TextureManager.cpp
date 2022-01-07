#include "TextureManager.h"
#include "../../../System/DebugLog/DebugLog.h"
#include "../../../Utility/GUIDCreator/GUIDCreator.h"
#include "../../../Utility/Texture/Texture/Texture.h"

const GUID& EvaEngine::TextureManager::AddTexture(const std::string& fileName)
{
	GUID guid{ GUID_NULL };
	if (GUIDCreator::Create(guid, "TextureManagerにて " + fileName + " のGUID生成に失敗しました。")) {

	}

	return guid;
}
