#pragma once
#include <memory>
#include <unordered_map>
#include <string>


namespace EvaEngine {
	
	class Texture;

	class TextureManager
	{
	public:
		GUID const& AddTexture(const std::string& fileName);
		GUID const& GetTextureGUID();
		
	private:
		std::unordered_map<GUID*, std::shared_ptr<Texture>> m_Textures;
	};
}