#pragma once
#include "../../Define/D3D11Defines.h"
#include "../../System/DebugLog/DebugLog.h"
#include "../../Utility/ModelUtility/ModelData/ConstantBufferData.h"
#include <memory>
#include <dxgidebug.h>

namespace EvaEngine {
	class Camera;
	
	namespace Internal {

		class DirectX11App {
			DirectX11App() = default;
			~DirectX11App() = default;
		public:

			// DirectX�̏�����
			static HRESULT Init();
			// ComPtr�����̉��
			static void Release();

#if _DEBUG
			// ComPtr�̃��������[�N���o��
			static void ReportLiveObjects();
			// Debug�Ɏg�����I�u�W�F�N�g�����
			static void DebugRelease();
#endif

		private:
			// �n�[�h�E�F�A�̃`�F�b�N(���GPU�������Ă���GPU���g���悤�ɂ���)
			static HRESULT HardWareCheck();
			// �f�o�C�X�ƃX���b�v�`�F�C���̍쐬
			static HRESULT CreateDeviceAndSwapChain();
			// ���X�^���C�U�̍쐬
			static HRESULT CreateRasterizerState();
			// �����_�[�^�[�Q�b�g�̍쐬
			static HRESULT CreateRenderTargetView();
			// �[�x�X�e���V���r���[�̍쐬
			static HRESULT CreateDepthAndStencilView();
			// �萔�o�b�t�@�̍쐬
			static HRESULT CreateConstantBuffer();
			// �萔�o�b�t�@�̃Z�b�g
			static void SetConstantBuffer(const std::weak_ptr<Camera>& camera);

		public:
			static ID3D11Device* g_Device;
			static ID3D11DeviceContext* g_Context;
			static IDXGISwapChain* g_SwapChain;
			static ID3D11RenderTargetView* g_EditorRenderTargetView;
			static ID3D11DepthStencilView* g_EditorDepthStencilView;

			static ID3D11Buffer* g_ConstantBuffer;
			static ConstantBufferData g_ConstantBufferData;

#if _DEBUG
			static IDXGIDebug* g_pDxgiDebug;
			static ID3D11Debug* g_pD3DDebug;
#endif

		private:
			static IDXGIAdapter* m_Adapter;
		};
	}
}