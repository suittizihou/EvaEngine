#include "TextureManager.h"
#include "../../../System/DebugLog/DebugLog.h"
#include "../../../Utility/Texture/Texture/Texture.h"
#include "../../../Utility/Texture/TextureLoader/TextureLoader.h"

#include <wrl.h>

void EvaEngine::TextureManager::LoadTexture(const std::u8string& fileName, GUID* guid)
{
	*guid = GUID_NULL;
	if (GUIDUtility::Create(guid, u8"TextureManagerにて " + fileName + u8" のGUID生成に失敗しました。")) {
		return;
	}
	
	Microsoft::WRL::ComPtr<ID3D11Resource> tempTex{ nullptr };
	ID3D11ShaderResourceView* tempView{ nullptr };

	if (EvaEngine::TextureLoader::LoadImage(fileName, &tempTex, &tempView) == false) return;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex{ nullptr };
	if (FAILED(tempTex.As(&tex))) {
		DebugLog::LogError(u8"TextureManagerにてID3D11ResourcesからID3D11Texture2DのAs関数を用いたインターフェース取得に失敗しました。");
		return;
	}

	D3D11_TEXTURE2D_DESC desc{};
	tex->GetDesc(&desc);
	
	auto texture = std::make_shared<Texture>(desc.Width, desc.Height);
	texture->SetD3DResource(tempTex.Get());
	texture->SetD3DShaderResourceView(tempView);
	m_Textures[*guid] = texture;
}

std::weak_ptr<EvaEngine::Texture> EvaEngine::TextureManager::GetTextureGUID(const GUID& guid)
{
	return m_Textures[guid];
}