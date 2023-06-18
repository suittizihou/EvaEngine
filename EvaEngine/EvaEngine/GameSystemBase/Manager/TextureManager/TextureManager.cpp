#include "TextureManager.h"
#include "../../../System/DebugLog/DebugLog.h"
#include "../../../Utility/Texture/Texture/Texture.h"
#include "../../../Utility/Texture/TextureLoader/TextureLoader.h"

#include <wrl.h>

void EvaEngine::TextureManager::LoadTexture(const std::string& fileName, GUID* guid)
{
	*guid = GUID_NULL;
	if (GUIDUtility::Create(guid, "TextureManager�ɂ� " + fileName + " ��GUID�����Ɏ��s���܂����B")) {
		return;
	}
	
	Microsoft::WRL::ComPtr<ID3D11Resource> tempTex{ nullptr };
	ID3D11ShaderResourceView* tempView{ nullptr };

	if (EvaEngine::TextureLoader::LoadImage(fileName, &tempTex, &tempView) == false) return;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex{ nullptr };
	if (FAILED(tempTex.As(&tex))) {
		DebugLog::LogError("TextureManager�ɂ�ID3D11Resources����ID3D11Texture2D��As�֐���p�����C���^�[�t�F�[�X�擾�Ɏ��s���܂����B");
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