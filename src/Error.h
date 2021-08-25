#pragma once

#include <iostream>

enum ErrorType {
    UNKNOWN = 0, CHAR,
};
const char* ErrorTypes[] = {
    "UNKNOWN", "CHAR"
};

const char* etts(ErrorType t) {
    return ErrorTypes[t];
}

class Error {

    public:
        ErrorType type;
        std::string message;

    public:
        Error(std::string m) {
            message = m;
            type = ErrorType::UNKNOWN;
            err();
        };
        Error(std::string m, ErrorType t) {
            message = m;
            type = t;
            err();
        };
        Error(ErrorType t) {
            message = "Unknown Error";
            type = t;
        };

        std::string err() {
            return std::string("\n\n[ERROR::" + std::string(etts(type)) + "] >> " + message + "\n\n");
        }

};
class DynamicError {};