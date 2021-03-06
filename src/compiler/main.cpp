#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include "ExcParser.h"
#include "ExpBlock.h"
#include "FuncPrint.h"
#include "FuncPrintln.h"
#include "FuncInput.h"
#include "FuncToInteger.h"
#include "FuncToBool.h"
#include "FuncToDouble.h"
#include "FuncToString.h"
#include "FuncToList.h"
#include "FuncSleep.h"
#include "FuncList.h"
#include "FuncMap.h"
#include "FuncClearConsole.h"
#include "FuncAddToMap.h"

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

    auto start = clock();

    auto application = new Node(new ExpBlock(0, "main"));
    auto functions = new std::map<std::string, Node*> {
            { "print1",    new Node( new FuncPrint        () ) },
            { "println1",  new Node( new FuncPrintln      () ) },
            { "input0",    new Node( new FuncInput        () ) },
            { "bool1",     new Node( new FuncToBool       () ) },
            { "int1",      new Node( new FuncToInteger    () ) },
            { "float1",    new Node( new FuncToDouble     () ) },
            { "string1",   new Node( new FuncToString     () ) },
            { "list0",     new Node( new FuncList         () ) },
            { "list1",     new Node( new FuncToList       () ) },
            { "map0",      new Node( new FuncMap          () ) },
            { "addToMap3", new Node( new FuncAddToMap     () ) },
            { "sleep1",    new Node( new FuncSleep        () ) },
            { "clc0",      new Node( new FuncClearConsole () ) },
    };

    try {
        Lexer lexer;
        lexer.scanFile("main.dsl");

        /*
        for (const auto& token: lexer.getTokens()) {
            if (token.getType() != SEMICOLON) {
                std::cout << token.toString() << std::endl;
            }
        }
        */

        Parser parser(application, functions);
        parser.addTokens(lexer.getTokens());

        //std::cout << std::endl << parser.getTree()->toString() << std::endl;

        Interpreter compiler(functions);
        compiler.execute(application);

        /*
        std::cout << std::endl;
        for (const auto& var: *compiler.getVariables()) {
            std::cout << std::endl << var.first + " = " + var.second->getString();
        }
        std::cout << std::endl;
        */
    } catch (const std::exception& ex) {
        std::cout << std::endl << "\033[1;31m" << ex.what() << "\033[0m";
    }

    delete application;
    for (const auto& func: *functions) {
        delete func.second;
    }
    delete functions;

    std::cout <<
    std::endl <<
    "\033[1;32m" <<
    "Program compiled in " <<
    (double) (clock() - start) / CLOCKS_PER_SEC <<
    " seconds"  << "\033[0m" <<
    std::endl;

    return 0;
}
