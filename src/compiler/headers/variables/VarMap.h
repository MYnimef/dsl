//
// Created by Ivan Markov on 27.04.2022.
//

#pragma once

#include <map>
#include "Var.h"

class VarMap final: public Var {
private:
    const std::map<Var*, Var*> value;

public:
    explicit VarMap(const int& lineNum, const std::map<Var*, Var*>& value);

    Var* operator + (const Var& second) const override;
    Var* operator - (const Var& second) const override;
    Var* operator * (const Var& second) const override;
    Var* operator / (const Var& second) const override;

    [[nodiscard]] explicit operator std::string          () const override;

    [[nodiscard]] Var* copy(const int& lineNum) const override;
};
