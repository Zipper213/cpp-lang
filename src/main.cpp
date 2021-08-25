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
		file = std::string(args[2]);
	} else {
		return 1;
	}

	Lexer lex(file);

	std::vector<TokenStruct> tokens = lex.makeTokens();
	std::cout << tokens.size();
	tokens.pop_back();
	for(TokenStruct ts : tokens) {
		Token* tok = ts.tok;
		bool isInst = ts.isInst;
		TokenType eT = ts.eT;
		std::string val = ts.val;
		if(isInst) {
			std::cout << "Instr >> {" << ttc(eT) << "}" << std::endl;
		} else {
			std::cout << "Token >> {" << ttc(eT) << ":" << val << "}" << std::endl;
		}
	}

	return 0;

}
