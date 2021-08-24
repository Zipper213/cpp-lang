#include <vector>
#include <string>
#include "./Token.h"

const char END_LINE = '\0';

int charToInt(char c) {
	if(c == '1') return 1;
	if(c == '2') return 2;
	if(c == '3') return 3;
	if(c == '4') return 4;
	if(c == '5') return 5;
	if(c == '6') return 6;
	if(c == '7') return 7;
	if(c == '8') return 8;
	if(c == '9') return 9;
	if(c == '0') return 0;
	return 0;
};

class Lexer {

	private:
		std::string text;
		int pos = 0;
		char current_char;

		TokenStruct makeNumber(char num) {
			using TT = TokenType;
			Token t(TT::INT, std::to_string(charToInt(num)));
			return TokenStruct {
				&t,
				false,
				TT::INT
			};
		};

	public:
		Lexer(std::string t) {
			text = t;
			advance();
		};
		void advance() {
			pos += 1;
			if(pos < text.length()) {
				current_char = text.at(pos);
			} else {
				current_char = END_LINE;
			}
		};
		std::vector<TokenStruct> makeTokens() {
			using TT = TokenType;
			std::vector<TokenStruct> tokens;
			while(current_char != END_LINE) {

				// DIGITS
				if(
					(current_char == '1') ||
					(current_char == '2') ||
					(current_char == '3') ||
					(current_char == '4') ||
					(current_char == '5') ||
					(current_char == '6') ||
					(current_char == '7') ||
					(current_char == '8') ||
					(current_char == '9') ||
					(current_char == '0')
				) {
					tokens.push_back(makeNumber(current_char));
				}

				// MATH TOKENS
				else if(current_char == '=') 
					tokens.push_back(TokenStruct {nullptr, true, TT::EQUAL});
				else if(current_char == '+')
					tokens.push_back(TokenStruct {nullptr, true, TT::PLUS});
				else if(current_char == '-') 
					tokens.push_back(TokenStruct {nullptr, true, TT::MINUS});
				else if(current_char == '*')
					tokens.push_back(TokenStruct {nullptr, true, TT::MUL});
				else if(current_char == '/')
					tokens.push_back(TokenStruct {nullptr, true, TT::DIV});
				else if(current_char == '(')
					tokens.push_back(TokenStruct {nullptr, true, TT::LPAREN});
				advance();
			}
			return tokens;
		}
};
