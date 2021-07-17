#pragma once
#include <string>
#include <vector>
#include <memory>
#include <imgui.h>

namespace EvaEngine {
	namespace Editor {
		class EditorWindow {
		public:
			EditorWindow(const std::string& windowName, const std::string& windowPath);
			virtual ~EditorWindow();

			void virtual Begin();
			void virtual OnGUI();
			void virtual End();

		private:
			std::string m_WindowName{};
			std::string m_WindowPath{};
		};
	}
}