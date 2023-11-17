#if _DEBUG
#pragma once
#include <string>
#include <vector>
#include <list>
#include <memory>
#include <imgui.h>
#include "../../Utility/TypeIDAssist/TypeIDAssist.h"
#include "../../Utility/Math/Vector2/Vector2.h"

namespace EvaEngine {
	namespace Editor {

		class EditorWindowBase {
		public:
			EditorWindowBase() = default;
			virtual ~EditorWindowBase() = default;

		public:
			virtual void Init() = 0;
			virtual void Begin() = 0;
			virtual void OnGUI() = 0;
			virtual void End() = 0;
			
			virtual std::string GetWindowName() const = 0;
			virtual std::string GetWindowPath() const = 0;
			virtual Vector2 GetWindowSize() const = 0;


		public:
			bool isOpen{ false };
		};

		template<class T>
		class EditorWindow : public EditorWindowBase {
		public:
			EditorWindow(const std::string& windowPath) :
				m_WindowName{ TypeIDAssist<T>::GetClassName() },
				m_WindowPath{ windowPath }
			{
				InternalInit();
			}

			EditorWindow(const std::string& windowPath, const Vector2& windowSize) :
				m_WindowName{ TypeIDAssist<T>::GetClassName() },
				m_WindowPath{ windowPath },
				m_WindowSize{ windowSize }
			{
				InternalInit();
			}

			EditorWindow(const std::string& windowPath, const ImGuiWindowFlags& windowFlags) :
				m_WindowName{ TypeIDAssist<T>::GetClassName() },
				m_WindowPath{ windowPath },
				windowFlags{ windowFlags }
			{
				InternalInit();
			}

			EditorWindow(const std::string& windowPath, const Vector2& windowSize, const ImGuiWindowFlags& windowFlags) :
				m_WindowName{ TypeIDAssist<T>::GetClassName() },
				m_WindowPath{ windowPath },
				m_WindowSize{ windowSize },
				windowFlags{ windowFlags }
			{
				InternalInit();
			}

			virtual ~EditorWindow() = default;

		private:
			void InternalInit() {
				isOpen = true;
			}

		protected:
			virtual void Init() override {};

		public:
			// 開始処理
			void virtual Begin() override
			{
				ImGui::SetNextWindowSize(ImVec2(m_WindowSize.x, m_WindowSize.y), ImGuiCond_FirstUseEver);
				ImGui::Begin(m_WindowName.c_str(), &isOpen, windowFlags, &m_Loaded);
			}
			// 描画処理
			void virtual OnGUI() override {};
			// 終了処理
			void virtual End() override { ImGui::End(); };

		public:
			// Window名を取得
			std::string GetWindowName() const override { return m_WindowName; };
			// WindowPathを取得
			std::string GetWindowPath() const override { return m_WindowPath; };
			// WindowSizeを取得
			Vector2 GetWindowSize() const override { return m_WindowSize; };
			
		public:
			ImGuiWindowFlags windowFlags{};

		private:
			std::string m_WindowName{};
			std::string m_WindowPath{};
			Vector2 m_WindowSize{ 300.0f, 450.0f };

		private:
			bool m_Loaded{ false };
		};
	}
}
#endif