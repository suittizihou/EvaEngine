#if _DEBUG
#pragma once

#include "../../EditorWindow/EditorWindow.h"

namespace EvaEngine
{
	namespace Editor 
	{
		namespace Internal 
		{
			class GameWindow : public EditorWindow<GameWindow> {
			public:
				GameWindow(const std::string& windowPath) : 
					EditorWindow<GameWindow>(windowPath) {};
				~GameWindow() = default;

				void Init() override;
				void OnGUI() override;
			};
		}
	}
}
#endif