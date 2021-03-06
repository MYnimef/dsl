//
// Created by Ivan Markov on 12.04.2022.
//

#pragma once


#include <string>
#include "Exp.h"

class ExpOpAssignVarFunc final: public Exp {
private:
    std::string id;

public:
    explicit ExpOpAssignVarFunc(const int& lineNum, const std::string& value);

    void action(const InterpreterArgs& args) const override;

    [[nodiscard]] std::string toString() const override;
};
