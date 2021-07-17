#pragma once

#include "../../EditorWindow/EditorWindow.h"

namespace EvaEngine {
	namespace Editor {
		class ConsoleWindow : public EditorWindow {
		public:
			ConsoleWindow(const std::string& windowName, const std::string& windowPath);
			~ConsoleWindow() = default;

			void OnGUI();
		};
	}
}