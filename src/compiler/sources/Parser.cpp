//
// Created by Ivan Markov on 06.03.2022.
//

#include <stack>
#include <iostream>
#include <regex>
#include "Parser.h"
#include "ExpressionValBool.h"
#include "ExpressionValInteger.h"
#include "ExpressionValDouble.h"
#include "ExpressionValString.h"
#include "ExpressionOpAssignment.h"
#include "ExpressionOpSum.h"
#include "ExpressionOpSub.h"
#include "ExpressionOpMult.h"
#include "ExpressionOpDiv.h"
#include "ExpressionVarInit.h"
#include "ExpressionVarCall.h"
#include "ExpressionFunctionCall.h"
#include "ExpressionIf.h"
#include "ExpressionOpLogicalAnd.h"
#include "ExpressionOpLogicalOr.h"
#include "ExpressionOpEqual.h"
#include "ExpressionOpGreaterOrEqual.h"
#include "ExpressionOpSmallerOrEqual.h"
#include "ExpressionOpGreater.h"
#include "ExpressionOpSmaller.h"
#include "ExpressionOpNotEqual.h"
#include "ExpressionOpAssigmentSum.h"
#include "ExpressionOpAssigmentSub.h"
#include "ExpressionOpAssigmentMult.h"
#include "ExpressionOpAssigmentDiv.h"

Parser::Parser(const std::string& name):
grammatics({
    { GR_CODE_BLOCK,              std::regex( R"(\{.*\})" )                                                                                            },
    { GR_FUNC,                    std::regex( R"(@\(.*\))" )                                                                                           },
    { GR_VAR_ASSIGNMENT,          std::regex( R"(@((=)|(\+=)|(\-=)|(\*=)|(\/=))(\-)?([\(]*((@\(.*\))|[@bids])[\)]*[\+\-\*\/<>GSE\|&])*[\(]*((@\(.*\))|[@bids])[\)]*)" )  },
    { GR_VAR_INCREMENT_DECREMENT, std::regex( R"(@[ID])" )                                                                                             },
    //{ GR_IF,                      std::regex( R"(if\(.*\)\{.*\}(elseif\(.*\)\{.*\})*(else\(.*\)\{.*\})?)" )                                    },
    { GR_IF,                      std::regex( R"(if\((\-)?([\(]*((@\(.*\))|[@bids])[\)]*[\+\-\*\/<>GSE\|&])*[\(]*((@\(.*\))|[@bids])[\)]*\)\{.*\})" )  },
    { GR_LOOP_WHILE,              std::regex( R"(while\(.*\)\{.*\})" )                                                                                 },
    { GR_LOOP_FOR,                std::regex( R"(for\(.*\)\{.*\})" )                                                                                   },
    { GR_FUNC_DEFINITION,         std::regex( R"(func@\((((@,)*(@))|((@)?))\)\{.*\})" )                                                                }
}) {
    tree = new Node(new ExpressionFunctionCall("main"));
}

Parser::Parser(const std::map<GrammarType, std::regex>& grammatics):
grammatics(grammatics) {
    tree = new Node(new ExpressionFunctionCall("main"));
}

Parser::~Parser() {
    //delete tree;
}

void Parser::addTokens(const std::list<Token>& tokens) {
    std::list<Token> tokensLine;

    int openedBrackets = 0;
    int openedBraces = 0;

    bool semicolon = false;
    bool op = false;

    for (const auto &token: tokens) {
        const auto &type = token.getType();

        if (type == SEMICOLON) {
            if (openedBraces == 0) {
                if (openedBrackets == 0) {
                    semicolon = true;
                }
            } else {
                tokensLine.push_back(token);
            }
        } else {
            if ((type == ID || token.isKeyWord()) && !op) {
                if (semicolon) {
                    if (!tokensLine.empty()) {
                        addTokensLine(tokensLine);
                        tokensLine.clear();
                    }
                }
            } else if (token.isOperator()) {
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

    if (!tokensLine.empty()) {
        addTokensLine(tokensLine);
        tokensLine.clear();
    }
}

void Parser::addTokensLine(std::list<Token>& tokens) {
    std::cout << std::endl;
    for (const auto& i: tokens) {
        std::cout << i.getValue() << " ";
    }

    generateExpression(tokens);
}

void Parser::generateExpression(std::list<Token>& tokens) {
    GrammarType type = checkGrammar(tokens);

    switch (type) {
        case GR_VAR_ASSIGNMENT:
            parseAssignment(tokens);
            break;
        case GR_VAR_INCREMENT_DECREMENT:
            parseIncrementDecrement(tokens);
            break;
        case GR_FUNC:
            break;
        case GR_IF:
            parseIf(tokens);
            break;
        case GR_LOOP_WHILE:
            break;
        case GR_LOOP_FOR:
            break;
        case GR_FUNC_DEFINITION:
            parseFuncDefinition(tokens);
            break;
        case GR_CODE_BLOCK:
            break;
    }
}

Parser::GrammarType Parser::checkGrammar(std::list<Token>& tokens) {
    std::string comp;
    for (const auto &token: tokens) {
        comp += token.typeToString();
    }
    std::cout << comp;

    for (const auto &grammar: grammatics) {
        if (std::regex_match(comp, grammar.second)) {
            return grammar.first;
        }
    }

    throw std::overflow_error("wrong grammar");
}

void Parser::parseAssignment(std::list<Token>& tokens) {
    std::list<Expression*> expressions;

    expressions.emplace_back(new ExpressionVarInit(tokens.front().getValue()));
    tokens.pop_front();

    auto op = tokens.front().getType();
    if (op == ASSIGN_OP) {
        expressions.emplace_back(new ExpressionOpAssignment());
    } else if (op == ASSIGN_SUM_OP) {
        expressions.emplace_back(new ExpressionOpAssignmentSum());
    } else if (op == ASSIGN_SUB_OP) {
        expressions.emplace_back(new ExpressionOpAssignmentSub());
    } else if (op == ASSIGN_MULT_OP) {
        expressions.emplace_back(new ExpressionOpAssignmentMult());
    } else if (op == ASSIGN_DIV_OP) {
        expressions.emplace_back(new ExpressionOpAssignmentDiv());
    }
    tokens.pop_front();

    if (tokens.front().getType() == SUB_OP) {
        tokens.push_front(Token(INT_DIGIT, "0"));
    }

    expressions.splice(expressions.end(), parseOperations(tokens));

    tree->addChildBack(addNodeExpr(toPostfix(expressions)));
}

void Parser::parseIncrementDecrement(std::list<Token>& tokens) {
    std::list<Expression*> expressions;

    std::string id = tokens.front().getValue();
    tokens.pop_front();
    auto op = tokens.front().getType();
    tokens.clear();

    expressions.emplace_back(new ExpressionVarInit(id));
    expressions.emplace_back(new ExpressionVarCall(id));
    expressions.emplace_back(new ExpressionValInteger(1));
    if (op == INCREMENT_OP) {
        expressions.emplace_back(new ExpressionOpSum());
    } else {
        expressions.emplace_back(new ExpressionOpSub());
    }
    expressions.emplace_back(new ExpressionOpAssignment());

    tree->addChildBack(addNodeExpr(expressions));
}

std::list<Expression*> Parser::parseOperations(std::list<Token>& tokens) {
    std::list<Expression*> expressions;

    std::stack<Token> stack;
    int brackets = 0;
    bool bracketsOver = false;

    for (const auto &token: tokens) {
        const auto& type = token.getType();

        if (token.isOperator() && brackets == 0) {
            subOperations(expressions, stack, bracketsOver);

            if (type == SUM_OP) {
                expressions.emplace_back(new ExpressionOpSum());
            } else if (type == SUB_OP) {
                expressions.emplace_back(new ExpressionOpSub());
            } else if (type == MULT_OP) {
                expressions.emplace_back(new ExpressionOpMult());
            } else if (type == DIV_OP) {
                expressions.emplace_back(new ExpressionOpDiv());
            } else if (type == AND_OP) {
                expressions.emplace_back(new ExpressionOpLogicalAnd());
            } else if (type == OR_OP) {
                expressions.emplace_back(new ExpressionOpLogicalOr());
            } else if (type == EQUAL_OP) {
                expressions.emplace_back(new ExpressionOpEqual());
            } else if (type == GREATER_OR_EQUAL_OP) {
                expressions.emplace_back(new ExpressionOpGreaterOrEqual());
            } else if (type == SMALLER_OR_EQUAL_OP) {
                expressions.emplace_back(new ExpressionOpSmallerOrEqual());
            } else if (type == GREATER_OP) {
                expressions.emplace_back(new ExpressionOpGreater());
            } else if (type == SMALLER_OP) {
                expressions.emplace_back(new ExpressionOpSmaller());
            } else {
                expressions.emplace_back(new ExpressionOpNotEqual());
            }
        } else if (type == L_BRACKET) {
            if (brackets != 0) {
                stack.push(token);
            } else {
                expressions.emplace_back(new ExpressionBracketL());
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

void Parser::subOperations(std::list<Expression*>& expressions, std::stack<Token>& stack, bool bracketsOver) {
    std::list<Token> localTokens;
    while (!stack.empty()) {
        localTokens.push_front(stack.top());
        stack.pop();
    }

    std::string localString;
    for (const auto& localToken: localTokens) {
        localString += localToken.typeToString();
    }

    if (localString == "@") {
        expressions.emplace_back(new ExpressionVarCall(localTokens.front().getValue()));
    } else if (localString == "b") {
        expressions.emplace_back(new ExpressionValBool(localTokens.front().getValue()));
    } else if (localString == "i") {
        expressions.emplace_back(new ExpressionValInteger(localTokens.front().getValue()));
    } else if (localString == "d") {
        expressions.emplace_back(new ExpressionValDouble(localTokens.front().getValue()));
    } else if (localString == "s") {
        expressions.emplace_back(new ExpressionValString(localTokens.front().getValue()));
    } else if (std::regex_match(localString, std::regex(R"(@\(.*\))"))) {

    } else if (!localTokens.empty()) {
        expressions.splice(expressions.end(), parseOperations(localTokens));

        if (bracketsOver) {
            expressions.emplace_back(new ExpressionBracketR());
        }
    }
}

//funcid\((((id,)*(id))|((id)+))\)\{.*\}
void Parser::parseFuncDefinition(std::list<Token>& tokens) {
    /*
    tokens.pop_front(); // remove func
    std::string funcName = tokens.front().getValue();
    tokens.pop_front(); // remove func name

    Node* node = new Node(expression(EXP_FUNC_DEFINITION, funcName));

    tokens.pop_front(); // remove (
    int amountOfArgs = 0;
    for (const auto& token: tokens) {
        if (token.getType() == R_BRACKET) {
            break;
        } else {
            node->addChildBack(new Node(expression(EXP_GET_FROM_LOCAL, token.getValue())));
            amountOfArgs++;
        }
    }
    funcName += std::to_string(amountOfArgs);

    for (int i = 0; i < amountOfArgs; i++) {
        tokens.pop_front();
    }

    tokens.pop_front(); // delete )
    tokens.pop_front(); // delete {
    tokens.pop_front(); // delete first ; (cuz generation)
    tokens.pop_back();  // delete }

    Parser parser(grammatics);
    parser.addTokens(tokens);
    node->addChildBack(parser.getTree());

    if (functions.count(funcName)) {
        throw std::overflow_error("attempt to re-declare function " + funcName);
    } else {
        functions.insert_or_assign(funcName, node);
    }
     */
}

//if\(b\)\{.*\}
void Parser::parseIf(std::list<Token>& tokens) {
    tokens.pop_front(); // remove if
    tokens.pop_front(); // remove (

    std::list<Token> localTokens;
    int amount = 0;
    for (const auto& token: tokens) {
        if (token.getType() != R_BRACKET) {
            localTokens.push_back(token);
            amount++;
        } else {
            break;
        }
    }

    for (int i = 0; i < amount; i++) {
        tokens.pop_front();
    }
    tokens.pop_front(); // remove )

    auto condition = parseOperations(localTokens);
    auto conditionNode = addNodeExpr(toPostfix(condition));

    tokens.pop_front(); // remove {
    tokens.pop_back();  // remove }

    Parser parser(grammatics);
    parser.addTokens(tokens);

    auto node = new Node(new ExpressionIf(parser.getTree()));
    node->addChildBack(conditionNode);

    tree->addChildBack(node);
}

std::list<Expression*> Parser::toPostfix(std::list<Expression*>& expressions) {
    std::list<Expression*> postfix;
    std::stack<Expression*> operators;

    for (auto* expression: expressions) {
        const auto& type = expression->getType();

        if (type == EXP_BRACKET_L) {
            operators.push(expression);
        } else if (type == EXP_BRACKET_R) {
            while (operators.top()->getType() != EXP_BRACKET_L) {
                postfix.push_back(operators.top());
                operators.pop();
            }

            auto prev = operators.top();
            operators.pop();
            delete prev;

            delete expression;
        } else if (expression->isOperator()) {
            while (!operators.empty() && operatorPriority(type) >= operatorPriority(operators.top()->getType())) {
                postfix.push_back(operators.top());
                operators.pop();
            }
            operators.push(expression);
        } else {
            postfix.push_back(expression);
        }
    }

    while (!operators.empty()) {
        postfix.push_back(operators.top());
        operators.pop();
    }

    return postfix;
}

short Parser::operatorPriority(const ExpressionType& type) {
    if (type == EXP_OP_MULTIPLICATION || type == EXP_OP_DIVISION) {
        return 0;
    } else if (type == EXP_OP_SUM || type == EXP_OP_SUBTRACTION) {
        return 1;
    } else if (type == EXP_OP_SMALLER || type == EXP_OP_SMALLER_OR_EQUAL || type == EXP_OP_GREATER || type == EXP_OP_GREATER_OR_EQUAL) {
        return 2;
    } else if (type == EXP_OP_EQUAL || type == EXP_OP_NOT_EQUAL) {
        return 3;
    } else if (type == EXP_LOGICAL_AND) {
        return 4;
    } else if (type == EXP_LOGICAL_OR) {
        return 5;
    } else { //type == EXP_OP_ASSIGNMENT
        return 6;
    }
}

Node* Parser::addNodeExpr(const std::list<Expression*>& postfix) {
    std::stack<Node*> st;

    for (const auto& exp: postfix) {
        Node* node = new Node(exp);
        if (node->getExpression()->isOperator()) {
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
