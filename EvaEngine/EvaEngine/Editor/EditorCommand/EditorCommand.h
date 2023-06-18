#if _DEBUG
#pragma once

namespace ImGuizmo {
	enum OPERATION;
}

namespace EvaEngine {
	namespace Editor {
		namespace Internal {
			class EditorCommand {
				EditorCommand() = default;
				~EditorCommand() = default;
			public:

				// Transform�̕ҏW��GUI�ōs����悤�ɂ���֐�
				static void EditTransform(float* cameraView, float* cameraProjection, float* matrix, bool editTransformDecomposition, float camDistance = 8.0f);

			private:
				static ImGuizmo::OPERATION mCurrentGizmoOperation;
			};
		}
	}
}
#endif