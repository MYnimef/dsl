//
// Created by Ivan Markov on 29.04.2022.
//

#include "VarCustom.h"

VarCustom::VarCustom(const int &lineNum, const std::string& name, const std::map<std::string, Var*>& fields):
Var(lineNum, MAP_VAR),
name(name),
fields(fields) {}

VarCustom::operator std::string() const {
    return std::string();
}

Var *VarCustom::copy(const int &lineNum) const {
    return new VarCustom(lineNum, name, fields);
}
