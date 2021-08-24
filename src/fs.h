#include "./loader.h"

namespace fs {
	std::vector<std::string> getLines(const char* fileName) {
		std::vector<std::string> lines;
		std::ifstream f(fileName);
		if(f.is_open()) {
			std::string line;
			while(std::getline(f, line)) {
				lines.push_back(line);
			};
			f.close();
		};
		return lines;
	};

	std::string readFile(const char* fileName, bool showLine = false) {
		std::vector<std::string> lines = getLines(fileName);
		std::string res;
		int ln = 1;
		for(std::string& line : lines) {
			res += ((showLine == true) ? std::to_string(ln) + ": " : "") + line + "\n";
			ln++;
		};
		return res + '\0';
	};
}
