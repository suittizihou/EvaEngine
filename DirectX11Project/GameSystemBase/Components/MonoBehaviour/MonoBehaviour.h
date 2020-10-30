#ifndef MONO_BEHAVIOUR_H_
#define MONO_BEHAVIOUR_H_

#include "../../Base/Component/Component.h"
#include "../../../Utility/Input/Input.h"

class Transform;

class MonoBehaviour : public Component {
public:
	MonoBehaviour(
		const ComponentDesc& componentDesc,
		const UINT& functionMask,
		const bool canMultiAttach = true,
		const bool canRemove = true);
	virtual ~MonoBehaviour() = default;

	// Transform‚Ìweak_ptr‚ð•Ô‚·
	std::weak_ptr<Transform> GetTransform() const;


private:
	std::weak_ptr<Transform> m_Transform;
};

#endif