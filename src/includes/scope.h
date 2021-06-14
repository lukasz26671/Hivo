#pragma once
#include <iostream>
#include "AST.h"

namespace Hivo {

	typedef struct SCOPE_STRUCT
	{
		std::vector<AST*> variableDefinitions;
		size_t variableDefinitionsSize = 0;

		std::vector<AST*> functionDefinitions;
		size_t functionDefinitionsSize = 0;

	} Scope;
	AST* addFunctionDefinition(Scope* scope, AST* fdef);
	AST* addVariableDefinition(Scope* scope, AST* vdef);

	AST* getFunctionDefinition(Scope* scope, const std::string& fname);
	AST* getVariableDefinition(Scope* scope, const std::string& vname);
}