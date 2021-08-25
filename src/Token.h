#pragma once

#include <string>
#include <iostream>

enum TokenType {
	INT = 0, FLOAT,
	CHR, STR,
	EQUAL, PLUS, MINUS, MUL, DIV, LPAREN, RPAREN
};
const char* types[] = {
	"INT", "FLOAT", 
	"CHR", "STR",
	"EQUAL", "PLUS", "MINUS", "MUL", "DIV", "LPAREN", "RPAREN"
};
const char* ttc(TokenType t) {
	return types[t];
};

class Token {
	private:
		TokenType _type;
	
	public:
		std::string val;
		
		Token(TokenType type, std::string value) {
			_type = type;
			val = value;
		};
		const char* str() {
			std::string a = std::string(ttc(_type));
			if(val != "") {
				std::string s = (a + ":" + val).c_str();
				return s.c_str();
			}
			return a.c_str();
		};
};

typedef struct {
	unsigned int start;
	unsigned int end;
	Token* tok;
	bool isInst;
	TokenType eT;
	std::string val;
} TokenStruct;
