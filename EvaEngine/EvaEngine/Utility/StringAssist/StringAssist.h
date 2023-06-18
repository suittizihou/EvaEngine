#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

namespace EvaEngine {
    class StringAssist {
        StringAssist() = default;
        ~StringAssist() = default;
    public:

        static std::vector<std::string> Split(std::string str, const std::string& del);

        static void Split(char split_char, char* buffer, std::vector<std::string>& out);
        // ���C�h��������}���`�o�C�g�����ւ̕ϊ�
        static void ToString(const std::wstring& src, std::string& dest);
        // �}���`�o�C�g�������烏�C�h�����ւ̕ϊ�
        static void ToWString(const std::string& src, std::wstring& dest);
        // Shift-JIS����UTF-8
        static void ToUTF8(const std::string& src, std::string& dest);

    private:
        static void ToUTF8String(const std::wstring& src, std::string& dest);
    };
}