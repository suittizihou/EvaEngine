#include "TextureLoader.h"
#include "../Texture/Texture.h"
#include "../../../App/DirectX11App/DirectX11App.h"
#include "../../../GameSystemBase/Manager/TextureManager/TextureManager.h"
#include <DirectXTex.h>
#include <WICTextureLoader.h>
#include "../../StringAssist/StringAssist.h"

using namespace DirectX;
using namespace EvaEngine::Internal;

bool EvaEngine::TextureLoader::LoadImage(const std::string& fileName, ID3D11Resource** texture, ID3D11ShaderResourceView** textureView)
{
	std::wstring w_FileName{};
	StringAssist::ToWString(fileName, w_FileName);
	auto hr = CreateWICTextureFromFile(
				DirectX11App::g_Device,
				DirectX11App::g_Context,
				w_FileName.c_str(),
				texture,
				textureView);

	if (FAILED(hr)) {
		DebugLog::LogError("TextureLoaderÇ…Çƒ " + fileName + " ÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
		return false;
	}
	
	return true;
}