#pragma once
#include <iostream>
#include "AST.h"
#include "Parser.h";
namespace Hivo {


	class Visitor {

	public:
		Visitor();
		~Visitor();

		AST* previousNode;
		AST* prevPreviousNode;

		AST* visit(AST* node);

		AST* visitVariableDefinition(AST* node);

		AST* visitVariable(AST* node);

		AST* visitString(AST* node);

		AST* visitFunctionCall(AST* node);

		AST* visitFunctionDefinition(AST* node);

		AST* visitCompound(AST* node);


	};

}