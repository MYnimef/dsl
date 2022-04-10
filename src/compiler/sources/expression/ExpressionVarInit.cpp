//
// Created by Ivan Markov on 07.04.2022.
//

#include "ExpressionVarInit.h"

ExpressionVarInit::ExpressionVarInit(const std::string &value):
id(value) {
    type = EXP_VAR_INITIALIZATION;
}

void ExpressionVarInit::action(const CompilerArgs& args) const {
    args.stackVariablesId.push(id);
}

std::string ExpressionVarInit::toString() const {
    return id;
}
