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

				// TransformÇÃï“èWÇGUIÇ≈çsÇ¶ÇÈÇÊÇ§Ç…Ç∑ÇÈä÷êî
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