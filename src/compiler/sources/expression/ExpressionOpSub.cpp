//
// Created by Ivan Markov on 07.04.2022.
//

#include "ExpressionOpSub.h"

ExpressionOpSub::ExpressionOpSub() {
    type = EXP_OP_SUBTRACTION;
}

void ExpressionOpSub::action(
        std::list<std::map<std::string, Variable*>*> variablesGlobal,
        std::map<std::string, Variable*>* variables,
        std::stack<std::string>& stackVariablesId,
        std::stack<Variable*>& stack
        ) const {

    auto arg2 = stack.top();
    stack.pop();
    auto arg1 = stack.top();
    stack.pop();
    stack.push(*arg1 - *arg2);

    delete arg1;
    delete arg2;
}

std::string ExpressionOpSub::toString() const {
    return "-";
}
