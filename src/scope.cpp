#include "includes/scope.h";
#include "includes/AST.h";

namespace Hivo
{
	AST* addFunctionDefinition(Scope* scope, AST* fdef)
	{
		scope->functionDefinitionsSize++;
		
		scope->functionDefinitions.push_back(fdef);

		return fdef;
	}
	AST* addVariableDefinition(Scope* scope, AST* vdef)
	{
		scope->variableDefinitionsSize++;
		scope->variableDefinitions.push_back(vdef);

		return vdef;
	}
	AST* getFunctionDefinition(Scope* scope, const std::string& fname)
	{
		for (auto const& fdef : scope->functionDefinitions)
		{
			if (fdef->functionName == fname)
				return fdef;
		}
		return nullptr;

	}
	AST* getVariableDefinition(Scope* scope, const std::string& vname)
	{
		for (auto const& vdef : scope->variableDefinitions)
		{
			if (vdef->variableDefinitionVariableName == vname)
				return vdef;
		}
		return nullptr;
	}
}