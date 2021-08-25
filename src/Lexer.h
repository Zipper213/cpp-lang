#pragma once

#define loop(block_name) goto block_name; \
						 block_name##_skip: if(0) \
						 block_name:

#define break(block_name) goto block_name##_skip

#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>

#include "./fs.h"
#include "./special.h"

#include "./Token.h"
#include "./Error.h"

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
		std::vector<std::string> lines;
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
				pos,
				pos - numbers.size(),
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
				pos - string.size(),
				pos,
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
		Lexer(std::string f) {
			text = fs::readFile(f.c_str());
			lines = fs::getLines(f.c_str());
			advance();
		};
		bool handleError(Error* e) {
			std::string msg = e->err();
			if(e->type == ErrorType::CHAR) {
				//
			}
		}
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

				bool isString = false;

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
					isString = true;
				}

				// STRINGS
				std::vector<char> string;
				bool isChar = false;
				bool stillIn = true;
				bool isEscaped = false;
				bool pt = false;
				int sl = 0;
				if(getQuote(current_char) == 0) {} else {
					if(current_char == '\'') {
						isChar = true;
					}
					advance();

					while(stillIn) {
						if(getQuote(current_char) == 0) {
							if(current_char == '\\') {
								isEscaped = !isEscaped;
							}
							string.push_back(current_char);
							sl++;
						} else {
							if(isChar) {
								if(getQuote(current_char) == 2) {
									if(isEscaped == true) {
										string.push_back(current_char);
										sl++;
										isEscaped = false;
									} else {
										stillIn = false;
										pt = true;
									}
								}
							} else {
								if(getQuote(current_char) == 1) {
									if(isEscaped == true) {
										string.push_back(current_char);
										sl++;
										isEscaped = false;
									} else {
										stillIn = false;
										pt = true;
									}
								}
							}
						}
						
						advance();
					}
				}

				if(pt) {
					tokens.push_back(makeString(string, isChar));
					if(sl > 1 && isChar) {
						Error e("Char exceeds one-character maximum.");
						bool shouldClose = handleError(&e);
						if(shouldClose) break;
					}
					continue;
				}

				// MATH TOKENS
				if(current_char == '=') 
					tokens.push_back(TokenStruct {pos-1, pos, nullptr, true, TT::EQUAL});
				else if(current_char == '+')
					tokens.push_back(TokenStruct {pos-1, pos, nullptr, true, TT::PLUS});
				else if(current_char == '-') 
					tokens.push_back(TokenStruct {pos-1, pos, nullptr, true, TT::MINUS});
				else if(current_char == '*')
					tokens.push_back(TokenStruct {pos-1, pos, nullptr, true, TT::MUL});
				else if(current_char == '/')
					tokens.push_back(TokenStruct {pos-1, pos, nullptr, true, TT::DIV});
				else if(current_char == '(')
					tokens.push_back(TokenStruct {pos-1, pos, nullptr, true, TT::LPAREN});
				advance();
			}
			return tokens;
		}
};
