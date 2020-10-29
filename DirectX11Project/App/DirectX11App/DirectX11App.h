#pragma once
#include "../../Define/D3D11Defines.h"

class DirectX11App {
public:
	static bool Init();
	static int Update();

public:
	D3DDevice m_Device{};
	D3DContext m_Context{};
	SwapChain m_SwapChain{};
	Texture2D m_Texture2D{};
	RenderTargetView m_RenderTargetView{};

};