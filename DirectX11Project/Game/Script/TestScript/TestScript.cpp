#include "TestScript.h"
#include "../../../GameSystemBase/Base/GameObject/GameObject.h"
#include "../../../GameSystemBase/Components/ComponentHeaders.h"

TestScript::TestScript() : MonoBehaviour(FunctionMask::NONE)
{
}

void TestScript::Awake()
{
	auto meshFilter = GetGameObject().lock()->AddComponent<MeshFilter>(0);
	GetGameObject().lock()->AddComponent<MeshRenderer>(meshFilter, FindGameObjectWithTag("Main Camera").lock()->GetComponent<Camera>());

	auto gameObj = AddGameObject();
	gameObj.lock()->AddComponent<MeshRenderer>(gameObj.lock()->AddComponent<MeshFilter>(1),
		FindGameObjectWithTag("Main Camera").lock()->GetComponent<Camera>());
}