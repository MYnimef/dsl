//
// Created by Ivan Markov on 06.03.2022.
//

#include <stack>
#include <iostream>
#include <regex>
#include "Parser.h"

Parser::Parser(const std::string& name):
grammatics({
    { GR_LET_INITIALIZATION, std::regex(R"(letid=([\(]*((id\(.*\))|(id)|(i)|(d)|(s))[\)]*[\+\-\*\/])*[\(]*((id\(.*\))|(id)|(i)|(d)|(s))[\)]*)") },
    { GR_VAR_INITIALIZATION, std::regex(R"(varid=([\(]*((id\(.*\))|(id)|(i)|(d)|(s))[\)]*[\+\-\*\/])*[\(]*((id\(.*\))|(id)|(i)|(d)|(s))[\)]*)") },
    { GR_VAR_ASSIGNMENT,     std::regex(R"(id=([\(]*((id\(.*\))|(id)|(i)|(d)|(s))[\)]*[\+\-\*\/])*[\(]*((id\(.*\))|(id)|(i)|(d)|(s))[\)]*)") },
    { GR_FUNC,               std::regex(R"(id\(.*\))") },
    { GR_IF,                 std::regex(R"(if\(.*\)\{.*\}(elseif\(.*\)\{.*\})*(else\(.*\)\{.*\})?)") },
    { GR_LOOP_WHILE,         std::regex(R"(while\(.*\)\{.*\})") },
    { GR_LOOP_FOR,           std::regex(R"(for\(.*\)\{.*\})") },
    { GR_FUNC_DEFINITION,    std::regex(R"(funcid\(.*\)\{.*\})") },
    { GR_CODE_BLOCK,         std::regex(R"(\{.*\})") }
}) {
    tree = new Node(Expression(EXP_FUNC, "main"));
}

Parser::~Parser() {

}

void Parser::addTokens(const std::list<Token*>& tokens) {
    std::list<Token*> tokensLine;

    int openedBrackets = 0;
    int openedBraces = 0;

    bool semicolon = false;
    bool op = false;

    for (const auto& token: tokens) {
        const auto& type = token->getType();

        if (type == SEMICOLON) {
            if (openedBraces == 0) {
                if (openedBrackets == 0) {
                    semicolon = true;
                }
            } else {
                tokensLine.push_back(token);
            }
        } else {
            if ((type == ID || token->isKeyWord()) && !op) {
                if (semicolon) {
                    addTokensLine(tokensLine);
                    tokensLine.clear();
                }
            } else if (token->isOperator()) {
                op = true;
            } else if (type == L_BRACKET) {
                openedBrackets++;
            } else if (type == R_BRACKET) {
                openedBrackets--;
            } else if (type == L_BRACE) {
                openedBraces++;
            } else if (type == R_BRACE) {
                openedBraces--;
            } else {
                op = false;
            }

            semicolon = false;
            tokensLine.push_back(token);
        }
    }

    addTokensLine(tokensLine);
    tokensLine.clear();
}

void Parser::addTokensLine(std::list<Token*>& tokens) {
    std::cout << std::endl;
    for (auto i: tokens) {
        std::cout << i->getValue() << " ";
    }

    auto* exp = generateExpression(tokens);
    auto* postfix = toPostfix(*exp);
    delete exp;
    tree->addChildBack(addNodeExpr(*postfix));
    delete postfix;
}

std::list<Expression*>* Parser::generateExpression(std::list<Token*>& tokens) {
    GrammarType type = checkGrammar(tokens);

    switch (type) {
        case GR_LET_INITIALIZATION:
            tokens.pop_front();
            return parseAssignment(EXP_LET_INITIALIZATION, tokens);
        case GR_VAR_INITIALIZATION:
            tokens.pop_front();
        case GR_VAR_ASSIGNMENT:
            return parseAssignment(EXP_VAR_INITIALIZATION, tokens);
        case GR_FUNC:
            return nullptr;
        case GR_IF:
            return nullptr;
        case GR_LOOP_WHILE:
            return nullptr;
        case GR_LOOP_FOR:
            return nullptr;
        case GR_FUNC_DEFINITION:
            return nullptr;
        case GR_CODE_BLOCK:
            return nullptr;
    }
}

Parser::GrammarType Parser::checkGrammar(std::list<Token*>& tokens) {
    std::string comp;
    for (const auto &token: tokens) {
        comp += token->typeToString();
    }

    GrammarType type;
    bool didFind = false;

    for (const auto &grammar: grammatics) {
        if (std::regex_match(comp, grammar.second)) {
            type = grammar.first;
            didFind = true;
        }
    }

    if (didFind) {
        return type;
    } else {
        throw std::overflow_error("wrong grammar");
    }
}

std::list<Expression*>* Parser::parseAssignment(ExpressionType type, std::list<Token*>& tokens) {
    auto* expressions = new std::list<Expression*>;

    expressions->push_back(new Expression(type, tokens.front()->getValue()));
    tokens.pop_front();
    expressions->push_back(new Expression(EXP_OP_ASSIGNMENT, tokens.front()->getValue()));
    tokens.pop_front();

    auto* exp = parseOperations(tokens);
    expressions->splice(expressions->end(), *exp);
    delete exp;

    return expressions;
}

std::list<Expression*>* Parser::parseOperations(std::list<Token*>& tokens) {
    auto* expressions = new std::list<Expression*>;

    std::stack<Token*> stack;
    int brackets = 0;
    bool bracketsOver = false;

    for (const auto &token: tokens) {
        const auto& type = token->getType();

        if (token->isOperator() && brackets == 0) {
            subOperations(expressions, stack, bracketsOver);

            if (type == SUM_OP) {
                expressions->push_back(new Expression(EXP_OP_SUM, token->getValue()));
            } else if (type == SUB_OP) {
                expressions->push_back(new Expression(EXP_OP_SUBTRACTION, token->getValue()));
            } else if (type == MULT_OP) {
                expressions->push_back(new Expression(EXP_OP_MULTIPLICATION, token->getValue()));
            } else {
                expressions->push_back(new Expression(EXP_OP_DIVISION, token->getValue()));
            }
        } else if (type == L_BRACKET) {
            if (brackets != 0) {
                stack.push(token);
            } else {
                expressions->push_back(new Expression(EXP_ID, "("));
            }
            brackets++;
        } else if (type == R_BRACKET) {
            brackets--;
            if (brackets != 0) {
                stack.push(token);
            } else {
                bracketsOver = true;
            }
        } else {
            stack.push(token);
        }
    }

    subOperations(expressions, stack, bracketsOver);
    tokens.clear();
    return expressions;
}

void Parser::subOperations(std::list<Expression*>* expressions, std::stack<Token*>& stack, bool bracketsOver) {
    std::list<Token*> localTokens;
    while (!stack.empty()) {
        localTokens.push_front(stack.top());
        stack.pop();
    }

    std::string localString;
    for (const auto& localToken: localTokens) {
        localString += localToken->typeToString();
    }

    if (localString == "id") {
        expressions->push_back(new Expression(EXP_ID, localTokens.front()->getValue()));
    } else if (localString == "i") {
        expressions->push_back(new Expression(EXP_INTEGER, localTokens.front()->getValue()));
    } else if (localString == "d") {
        expressions->push_back(new Expression(EXP_DOUBLE, localTokens.front()->getValue()));
    } else if (localString == "s") {
        expressions->push_back(new Expression(EXP_STRING, localTokens.front()->getValue()));
    } else if (std::regex_match(localString, std::regex(R"(id\(.*\))"))) {

    } else if (!localTokens.empty()) {
        auto* exp = parseOperations(localTokens);
        expressions->splice(expressions->end(), *exp);
        delete exp;

        if (bracketsOver) {
            expressions->push_back(new Expression(EXP_ID, ")"));
            bracketsOver = false;
        }
    }
}

std::list<Expression*>* Parser::toPostfix(std::list<Expression*>& expressions) {
    auto* postfix = new std::list<Expression*>;
    std::stack<Expression*> operators;

    for (const auto& expression: expressions) {
        const auto& val = expression->getValue();

        if (val == "(") {
            operators.push(expression);
        } else if (val == ")") {
            while (operators.top()->getValue() != "(") {
                postfix->push_back(operators.top());
                operators.pop();
            }

            auto& prev = operators.top();
            operators.pop();
            delete prev;
            delete expression;
        } else if (expression->isOperator()) {
            while (!operators.empty() && operatorPriority(val) <= operatorPriority(operators.top()->getValue())) {
                postfix->push_back(operators.top());
                operators.pop();
            }
            operators.push(expression);
        } else {
            postfix->push_back(expression);
        }
    }

    while (!operators.empty()) {
        postfix->push_back(operators.top());
        operators.pop();
    }

    return postfix;
}

short Parser::operatorPriority(const std::string& op) {
    if (op == "*" || op == "/") {
        return 4;
    } else if (op == "+" || op == "-") {
        return 3;
    } else if (op == "=" || op == "==") {
        return 2;
    } else if (op == "&&") {
        return 1;
    } else if (op == "||") {
        return 0;
    } else {
        return -1;
    }
}

Node* Parser::addNodeExpr(const std::list<Expression*>& postfix) {
    std::cout << std::endl;
    for (auto i: postfix) {
        std::cout << i->getValue() << " ";
    }

    std::stack<Node*> st;

    for (auto exp: postfix) {
        Node* node = new Node(*exp);
        if (node->getToken().isOperator()) {
            node->addChildFront(st.top());
            st.pop();
            node->addChildFront(st.top());
            st.pop();
        }
        st.push(node);
    }

    Node* result = st.top();
    st.pop();

    return result;
}

Node *Parser::getTree() {
    return tree;
}
