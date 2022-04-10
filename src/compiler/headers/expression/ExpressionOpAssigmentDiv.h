//
// Created by Ivan Markov on 10.04.2022.
//

#pragma once

#include "Expression.h"

class ExpressionOpAssignmentDiv final: public Expression {
public:
    explicit ExpressionOpAssignmentDiv();

    void action(const CompilerArgs& args) const override;

    [[nodiscard]] std::string toString() const override;
};
