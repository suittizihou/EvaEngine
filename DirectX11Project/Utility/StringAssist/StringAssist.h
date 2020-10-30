#ifndef STRING_ASSIST_H_
#define STRING_ASSIST_H_

#include <iostream>
#include <string>
#include <vector>

class StringAssist {
public:

	static std::vector<std::string> split(std::string str, char del) {
		int first = 0;
		int last = static_cast<int>(str.find_first_not_of(del));

		std::vector<std::string> result;

		while (first < str.size()) {
			std::string subStr(str, first, last - first);

			result.push_back(subStr);

			first = last + 1;
			last = static_cast<int>(str.find_first_of(del, first));

			if (last == std::string::npos) {
				last = static_cast<int>(str.size());
			}
		}

		return result;
	}
};

#endif