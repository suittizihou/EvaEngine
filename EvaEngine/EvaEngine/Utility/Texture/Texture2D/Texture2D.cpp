#include "Texture2D.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

EvaEngine::Texture2D::Texture2D()
{
	textureType = TextureType::Tex2D;
}

EvaEngine::Texture2D::~Texture2D()
{
	if(m_Texture2D != nullptr)
		m_Texture2D->Release();
}

void STDMETHODCALLTYPE Texture2D::GetD3DTexture2D(_Out_ D3D11_TEXTURE2D_DESC* pDesc)
{
	return m_Texture2D->GetDesc(pDesc);
}