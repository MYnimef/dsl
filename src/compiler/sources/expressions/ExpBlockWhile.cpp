//
// Created by Ivan Markov on 10.04.2022.
//

#include "ExpBlockWhile.h"
#include "Interpreter.h"

ExpBlockWhile::ExpBlockWhile(
        const int& lineNum,
        const Node* blockCondition,
        const Node* blockExecute,
        std::map<std::string, Node*>* functions
):
Exp(EXP_LOOP_WHILE, lineNum),
blockCondition(blockCondition),
blockExecute(blockExecute),
functions(functions) {}

ExpBlockWhile::~ExpBlockWhile() {
   delete blockCondition;
   delete blockExecute;
    for (const auto& func: *functions) {
        delete func.second;
    }
    delete functions;
}

void ExpBlockWhile::action(const InterpreterArgs& args) const {
    args.variablesGlobal.push_front(args.variables);

    Interpreter compilerCondition(args.functions, args.variablesGlobal);
    compilerCondition.executeChild(blockCondition);

    auto condition = compilerCondition.getStack().top();
    compilerCondition.getStack().pop();

    while ((bool) *condition) {
        args.functions.push_front(functions);

        Interpreter compilerExecute(args.functions, args.variablesGlobal);
        compilerExecute.execute(blockExecute);

        args.functions.pop_front();

        compilerCondition.executeChild(blockCondition);
        delete condition;
        condition = compilerCondition.getStack().top();
        compilerCondition.getStack().pop();
    }

    args.variablesGlobal.pop_front();
    delete condition;
}

std::string ExpBlockWhile::toString() const {
    return "while\n        " + blockCondition->toString(2) + "\n        execute " + blockExecute->toString(2);
}
