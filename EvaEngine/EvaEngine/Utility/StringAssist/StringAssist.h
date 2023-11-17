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
        // ワイド文字からマルチバイト文字への変換
        static void ToString(const std::wstring& src, std::string& dest);
        // マルチバイト文字からワイド文字への変換
        static void ToWString(const std::string& src, std::wstring& dest);
        // Shift-JISからUTF-8
        static void ToUTF8(const std::string& src, std::string& dest);

    private:
        static void ToUTF8String(const std::wstring& src, std::string& dest);
    };
}