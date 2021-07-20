#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace EvaEngine {
    class StringAssist {
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
    };
}