//
// Created by Ivan Markov on 05.03.2022.
//

#pragma once

#include <string>
#include <list>

enum TokenType {
    DECREMENT_OP,
    INCREMENT_OP,
    STRING,
    INT_DIGIT,
    DOUBLE_DIGIT,
    ID,
    BOOL,
    FUNC_KW,
    IF_KW,
    ELSE_KW,
    WHILE_KW,
    FOR_KW,
    L_BRACKET,
    R_BRACKET,
    L_BRACE,
    R_BRACE,
    ASSIGN_OP,
    ASSIGN_SUM_OP,
    ASSIGN_SUB_OP,
    ASSIGN_MULT_OP,
    ASSIGN_DIV_OP,
    SUM_OP,
    SUB_OP,
    MULT_OP,
    DIV_OP,
    OR_OP,
    AND_OP,
    GREATER_OP,
    SMALLER_OP,
    GREATER_OR_EQUAL_OP,
    SMALLER_OR_EQUAL_OP,
    EQUAL_OP,
    COMMA,
    SEMICOLON,
};

class Token final {
private:
    TokenType type;
    std::string value;

public:
    Token(const TokenType&, const std::string&);
    ~Token();
    Token(const Token&);

    [[nodiscard]] TokenType getType() const;
    [[nodiscard]] std::string getValue() const;

    [[nodiscard]] std::string toString() const;
    [[nodiscard]] std::string typeToString() const;

    [[nodiscard]] bool isOperator() const;
    [[nodiscard]] bool isKeyWord() const;
};
