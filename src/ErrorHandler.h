#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#include <Lexer.h>

typedef struct {
    std::string message;

} EEntry;

class ErrorHandler {

    private:
        Lexer* attachedTo = nullptr;
        std::vector<EEntry> log;

    public:
        ErrorHandler() {};
        ~ErrorHandler() {
            // Save Log
        };

        bool Attach(Lexer* lexer) {
            attachedTo = lexer;

        }

};