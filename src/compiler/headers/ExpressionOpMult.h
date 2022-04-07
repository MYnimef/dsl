//
// Created by Ivan Markov on 07.04.2022.
//

#pragma once

#include "Expression.h"

class ExpressionOpMult final: public Expression {
public:
    explicit ExpressionOpMult();

    void action(
            std::map<std::string, Variable>& variables,
            std::stack<std::string>& stackVariablesId,
            std::stack<Variable>& stack
    ) const override;
};
