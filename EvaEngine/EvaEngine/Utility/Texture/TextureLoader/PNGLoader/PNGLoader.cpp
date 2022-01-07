#include "PNGLoader.h"
#include <DirectXTex.h>
#include "../../../StringAssist/StringAssist.h"

using namespace DirectX;
using namespace EvaEngine;

void PNGLoader::Load(const std::string& fileName)
{
	const unsigned int maxLen{ 100 };
	char ms[maxLen];
	std::wstring w_fileName{ L"" };
	StringAssist::ToWString(fileName, w_fileName);
	//wcstombs(ms, w_fileName.c_str(), maxLen);
}