//
// Created by Ivan Markov on 29.04.2022.
//

#include "ClassMap.h"
#include "VarList.h"

ClassMap::ClassMap():
VarCustom(
        0,
        "map",
        {
                { "keys",   new VarList( 0, {} ) },
                { "values", new VarList( 0, {} ) },
        }
        ) {}

ClassMap::~ClassMap() = default;

ClassMap::operator std::string() const {
    return VarCustom::operator std::string();
}
