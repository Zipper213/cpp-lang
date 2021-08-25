#define loop(block_name) goto block_name; \
						 block_name##_skip: if(0) \
						 block_name:

#define break(block_name) goto block_name##_skip

#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>

#include "./Token.h"

const char END_LINE = '\0';

std::vector<char> digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

int charToInt(char c) {
	for(int i = 0; i < digits.size(); i++) {
		if(c == digits[i]) return i;
	}
	return -1;
};

class Lexer {

	private:
		std::string text;
		int pos = -1;
		char current_char;

		TokenStruct makeNumber(std::vector<int> numbers) {
			int num = 0;
			
			int size = numbers.size();
			for(int i = 0; i < size; i++) {
				num += std::pow(10, size-i-1) * numbers[i];
			}

			using TT = TokenType;
			Token t(TT::INT, std::to_string(num));
			return TokenStruct {
				&t,
				false,
				TT::INT,
				std::to_string(num)
			};
		};
		bool isCharInteger(char c) {
			for(int i = 0; i < digits.size(); i++) {
				if(c == digits[i]) return true;
			}
			return false;
		};
		TokenStruct makeString(std::vector<char> string, bool isChar) {
			std::string str;
			for(char c : string) {
				str += c;
			}
			using TT = TokenType;
			Token t((isChar ? TT::CHR : TT::STR), str);
			return TokenStruct {
				&t,
				false,
				(isChar ? TT::CHR : TT::STR),
				str
			};
		};
		int getQuote(char c) {
			if(c == '"') return 1;
			if(c == '\'') return 2;
			return 0;
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
			while(current_char != END_LINE && pos < text.length()) {
				if(
					(current_char == '\t') ||
					(current_char == '\n') ||
					(current_char == '\0')
				) {
					advance();
					continue;
				}

				// DIGITS
				bool isInt = false;
				bool hadNum = false;
				if(isCharInteger(current_char)) {
					isInt = true;
					hadNum = true;
				}
				std::vector<int> numbers;
				while(isInt && isCharInteger(current_char)) {
					int current = std::atoi(&current_char);
					numbers.push_back(current);
					advance();
				}
				if(hadNum) {
					tokens.push_back(makeNumber(numbers));
					continue;
				} else {
					if(getQuote(current_char) == 0) {} else {
						bool isChar = false;
						bool stillIn = true;
						bool isEscaped = false;
						std::vector<char> string;
						if(current_char == '\'') {
							isChar = true;
						}
						advance();

						loop(wsi)
						while(stillIn) {
							if(getQuote(current_char) == 0) {
								if(current_char == '\\') {
									isEscaped = !isEscaped;
								}
								string.push_back(current_char);
								advance();
								continue;
							} else {
								if(isChar) {
									if(getQuote(current_char) == 2) {
										if(isEscaped == true) {
											string.push_back(current_char);
											isEscaped = false;
										} else {
											advance();
											stillIn = false;
											break(wsi);
										}
									} else {
										string.push_back(current_char);
									}
								} else {
									if(getQuote(current_char) == 1) {
										if(isEscaped == true) {
											string.push_back(current_char);
											isEscaped = false;
										} else {
											advance();
											stillIn = false;
											break(wsi);
										}
									} else {
										string.push_back(current_char);
									}
								}
								continue;
							}
							tokens.push_back(makeString(string, isChar));
							advance();
						}
						continue;
					}	
				}

				// MATH TOKENS
				if(current_char == '=') 
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
