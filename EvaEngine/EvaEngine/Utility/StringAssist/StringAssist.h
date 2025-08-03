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

        static std::vector<std::u8string> Split(std::u8string str, const std::u8string& del);
        static std::vector<std::u8string> Split(std::string str, const std::string& del);

		// UTF-8文字列からワイド文字列への変換
        static std::u8string to_u8string(const std::string& str);

        static void Split(char split_char, char* buffer, std::vector<std::u8string>& out);
        // ワイド文字からマルチバイト文字への変換
        static void ToString(const std::wstring& src, std::u8string& dest);
        // マルチバイト文字からワイド文字への変換
        static void ToWString(const std::u8string& src, std::wstring& dest);
        // Shift-JISからUTF-8
        static void ToUTF8(const std::u8string& src, std::u8string& dest);

    private:
        static void ToUTF8String(const std::wstring& src, std::u8string& dest);
    };
}