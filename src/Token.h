#pragma once

#include <string>
#include <iostream>

enum TokenType {
	INT, FLOAT, EQUAL, PLUS, MINUS, MUL, DIV, LPAREN, RPAREN
};
std::string ttc(TokenType t) {
	using TT = TokenType;
	if(t == TT::INT) return "INT";
	if(t == TT::FLOAT) return "FLOAT";
	if(t == TT::EQUAL) return "EQUAL";
	if(t == TT::PLUS) return "PLUS";
	if(t == TT::MINUS) return "MINUS";
	if(t == TT::MUL) return "MUL";
	if(t == TT::DIV) return "DIV";
	if(t == TT::LPAREN) return "LPAREN";
	if(t == TT::RPAREN) return "RPAREN";
	return "";
};

class Token {
	private:
		TokenType _type;
		std::string _value;
	public:
		Token(TokenType type, std::string value) {
			_type = type;
			_value = value;
		};
		const char* str() {
			std::string a = ttc(_type);
			std::cout << a << std::endl;
			if(_value != "")
				return (a + std::string(":") + _value).c_str();
			return a.c_str();
		};
};

struct TokenStruct {
	Token* tok = nullptr;
	bool isInst = false;
	TokenType eT;
};
