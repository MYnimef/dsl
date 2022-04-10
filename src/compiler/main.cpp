#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Compiler.h"
#include "ExceptionParser.h"

int main() {
    std::cout <<
    std::endl <<
    "\033[1;32m" <<
    " ____  ____  _       _             __  ____   __     _                 __ \n"
    "|  _ \\/ ___|| |     | |__  _   _  |  \\/  \\ \\ / / __ (_)_ __ ___   ___ / _|\n"
    "| | | \\___ \\| |     | '_ \\| | | | | |\\/| |\\ V / '_ \\| | '_ ` _ \\ / _ \\ |_ \n"
    "| |_| |___) | |___  | |_) | |_| | | |  | | | || | | | | | | | | |  __/  _|\n"
    "|____/|____/|_____| |_.__/ \\__, | |_|  |_| |_||_| |_|_|_| |_| |_|\\___|_|  \n"
    "                           |___/                                          \n"
    "\033[0m" <<
    std::endl;

    clock_t start = clock();

    try {
        Lexer lexer;
        lexer.scanFile("main.dsl");

        for (const auto& token: lexer.getTokens()) {
            if (token.getType() != SEMICOLON) {
                std::cout << token.toString() << std::endl;
            }
        }

        Parser parser("main");
        parser.addTokens(lexer.getTokens());

        std::cout << std::endl << parser.getTree()->toString() << std::endl;

        Compiler compiler;
        compiler.execute(parser.getTree());

        std::cout << std::endl;
        for (const auto& var: *compiler.getVariables()) {
            std::cout << std::endl << var.first + " = " + var.second->getString();
        }
        std::cout << std::endl;
    } catch (const std::exception& ex) {
        std::cout << std::endl << "\033[1;31m" << ex.what() << "\033[0m";
    }

    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    std::cout << std::endl << "\033[1;32m" << "Program compiled in " << elapsed << " seconds"  << "\033[0m" << std::endl;

    return 0;
}
