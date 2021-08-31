#include "./loader.h"

#include "./fs.h"
#include "./special.h"

#include "./Token.h"

#include "./Lexer.h"
#include "./Grammar.h"

// pl compile fname.ext
int main(int argc, char** args) {

	if(argc < 4) {
		std::cout << "Invalid Argument Amount [exec] [cmd] (fname) (grammar fname)" << std::endl;
		return 1;
	}

	std::string file;
	std::string gFile;

	if(std::string(args[1]) == "compile") {
		file = std::string(args[2]);
		gFile = std::string(args[3]);
	} else {
		return 1;
	}

	Lexer lex(file);
	
	std::vector<TokenStruct> tokens = lex.makeTokens();
	std::cout << tokens.size() << " tokens." << std::endl;

	Grammar gram(&tokens);
	gram.prepare(fs::getLines(gFile.c_str()));
	gram.parse();

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
};