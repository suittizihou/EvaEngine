#include "GUIDUtility.h"
#include <combaseapi.h>
#include <rpc.h>
#include "../../System/DebugLog/DebugLog.h"

#pragma comment(lib, "Rpcrt4.lib")

bool EvaEngine::GUIDUtility::Create(GUID* dest, const std::u8string& errorMessage)
{
	*dest = GUID_NULL;
	if (S_OK != ::CoCreateGuid(dest)) {
		DebugLog::LogError(errorMessage);
		return false;
	}
	else {
		return true;
	}
}

std::string EvaEngine::GUIDUtility::ToString(const GUID& src)
{
	std::string result{};
	RPC_CSTR temp;
	if (RPC_S_OK == ::UuidToString(&src, &temp)) {
		result = (CHAR*)temp;
		RpcStringFree(&temp);
	}
	return result;
}