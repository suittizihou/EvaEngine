#if _DEBUG
#pragma once

namespace ImGuizmo {
	enum OPERATION;
}

namespace EvaEngine {
	namespace Editor {
		namespace Internal {
			class EditorCommand {
			public:
				EditorCommand() = default;

				// Transform�̕ҏW��GUI�ōs����悤�ɂ���֐�
				void EditTransform(float* cameraView, float* cameraProjection, float* matrix, bool editTransformDecomposition);

			public:
				float camDistance = 8.f;

			private:
				static ImGuizmo::OPERATION mCurrentGizmoOperation;
			};
		}
	}
}
#endif