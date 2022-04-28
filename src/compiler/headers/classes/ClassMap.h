//
// Created by Ivan Markov on 29.04.2022.
//

#pragma once


#include "VarCustom.h"

class ClassMap final: VarCustom {
public:
    ClassMap();
    ~ClassMap();

    [[nodiscard]] explicit operator std::string() const override;
};
