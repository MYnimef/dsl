cmake_minimum_required(VERSION 3.21)
project(dsl)

set(CMAKE_CXX_STANDARD 23)

include_directories(src/compiler/headers)
include_directories(src/compiler/headers/expression)
include_directories(src/compiler/headers/variable)

add_executable(
        dsl

        src/compiler/main.cpp

        src/compiler/headers/Token.h
        src/compiler/sources/Token.cpp

        src/compiler/headers/Lexer.h
        src/compiler/sources/Lexer.cpp

        src/compiler/headers/Parser.h
        src/compiler/sources/Parser.cpp

        src/compiler/headers/Node.h
        src/compiler/sources/Node.cpp

        src/compiler/headers/Compiler.h
        src/compiler/sources/Compiler.cpp

        src/compiler/headers/CompilerArgs.h
        src/compiler/sources/CompilerArgs.cpp

        src/compiler/headers/variable/Variable.h
        src/compiler/sources/variable/Variable.cpp

        src/compiler/headers/variable/VariableInteger.h
        src/compiler/sources/variable/VariableInteger.cpp

        src/compiler/headers/variable/VariableDouble.h
        src/compiler/sources/variable/VariableDouble.cpp

        src/compiler/headers/variable/VariableString.h
        src/compiler/sources/variable/VariableString.cpp

        src/compiler/headers/variable/VariableBool.h
        src/compiler/sources/variable/VariableBool.cpp

        src/compiler/headers/variable/VariableList.h

        src/compiler/headers/expression/Expression.h
        src/compiler/sources/expression/Expression.cpp

        src/compiler/headers/expression/ExpressionValInteger.h
        src/compiler/sources/expression/ExpressionValInteger.cpp

        src/compiler/headers/expression/ExpressionValString.h
        src/compiler/sources/expression/ExpressionValString.cpp

        src/compiler/headers/expression/ExpressionValDouble.h
        src/compiler/sources/expression/ExpressionValDouble.cpp

        src/compiler/headers/expression/ExpressionOpSum.h
        src/compiler/sources/expression/ExpressionOpSum.cpp

        src/compiler/headers/expression/ExpressionOpSub.h
        src/compiler/sources/expression/ExpressionOpSub.cpp

        src/compiler/headers/expression/ExpressionOpMult.h
        src/compiler/sources/expression/ExpressionOpMult.cpp

        src/compiler/headers/expression/ExpressionOpDiv.h
        src/compiler/sources/expression/ExpressionOpDiv.cpp

        src/compiler/headers/expression/ExpressionVarInit.h
        src/compiler/sources/expression/ExpressionVarInit.cpp

        src/compiler/headers/expression/ExpressionVarCall.h
        src/compiler/sources/expression/ExpressionVarCall.cpp

        src/compiler/headers/expression/ExpressionOpAssignment.h
        src/compiler/sources/expression/ExpressionOpAssignment.cpp

        src/compiler/headers/expression/ExpressionFunctionCall.h
        src/compiler/sources/expression/ExpressionFunctionCall.cpp

        src/compiler/headers/expression/ExpressionValBool.h
        src/compiler/sources/expression/ExpressionValBool.cpp

        src/compiler/headers/expression/ExpressionIf.h
        src/compiler/sources/expression/ExpressionIf.cpp

        src/compiler/headers/expression/ExpressionOpSmaller.h
        src/compiler/sources/expression/ExpressionOpSmaller.cpp

        src/compiler/headers/expression/ExpressionOpSmallerOrEqual.h
        src/compiler/sources/expression/ExpressionOpSmallerOrEqual.cpp

        src/compiler/headers/expression/ExpressionOpGreater.h
        src/compiler/sources/expression/ExpressionOpGreater.cpp

        src/compiler/headers/expression/ExpressionOpGreaterOrEqual.h
        src/compiler/sources/expression/ExpressionOpGreaterOrEqual.cpp

        src/compiler/headers/expression/ExpressionOpEqual.h
        src/compiler/sources/expression/ExpressionOpEqual.cpp

        src/compiler/headers/expression/ExpressionOpNotEqual.h
        src/compiler/sources/expression/ExpressionOpNotEqual.cpp

        src/compiler/headers/expression/ExpressionOpLogicalOr.h
        src/compiler/sources/expression/ExpressionOpLogicalOr.cpp

        src/compiler/headers/expression/ExpressionOpLogicalAnd.h
        src/compiler/sources/expression/ExpressionOpLogicalAnd.cpp
        src/compiler/headers/expression/ExpressionOpAssigmentSum.h src/compiler/headers/expression/ExpressionOpAssigmentSub.h src/compiler/headers/expression/ExpressionOpAssigmentMult.h src/compiler/headers/expression/ExpressionOpAssigmentDiv.h src/compiler/sources/expression/ExpressionOpAssigmentSum.cpp src/compiler/sources/expression/ExpressionOpAssigmentSub.cpp src/compiler/sources/expression/ExpressionOpAssigmentMult.cpp src/compiler/sources/expression/ExpressionOpAssigmentDiv.cpp)
