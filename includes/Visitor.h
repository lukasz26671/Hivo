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

		std::vector<AST*> variableDefinitions;
		size_t variableDefinitionsSize = 0;

		std::vector<AST*> functionDeclarations;
		size_t functionDeclarationsSize = 0;

		AST* visit(AST* node);

		AST* visitVariableDefinition(AST* node);

		AST* visitVariable(AST* node);

		AST* visitString(AST* node);

		AST* visitFunctionCall(AST* node);

		AST* visitFuncionDeclaration(AST* node);

		AST* visitCompound(AST* node);


	};

}