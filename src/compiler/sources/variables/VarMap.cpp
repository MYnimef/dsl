//
// Created by Ivan Markov on 27.04.2022.
//

#include "VarMap.h"

VarMap::VarMap(const int &lineNum, const std::map<Var*, Var*>& value):
Var(lineNum, MAP_VAR),
value(value) {}

Var* VarMap::operator + (const Var& second) const {
    return super::operator + (second);
}

Var* VarMap::operator - (const Var& second) const {
    return super::operator - (second);
}

Var* VarMap::operator * (const Var& second) const {
    return super::operator * (second);
}

Var* VarMap::operator / (const Var& second) const {
    return super::operator / (second);
}

VarMap::operator std::string() const {
    std::string result = "{";
    if (!value.empty()) {
        for (auto element: value) {
            result += " { " + (std::string) *element.first + " : " + (std::string) *element.second + " },";
        }
        result.pop_back();
    }
    result += " }";

    return result;
}

Var *VarMap::copy(const int& lineNum) const {
    return new VarMap(lineNum, value);
}
