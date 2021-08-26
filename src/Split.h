#include <iostream>
#include <string>
#include <vector>
#include <functional>

std::vector<std::string> split(std::string str, std::string del) {
    std::vector<std::string> list;
    
    std::size_t loc = str.find(del);
    while(loc != std::string::npos) {
        std::string sec = str.substr(0, loc);
        list.push_back(sec);
        str.erase(loc + ((size_t) del.length()));
        
        loc = str.find(del);
    }
    
    return list;
};
std::vector<std::string> split2(std::string str, std::string del) {
    
    int pos = 0;
    char cc = str[pos];
    
    std::function<void()> advance = [&]() {
        pos++;
        cc = str[pos];
    };
    
    std::vector<std::string> res;
    
    std::string s = "";
    int sp = 0;
    while(pos < str.length()) {
        bool ir = false;
        s += cc;
        
        while((sp < del.length())) {
            ir = true;
            if(del[sp] == str[pos + sp]) {
                break;
            }
            sp++;
        }
        if(ir) {
            pos += del.length();
            cc = str[pos];
            res.push_back(s);
            sp = 0;
            s = "";
        }
        advance();
    };
    
    return res;
    
};

int main() {
    std::string str = "hello, world";
    std::string del = ", ";
    std::vector<std::string> splt = split2(str, del);
    std::cout << std::endl;
    for(std::string s : splt) {
        std::cout << ">> " << s << std::endl;
    }
}