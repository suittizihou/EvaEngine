#include "GUIDCreator.h"
#include <combaseapi.h>
#include "../../System/DebugLog/DebugLog.h"

bool EvaEngine::GUIDCreator::Create(GUID& dest, const std::string& errorMessage)
{
	dest = GUID_NULL;
	if (S_OK != ::CoCreateGuid(&dest)) {
		DebugLog::LogError(errorMessage);
		return false;
	}
	else {
		return true;
	}
}
