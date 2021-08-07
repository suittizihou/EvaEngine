#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace EvaEngine {
    class StringAssist {
        StringAssist() = default;
        ~StringAssist() = default;
    public:

        static std::vector<std::string> Split(std::string str, const std::string& del) {

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

        static void Split(char split_char, char* buffer, std::vector<std::string>& out)
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
    };
}