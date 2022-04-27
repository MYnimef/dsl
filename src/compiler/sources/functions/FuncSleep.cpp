//
// Created by Ivan Markov on 27.04.2022.
//

#include <chrono>
#include <thread>
#include "FuncSleep.h"

FuncSleep::FuncSleep(const std::list<std::string> &args):
ExpFuncCustom(args) {}

FuncSleep::~FuncSleep() = default;

void FuncSleep::action(const std::map<std::string, Var*>& params, std::stack<Var*>& stack) const {
    for (const auto& name: funcArgs) {
        std::this_thread::sleep_for(std::chrono::milliseconds(params.find(name)->second->getInteger()));
    }
}

std::string FuncSleep::toString() const {
    return "sleep";
}
