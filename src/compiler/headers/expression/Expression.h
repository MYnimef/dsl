//
// Created by Ivan Markov on 05.04.2022.
//

#pragma once

#include "CompilerArgs.h"
#include "Variable.h"

enum ExpressionType {
    EXP_VAR_INITIALIZATION,

    EXP_ID,
    EXP_BOOL,
    EXP_INTEGER,
    EXP_DOUBLE,
    EXP_STRING,

    EXP_OP_MULTIPLICATION,
    EXP_OP_DIVISION,
    EXP_OP_SUM,
    EXP_OP_SUBTRACTION,
    EXP_OP_SMALLER,
    EXP_OP_SMALLER_OR_EQUAL,
    EXP_OP_GREATER,
    EXP_OP_GREATER_OR_EQUAL,
    EXP_OP_EQUAL,
    EXP_OP_NOT_EQUAL,
    EXP_LOGICAL_AND,
    EXP_LOGICAL_OR,
    EXP_OP_ASSIGNMENT,
    EXP_OP_ASSIGNMENT_SUM,
    EXP_OP_ASSIGNMENT_SUB,
    EXP_OP_ASSIGNMENT_MULT,
    EXP_OP_ASSIGNMENT_DIV,

    EXP_IF,

    EXP_LOOP_WHILE,
    EXP_LOOP_FOR,

    EXP_FUNC,
    EXP_FUNC_DEFINITION,

    EXP_CODE_BLOCK,
    EXP_ADD_TO_LOCAL,
    EXP_GET_FROM_LOCAL,

    EXP_BRACKET_L,
    EXP_BRACKET_R,
};

class Expression {
protected:
    ExpressionType type;

public:
    Expression();
    virtual ~Expression();

    [[nodiscard]] ExpressionType getType() const;

    virtual void action(const CompilerArgs& args) const = 0;

    [[nodiscard]] bool isOperator() const;

    [[nodiscard]] virtual std::string toString() const = 0;
};

class ExpressionBracketL: public Expression {
public:
    ExpressionBracketL() {
        type = EXP_BRACKET_L;
    }

    void action(const CompilerArgs& args) const override {

    }

    [[nodiscard]] std::string toString() const override {
        return "(";
    }
};

class ExpressionBracketR: public Expression {
public:
    ExpressionBracketR() {
        type = EXP_BRACKET_R;
    }

    void action(const CompilerArgs& args) const override {

    }

    [[nodiscard]] std::string toString() const override {
        return ")";
    }
};
