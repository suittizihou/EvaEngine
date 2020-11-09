#pragma once

#include <d3d11.h>
#include <wrl.h>

class GameApp {
public:
	GameApp();
	~GameApp();

	void Init();
	void Update();
	void Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command);
};