//
// Created by Ivan Markov on 07.04.2022.
//

#include "ExpressionOpAssignment.h"

ExpressionOpAssignment::ExpressionOpAssignment() {
    type = EXP_OP_ASSIGNMENT;
}

void ExpressionOpAssignment::action(const CompilerArgs& args) const {
    auto val = args.stack.top();
    args.stack.pop();
    auto id = args.stackVariablesId.top();
    args.stackVariablesId.pop();

    for (auto scope: args.variablesGlobal) {
        auto it = scope->find(id);
        if (it != scope->end()) {
            auto var = it->second;
            scope->insert_or_assign(id, val);
            delete var;
            return;
        }
    }

    auto it = args.variables->find(id);
    if (it != args.variables->end()) {
        auto var = it->second;
        args.variables->insert_or_assign(id, val);
        delete var;
    } else {
        args.variables->insert_or_assign(id, val);
    }
}

std::string ExpressionOpAssignment::toString() const {
    return "=";
}
