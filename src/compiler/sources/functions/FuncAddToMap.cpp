//
// Created by Ivan Markov on 28.04.2022.
//

#include "FuncAddToMap.h"
#include "VarMap.h"


FuncAddToMap::FuncAddToMap():
ExpFuncCustom({ "map", "key", "value" }) {}

FuncAddToMap::~FuncAddToMap() = default;

void FuncAddToMap::action(const std::map<std::string, Var*>& params, std::stack<Var*>& stack) const {
    const auto map   = params.find( "map"   )->second;
    const auto key   = params.find( "key"   )->second->copy(lineNum);
    const auto value = params.find( "value" )->second->copy(lineNum);

    auto result = (std::map<Var*, Var*>) *map;

    auto it = result.find(key);
    if (it == result.end()) {
        result.insert_or_assign(key, value);
        stack.push(new VarMap(0, result));
    }

}

std::string FuncAddToMap::toString() const {
    return "addToMap";
}
