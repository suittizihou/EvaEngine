#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <guiddef.h>

namespace EvaEngine {
	
	class Texture;

	class TextureManager
	{
	public:
		const GUID& LoadTexture(const std::string& fileName);
		const GUID& GetTextureGUID();
		
	private:
		std::unordered_map<GUID*, std::shared_ptr<Texture>> m_Textures;
	};
}