//
// Created by Ivan Markov on 06.03.2022.
//

#pragma once

#include <map>
#include <list>
#include <stack>
#include <regex>
#include "Token.h"
#include "Expression.h"
#include "Node.h"

class Parser final {
private:
    enum GrammarType {
        GR_CODE_BLOCK,
        GR_FUNC,
        GR_VAR_ASSIGNMENT,
        GR_VAR_INCREMENT_DECREMENT,
        GR_IF,
        GR_LOOP_WHILE,
        GR_LOOP_FOR,
        GR_FUNC_DEFINITION,
        };

    const std::map<GrammarType, std::regex> grammatics;
    Node* tree;
    std::map<std::string, Node*> functions;

    void addTokensLine(std::list<Token>&);
    void generateExpression(std::list<Token>&);
    GrammarType checkGrammar(std::list<Token>&);

    void parseAssignment(std::list<Token>&);
    void parseIncrementDecrement(std::list<Token>&);
    std::list<Expression*> parseOperations(std::list<Token>&);
    void subOperations(std::list<Expression*>& expressions, std::stack<Token>& stack, bool bracketsOver);
    void parseFuncDefinition(std::list<Token>&);
    void parseIf(std::list<Token>&);

    std::list<Expression*> toPostfix(std::list<Expression*>&);
    static short operatorPriority(const ExpressionType& type);
    Node* addNodeExpr(const std::list<Expression*>&);

public:
    explicit Parser(const std::string& name);
    explicit Parser(const std::map<GrammarType, std::regex>&);
    ~Parser();

    void addTokens(const std::list<Token>&);
    Node* getTree();
};