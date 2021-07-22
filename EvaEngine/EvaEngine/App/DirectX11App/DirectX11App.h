#pragma once
#include "../../Define/D3D11Defines.h"
#include "../../System/DebugLog/DebugLog.h"
#include "../../Utility/ModelUtility/ModelData/ConstantBufferData.h"
#include <memory>

namespace EvaEngine {
	class Camera;
	
	namespace Internal {

		class DirectX11App {
		public:
			// DirectX�̏�����
			static HRESULT Init();

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
			static D3DDevice g_Device;
			static D3DContext g_Context;
			static D3DSwapChain g_SwapChain;
			static D3DRenderTargetView g_RenderTargetView;
			static D3DDepthStencilView g_DepthStencilView;

			static ConstantBuffer g_ConstantBuffer;
			static ConstantBufferData g_ConstantBufferData;

		private:
			static IDXGIAdapter* m_Adapter;
		};
	}
}