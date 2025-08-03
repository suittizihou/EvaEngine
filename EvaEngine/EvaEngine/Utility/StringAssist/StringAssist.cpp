#include "StringAssist.h"
#include "../../System/DebugLog/DebugLog.h"
#include <codecvt>

std::vector<std::u8string> EvaEngine::StringAssist::Split(std::u8string str, const std::u8string& del) {

    auto splitStr = std::vector<std::u8string>();

    if (del.size() == 0) {
        splitStr.push_back(str);
    }
    else {
        auto offset = std::u8string::size_type(0);
        while (1) {
            auto pos = str.find(del, offset);
            if (pos == std::u8string::npos) {
                splitStr.push_back(str.substr(offset));
                break;
            }
            splitStr.push_back(str.substr(offset, pos - offset));
            offset = pos + del.size();
        }
    }

    return splitStr;
}

std::vector<std::u8string> EvaEngine::StringAssist::Split(std::string str, const std::string& del)
{
    return Split(to_u8string(str), to_u8string(del));
}

std::u8string EvaEngine::StringAssist::to_u8string(const std::string& str)
{
    // ANSI -> UTF-16
    int wideLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
    std::wstring wide(wideLen, L'\0');
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &wide[0], wideLen);

    // UTF-16 -> UTF-8 (u8string)
    int utf8Len = WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string utf8(utf8Len, '\0');
    WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), -1, &utf8[0], utf8Len, nullptr, nullptr);

    return std::u8string(reinterpret_cast<const char8_t*>(utf8.c_str()));
}

void EvaEngine::StringAssist::Split(char split_char, char* buffer, std::vector<std::u8string>& out)
{
    int count = 0;
    if (buffer == nullptr)
    {
        return;
    }

    int start_point = 0;

    while (buffer[count] != '\0')
    {
        if (buffer[count] == split_char)
        {
            if (start_point != count)
            {
                char split_str[256] = { 0 };
                strncpy_s(split_str, 256, &buffer[start_point], count - start_point);
                out.emplace_back(to_u8string(std::string(split_str)));
            }
            else
            {
                out.emplace_back(to_u8string(""));
            }
            start_point = count + 1;
        }
        count += 1;
    }

    if (start_point != count)
    {
        char split_str[256] = { 0 };
        strncpy_s(split_str, 256, &buffer[start_point], count - start_point);
        out.emplace_back(to_u8string(std::string(split_str)));
    }
}

// ワイド文字からマルチバイト文字への変換
void EvaEngine::StringAssist::ToString(const std::wstring& src, std::u8string& dest) {
    std::size_t converted{};
    std::vector<char> temp(src.size() * sizeof(wchar_t) + 1, '\0');
    if (::_wcstombs_s_l(&converted, temp.data(), temp.size(), src.data(), _TRUNCATE, ::_create_locale(LC_ALL, "jpn")) != 0) {
        DebugLog::LogError(to_u8string(std::system_error{ errno, std::system_category() }.code().message()));
    }
    temp.resize(std::char_traits<char>::length(temp.data()));
    temp.shrink_to_fit();
    dest = std::u8string(temp.begin(), temp.end());
}

// マルチバイト文字からワイド文字への変換
void EvaEngine::StringAssist::ToWString(const std::u8string& src, std::wstring& dest) {
    std::size_t converted{};
    const char* tempStr = reinterpret_cast<const char*>(src.c_str());

    std::vector<wchar_t> temp(strlen(tempStr) + 1, L'\0');
    if (::_mbstowcs_s_l(&converted, temp.data(), temp.size(), tempStr, _TRUNCATE, ::_create_locale(LC_ALL, "jpn")) != 0) {
        DebugLog::LogError(to_u8string(std::system_error{ errno, std::system_category() }.code().message()));
    }
    temp.resize(std::char_traits<wchar_t>::length(temp.data()));
    temp.shrink_to_fit();
    dest = std::wstring(temp.begin(), temp.end());
}

// Shift-JISからUTF-8
void EvaEngine::StringAssist::ToUTF8(const std::u8string& src, std::u8string& dest) {
    std::wstring temp{};
    ToWString(src, temp);
    ToUTF8String(temp, dest);
}

void EvaEngine::StringAssist::ToUTF8String(const std::wstring& src, std::u8string& dest) {
    auto const dest_size = ::WideCharToMultiByte(CP_UTF8, 0U, src.data(), -1, nullptr, 0, nullptr, nullptr);
    std::vector<char> temp(dest_size, '\0');
    if (::WideCharToMultiByte(CP_UTF8, 0U, src.data(), -1, temp.data(), temp.size(), nullptr, nullptr) == 0) {
        DebugLog::LogError(to_u8string(std::system_error{ static_cast<int>(::GetLastError()), std::system_category() }.code().message()));
    }
    temp.resize(std::char_traits<char>::length(temp.data()));
    temp.shrink_to_fit();
    dest = to_u8string(std::string(temp.begin(), temp.end()));
}
