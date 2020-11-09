#include "GameApp.h"
#include "../DirectX11App/DirectX11App.h"
#include "../../GameSystemBase/DataBase/ModelDataBase/ModelDataBase.h"
#include "../../GameSystemBase/DataBase/ShaderDataBase/ShaderDataBase.h"
#include "../../GameSystemBase/DataBase/TextureDataBase/TextureDataBase.h"
#include "../../GameSystemBase/DataBase/SceneDataBase/SceneDataBase.h"
#include "../../Game/Scene/GameTitle/GameTitle.h"
#include "../../Game/Scene/GameMain/GameMain.h"
#include "../../GameSystemBase/Manager/DrawManager/DrawManager.h"

GameApp::GameApp()
{
}

GameApp::~GameApp()
{
	// 全シェーダーのリソースを解放
	ShaderDataBase::Instance().DeleteAllShader();
}

void GameApp::Init()
{
	SceneDataBase::Instance().AddScene<GameTitle>(SceneType::GameTitle);
	SceneDataBase::Instance().AddScene<GameMain>(SceneType::GameMain);

	SceneDataBase::Instance().LoadScene(SceneType::GameTitle);
	SceneDataBase::Instance().InitializeScene();
}

void GameApp::Update()
{
	SceneDataBase::Instance().FixedUpdate();
	SceneDataBase::Instance().Update();
	SceneDataBase::Instance().LateUpdate();
	SceneDataBase::Instance().RemoveComponent();

	SceneDataBase::Instance().SceneChange();
}

void GameApp::Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command)
{
	// 描画開始処理
	DrawManager::DrawBegin();

	// ポリゴンの種類
	DirectX11App::g_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// シェーダーのセット
	Shader shader{ DrawManager::GetDefaultShader() };
	DrawManager::SetShader(shader);
	// レンダーターゲットの設定
	DirectX11App::g_Context->OMSetRenderTargets(1, DirectX11App::g_RenderTargetView.GetAddressOf(), DirectX11App::g_DepthStencilView.Get());

	SceneDataBase::Instance().Draw(command);

	// 描画終了処理
	DrawManager::DrawEnd();
}
