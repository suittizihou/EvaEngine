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
				m_WindowName{ TypeIDAssist<T>().GetClassName() },
				m_WindowPath{ windowPath }
			{
				Init();
			}

			EditorWindow(const std::string& windowPath, const Vector2& windowSize) :
				m_WindowName{ TypeIDAssist<T>().GetClassName() },
				m_WindowPath{ windowPath },
				m_WindowSize{ windowSize }
			{
				Init();
			}

			EditorWindow(const std::string& windowPath, const ImGuiWindowFlags& windowFlags) :
				m_WindowName{ TypeIDAssist<T>().GetClassName() },
				m_WindowPath{ windowPath },
				windowFlags{ windowFlags }
			{
				Init();
			}

			EditorWindow(const std::string& windowPath, const Vector2& windowSize, const ImGuiWindowFlags& windowFlags) :
				m_WindowName{ TypeIDAssist<T>().GetClassName() },
				m_WindowPath{ windowPath },
				m_WindowSize{ windowSize },
				windowFlags{ windowFlags }
			{
				Init();
			}

			virtual ~EditorWindow() = default;

		protected:
			void Init() {
				isOpen = true;
			};

		public:
			// äJénèàóù
			void virtual Begin() override
			{
				ImGui::SetNextWindowSize(ImVec2(m_WindowSize.x, m_WindowSize.y), ImGuiCond_FirstUseEver);
				ImGui::Begin(m_WindowName.c_str(), &isOpen, windowFlags, &load);
			}
			// ï`âÊèàóù
			void virtual OnGUI() override {};
			// èIóπèàóù
			void virtual End() override { ImGui::End(); };

		public:
			// WindowñºÇéÊìæ
			std::string GetWindowName() const override { return m_WindowName; };
			// WindowPathÇéÊìæ
			std::string GetWindowPath() const override { return m_WindowPath; };
			// WindowSizeÇéÊìæ
			Vector2 GetWindowSize() const override { return m_WindowSize; };
			
		public:
			ImGuiWindowFlags windowFlags{};

		private:
			std::string m_WindowName{};
			std::string m_WindowPath{};
			Vector2 m_WindowSize{ 300.0f, 450.0f };

		private:
			bool load{ false };
		};
	}
}