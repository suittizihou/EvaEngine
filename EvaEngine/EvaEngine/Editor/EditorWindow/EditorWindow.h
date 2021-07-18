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

		public:
			bool IsOpen() { return isOpen; };

		protected:
			bool isOpen{ true };
		};

		template<class T>
		class EditorWindow : public EditorWindowBase {
		public:
			EditorWindow(const std::string& windowPath) :
				m_WindowName{ TypeIDAssist<T>().GetClassName() },
				m_WindowPath{ windowPath }
			{
			}

			EditorWindow(const std::string& windowPath, const Vector2& windowSize) :
				m_WindowName{ TypeIDAssist<T>().GetClassName() },
				m_WindowPath{ windowPath },
				m_WindowSize{ windowSize }
			{
			}

			EditorWindow(const std::string& windowPath, const ImGuiWindowFlags& windowFlags) :
				m_WindowName{ TypeIDAssist<T>().GetClassName() },
				m_WindowPath{ windowPath },
				windowFlags{ windowFlags }
			{
			}

			EditorWindow(const std::string& windowPath, const Vector2& windowSize, const ImGuiWindowFlags& windowFlags) :
				m_WindowName{ TypeIDAssist<T>().GetClassName() },
				m_WindowPath{ windowPath },
				m_WindowSize{ windowSize },
				windowFlags{ windowFlags }
			{
			}

			virtual ~EditorWindow() = default;

			void virtual Begin() override
			{
				ImGui::SetNextWindowSize(ImVec2(m_WindowSize.x, m_WindowSize.y), ImGuiCond_FirstUseEver);
				ImGui::Begin(m_WindowName.c_str(), &isOpen, windowFlags);
			}

			void virtual OnGUI() override {};

			void virtual End() override { ImGui::End(); };

			std::string GetWindowName() const { return m_WindowName; };

			std::string GetWindowPath() const { return m_WindowPath; };

			Vector2 GetWindowSize() const { return m_WindowSize; };
			
		public:
			ImGuiWindowFlags windowFlags{};

		private:
			std::string m_WindowName{};
			std::string m_WindowPath{};
			Vector2 m_WindowSize{ 300.0f, 450.0f };
		};
	}
}