#pragma once

#include "../../EditorWindow/EditorWindow.h"

namespace EvaEngine {
	namespace Editor {
		namespace Internal {
			class ConsoleWindow : public EditorWindow<ConsoleWindow> {
			public:
				ConsoleWindow(const std::u8string& windowPath);
				~ConsoleWindow() = default;

				void OnGUI() override;
			};
		}
	}
}