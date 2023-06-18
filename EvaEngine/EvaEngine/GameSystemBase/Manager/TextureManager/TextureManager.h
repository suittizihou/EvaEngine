#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <guiddef.h>
#include "../../../Utility/GUIDUtility/GUIDUtility.h"

namespace EvaEngine {
	class Texture;

	class TextureManager
	{
	public:
		void LoadTexture(const std::string& fileName, GUID* guid);
		std::weak_ptr<Texture> GetTextureGUID(const GUID& guid);
		
	private:
		std::unordered_map<GUID, std::shared_ptr<Texture>> m_Textures;
	};
}