// pch.h: プリコンパイル済みヘッダー ファイルです。
// 次のファイルは、その後のビルドのビルド パフォーマンスを向上させるため 1 回だけコンパイルされます。
// コード補完や多くのコード参照機能などの IntelliSense パフォーマンスにも影響します。
// ただし、ここに一覧表示されているファイルは、ビルド間でいずれかが更新されると、すべてが再コンパイルされます。
// 頻繁に更新するファイルをここに追加しないでください。追加すると、パフォーマンス上の利点がなくなります。

#ifndef PCH_H
#define PCH_H

// プリコンパイルするヘッダーをここに追加します
#include "framework.h"
#include "GameSystemBase/Components/ComponentHeaders.h"
#include "GameSystemBase/Base/GameJobs/GameJobs.h"
#include "GameSystemBase/Base/GameObject/GameObject.h"
#include "GameSystemBase/Base/Scene/Scene.h"
#include "GameSystemBase/Base/Component/Component.h"
#include "GameSystemBase/Base/Component/ComponentDesc.h"
#include "Utility/Time/Time.h"
#include "Utility/ShaderUtility/ShaderLoader/ShaderLoader.h"
#include "Utility/ModelUtility/ModelLoader/ModelLoader.h"
#include "Utility/Mesh/Mesh.h"
#include "Utility/Math/Mathf/Mathf.h"
#include "Utility/Math/Vector2/Vector2.h"
#include "Utility/Math/Vector3/Vector3.h"
#include "Utility/Math/Matrix3x3/Matrix3x3.h"
#include "Utility/Math/Matrix4x4/Matrix4x4.h"
#include "Utility/Math/Quaternion/Quaternion.h"
#include "Utility/Material/Material.h"
#include "Utility/Input/Input.h"
#include "System/DebugLog/DebugLog.h"
#include "Setting/Window/Window.h"
#include "GameSystemBase/Manager/SceneManager/SceneManager.h"

class Test {
public:
	Test() = default;
	~Test() = default;

	void Set(int value);
};

#endif //PCH_H