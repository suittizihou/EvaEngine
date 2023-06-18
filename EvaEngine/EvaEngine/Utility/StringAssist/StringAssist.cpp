#include "StringAssist.h"
#include "../../System/DebugLog/DebugLog.h"

std::vector<std::string> EvaEngine::StringAssist::Split(std::string str, const std::string& del) {

    auto splitStr = std::vector<std::string>();

    if (del.size() == 0) {
        splitStr.push_back(str);
    }
    else {
        auto offset = std::string::size_type(0);
        while (1) {
            auto pos = str.find(del, offset);
            if (pos == std::string::npos) {
                splitStr.push_back(str.substr(offset));
                break;
            }
            splitStr.push_back(str.substr(offset, pos - offset));
            offset = pos + del.size();
        }
    }

    return splitStr;
}

void EvaEngine::StringAssist::Split(char split_char, char* buffer, std::vector<std::string>& out)
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
                out.emplace_back(split_str);
            }
            else
            {
                out.emplace_back("");
            }
            start_point = count + 1;
        }
        count += 1;
    }

    if (start_point != count)
    {
        char split_str[256] = { 0 };
        strncpy_s(split_str, 256, &buffer[start_point], count - start_point);
        out.emplace_back(split_str);
    }
}

// ���C�h��������}���`�o�C�g�����ւ̕ϊ�
void EvaEngine::StringAssist::ToString(const std::wstring& src, std::string& dest) {
    std::size_t converted{};
    std::vector<char> temp(src.size() * sizeof(wchar_t) + 1, '\0');
    if (::_wcstombs_s_l(&converted, temp.data(), temp.size(), src.data(), _TRUNCATE, ::_create_locale(LC_ALL, "jpn")) != 0) {
        DebugLog::LogError(std::system_error{ errno, std::system_category() }.code().message());
    }
    temp.resize(std::char_traits<char>::length(temp.data()));
    temp.shrink_to_fit();
    dest = std::string(temp.begin(), temp.end());
}

// �}���`�o�C�g�������烏�C�h�����ւ̕ϊ�
void EvaEngine::StringAssist::ToWString(const std::string& src, std::wstring& dest) {
    std::size_t converted{};
    std::vector<wchar_t> temp(src.size() * sizeof(char) + 1, L'\0');
    if (::_mbstowcs_s_l(&converted, temp.data(), temp.size(), src.data(), _TRUNCATE, ::_create_locale(LC_ALL, "jpn")) != 0) {
        DebugLog::LogError(std::system_error{ errno, std::system_category() }.code().message());
    }
    temp.resize(std::char_traits<wchar_t>::length(temp.data()));
    temp.shrink_to_fit();
    dest = std::wstring(temp.begin(), temp.end());
}

// Shift-JIS����UTF-8
void EvaEngine::StringAssist::ToUTF8(const std::string& src, std::string& dest) {
    std::wstring temp{};
    ToWString(src, temp);
    ToUTF8String(temp, dest);
}

void EvaEngine::StringAssist::ToUTF8String(const std::wstring& src, std::string& dest) {
    auto const dest_size = ::WideCharToMultiByte(CP_UTF8, 0U, src.data(), -1, nullptr, 0, nullptr, nullptr);
    std::vector<char> temp(dest_size, '\0');
    if (::WideCharToMultiByte(CP_UTF8, 0U, src.data(), -1, temp.data(), temp.size(), nullptr, nullptr) == 0) {
        DebugLog::LogError(std::system_error{ static_cast<int>(::GetLastError()), std::system_category() }.code().message());
    }
    temp.resize(std::char_traits<char>::length(temp.data()));
    temp.shrink_to_fit();
    dest = std::string(temp.begin(), temp.end());
}
