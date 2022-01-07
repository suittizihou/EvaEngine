#include "TextureManager.h"
#include "../../../System/DebugLog/DebugLog.h"
#include "../../../Utility/GUIDCreator/GUIDCreator.h"
#include "../../../Utility/Texture/Texture/Texture.h"

const GUID& EvaEngine::TextureManager::AddTexture(const std::string& fileName)
{
	GUID guid{ GUID_NULL };
	if (GUIDCreator::Create(guid, "TextureManagerÇ…Çƒ " + fileName + " ÇÃGUIDê∂ê¨Ç…é∏îsÇµÇ‹ÇµÇΩÅB")) {

	}

	return guid;
}
