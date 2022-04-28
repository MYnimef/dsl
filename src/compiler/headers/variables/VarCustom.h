//
// Created by Ivan Markov on 29.04.2022.
//

#pragma once

#include "Var.h"

class VarCustom: public Var {
private:
    const std::string name;
    const std::map<std::string, Var*> fields;

public:
    explicit VarCustom(const int& lineNum, const std::string& name, const std::map<std::string, Var*>& fields);

    [[nodiscard]] explicit operator std::string() const override;

    [[nodiscard]] Var* copy(const int& lineNum) const override;
};
