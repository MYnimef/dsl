//
// Created by Ivan Markov on 05.04.2022.
//

#include "Expression.h"

Expression::Expression() {

}

Expression::~Expression() {

}

ExpressionType Expression::getType() const {
    return type;
}

bool Expression::isOperator() const {
    return (
            type == EXP_OP_ASSIGNMENT ||
            type == EXP_OP_ASSIGNMENT_SUM ||
            type == EXP_OP_ASSIGNMENT_SUB ||
            type == EXP_OP_ASSIGNMENT_MULT ||
            type == EXP_OP_ASSIGNMENT_DIV ||
            type == EXP_OP_SUM ||
            type == EXP_OP_SUBTRACTION ||
            type == EXP_OP_MULTIPLICATION ||
            type == EXP_OP_DIVISION ||
            type == EXP_OP_EQUAL ||
            type == EXP_OP_NOT_EQUAL ||
            type == EXP_OP_GREATER_OR_EQUAL ||
            type == EXP_OP_SMALLER_OR_EQUAL ||
            type == EXP_OP_SMALLER ||
            type == EXP_OP_GREATER ||
            type == EXP_LOGICAL_AND ||
            type == EXP_LOGICAL_OR
    );
}
