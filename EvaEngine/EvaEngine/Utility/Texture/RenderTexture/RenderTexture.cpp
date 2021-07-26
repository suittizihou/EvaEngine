#include "RenderTexture.h"
#include "../Texture2D/Texture2D.h"

EvaEngine::RenderTexture::RenderTexture(const UINT width, const UINT height)
{
	m_pTexture2D = std::make_unique<Texture2D>(width, height);
}

void EvaEngine::RenderTexture::Create()
{
}
