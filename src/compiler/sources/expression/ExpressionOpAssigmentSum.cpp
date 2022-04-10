//
// Created by Ivan Markov on 10.04.2022.
//

#include "ExpressionOpAssigmentSum.h"

ExpressionOpAssignmentSum::ExpressionOpAssignmentSum() {
    type = EXP_OP_ASSIGNMENT_SUM;
}

void ExpressionOpAssignmentSum::action(const CompilerArgs &args) const {
    auto val = args.stack.top();
    args.stack.pop();
    auto id = args.stackVariablesId.top();
    args.stackVariablesId.pop();

    for (auto scope: args.variablesGlobal) {
        auto it = scope->find(id);
        if (it != scope->end()) {
            auto var = it->second;
            scope->insert_or_assign(id, *var + *val);
            delete var;
            delete val;
            return;
        }
    }

    auto it = args.variables->find(id);
    if (it != args.variables->end()) {
        auto var = it->second;
        args.variables->insert_or_assign(id, *var + *val);
        delete var;
        delete val;
    } else {
        throw std::overflow_error("usage of undeclared var");
    }
}

std::string ExpressionOpAssignmentSum::toString() const {
    return "+=";
}
