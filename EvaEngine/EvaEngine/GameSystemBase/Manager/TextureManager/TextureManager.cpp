#include "TextureManager.h"
#include "../../../System/DebugLog/DebugLog.h"
#include "../../../Utility/GUIDUtility/GUIDUtility.h"
#include "../../../Utility/Texture/Texture/Texture.h"

const GUID& EvaEngine::TextureManager::AddTexture(const std::string& fileName)
{
	GUID guid{ GUID_NULL };
	if (GUIDUtility::Create(&guid, "TextureManager�ɂ� " + fileName + " ��GUID�����Ɏ��s���܂����B")) {

	}

	return guid;
}
