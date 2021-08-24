#include "./loader.h"

#include "./fs.h"
#include "./special.h"

#include "./Token.h"
#include "./Lexer.h"

// pl compile fname.ext
int main(int argc, char** args) {

	if(argc < 3) {
		std::cout << "Invalid Argument Amount [exec] [cmd] (fname)" << std::endl;
		return 1;
	}

	std::string file;

	if(std::string(args[1]) == "compile") {
		file = fs::readFile(args[2]);
	} else {
		return 1;
	}

	Lexer lex(getWithSC(file));

	std::vector<TokenStruct> tokens = lex.makeTokens();
	for(TokenStruct ts : tokens) {
		std::cout << ts.eT;
		if(ts.tok == nullptr || ts.isInst) {
			std::cout << "{" << ttc(ts.eT).c_str() << "}" << std::endl;
		} else {
			std::cout << "{" << ts.tok->str() << "}" << std::endl;
		}
	}

	return 0;

}
