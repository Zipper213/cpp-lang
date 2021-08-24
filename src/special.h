#include "./loader.h"

void printWithSC(std::string str, bool nl = true) {
	int pos = 0;
	char c;
	while(pos != str.length()) {
		c = str.at(pos);
		int i = (unsigned char) c;
		switch(i) {
			case '\\':
				std::cout << "\\\\";
				break;
			case '\t':
				std::cout << "\\t";
				break;
			case '\n':
				std::cout << "\\n" << (nl ? ("\n") : (""));
				break;
			case '\r':
				std::cout << "\\r";
				break;
			case '\0':
				std::cout << "\\0";
				break;
			default:
				std::cout << c;
				break;
		};
		pos++;
	}
};
std::string getWithSC(std::string str, bool nl = true) {
	int pos = 0;
	char c;
	std::string s = "";
	while(pos != str.length()) {
		c = str.at(pos);
		int i = (unsigned char) c;
		switch(i) {
			case '\\':
				s += "\\\\";
				break;
			case '\t':
				s += "\\t";
				break;
			case '\n':
				s += "\\n";
				s += (nl ? ("\n") : (""));
				break;
			case '\r':
				s += "\\r";
				break;
			case '\0':
				s += "\\0";
				break;
			default:
				s += c;
				break;
		};
		pos++;
	}
	return s;
};
