#pragma once

#include "./fs.h"
#include "./HashMap.h"

#include "./Token.h"

typedef struct {
    int num;
    TokenType type;
} GDyn;
typedef struct {
    std::string name;
    std::vector<GDyn> map;
} GInfo;

class Grammar {
    public:
        std::vector<TokenStruct>* tokens = nullptr;

        std::string gf;
        std::vector<std::string> gl;

        HashMap<std::pair<unsigned int, unsigned int>, GInfo> data;
        /*
            Structure
                HashMap<
                    Pair<unsigned int, unsigned int> - Pos<start, end>,
                    GInfo {
                        std::string name; -- Name of Grammar Instruction
                        std::vector<GDyn> map; -- Token List
                        GDyn {
                            int num; -- Index of Token in List
                            TokenType -- Type of Token
                        }
                    }
                > - Grammar Instructions HashMap 
        */

        Grammar(std::vector<TokenStruct>* t) {
            tokens = t;
        };
        ~Grammar() {
            if(tokens == nullptr) return;
            tokens->clear();
            std::cout << "\nEXITED GRAMMAR PROGRAM" << std::endl;
        };

        std::vector<TokenStruct> getTokensOnLine(std::vector<TokenStruct>* tl, int l) {
            int cc = 0;
            int ln = 0;
            for(int i = 0; i < l && tl->size() >= i; i++) {
                cc += gl[i].length();
                ln = i;
            }
            std::vector<TokenStruct> tks;
            for(int i = 0; i < tl->size(); i++) {
                if(!(gl.size() >= ln+1)) return {};
                int diff = tl->at(i).end - tl->at(i).start;
                if(diff > cc && diff < diff + (gl[ln+1].length())) {
                    tks.push_back(tl->at(i));
                }
            }
            return tks;
        }

        void prepare(std::vector<std::string> gl2) {
            if(tokens == nullptr) {
                std::cout << "Tokens is nullptr" << std::endl;
            };
            gl = gl2;
            if(gl.size() < 1) {
                std::cout << "File is Empty s: " << gl.size() << std::endl;
                return;
            };
            std::cout << "Grammar File not Empty" << std::endl;
            int i = 0;
            for(std::string s : gl) {
                if(s[0] == '\n') continue;
                std::cout << s << std::endl;
            }
        };

        void parse() {
            if(tokens == nullptr);
            // 
        };

};