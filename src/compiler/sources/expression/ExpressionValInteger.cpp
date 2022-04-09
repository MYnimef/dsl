//
// Created by Ivan Markov on 07.04.2022.
//

#include "ExpressionValInteger.h"
#include "VariableInteger.h"

ExpressionValInteger::ExpressionValInteger(const int value):
value(value) {
    type = EXP_INTEGER;
}

ExpressionValInteger::ExpressionValInteger(const std::string& value):
value(std::stoi(value)) {
    type = EXP_INTEGER;
}

void ExpressionValInteger::action(
        std::list<std::map<std::string, Variable*>*> variablesGlobal,
        std::map<std::string, Variable*>* variables,
        std::stack<std::string>& stackVariablesId,
        std::stack<Variable*>& stack
        ) const {

    stack.push(new VariableInteger(value));
}

std::string ExpressionValInteger::toString() const {
    return std::to_string(value);
}