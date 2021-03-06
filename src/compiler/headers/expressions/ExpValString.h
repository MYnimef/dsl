//
// Created by Ivan Markov on 07.04.2022.
//

#pragma once


#include <string>
#include "Exp.h"

class ExpValString final: public Exp {
private:
    const std::string value;

public:
    explicit ExpValString(const int& lineNum, const std::string& value);

    void action(const InterpreterArgs& args) const override;

    [[nodiscard]] std::string toString() const override;
};
