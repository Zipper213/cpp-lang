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

        Grammar(std::vector<TokenStruct>* t) {
            tokens = t;
        };
        ~Grammar() {
            if(tokens == nullptr) return;
            tokens->clear();
            std::cout << "\n\nEXITED GRAMMAR PROGRAM\n\n" << std::endl;
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

        void prepare(std::string file) {
            std::cout << file << std::endl;
            if(tokens == nullptr) {
                std::cout << "Tokens is nullptr" << std::endl;
            };
            gf = file;
            gl = fs::getLines(file.c_str());
            for(std::string s : gl) std::cout << s << std::endl;
            if(gl.size() < 1) {
                std::cout << "File is Empty s: " << gl.size() << std::endl;
                return;
            };
            std::cout << "Grammar File not Empty" << std::endl;
            for(int i = 0; i < gl.size(); i++) {
                std::cout << "GL Line " << i << std::endl;
                std::string line = gl[i];
                int inc = 3;
                if(gl.size() >= i+inc) {
                    std::string name = gl[i];
                    std::string patt = gl[i+1];
                    std::string clos = gl[i+2];
                    std::cout << "Line " << i << " {" << std::endl;
                    std::cout << '\t' << "name: " << name << std::endl;
                    std::cout << '\t' << "patt: " << patt << std::endl;
                    std::cout << '\t' << "clos: " << clos << std::endl;
                    std::cout << "};" << std::endl;
                    i += inc;
                }
            }
        };

        void parse() {
            if(tokens == nullptr);
            // 
        };

};