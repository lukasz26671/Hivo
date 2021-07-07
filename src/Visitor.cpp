#include <iostream>
#include <stdio.h>
#include "includes/Hivo.h"
namespace Hivo {

	Visitor::Visitor() { }
	Visitor::~Visitor() {}

	AST* Visitor::visit(AST* node)
	{
		this->prevPreviousNode = this->previousNode;
		this->previousNode = node;
		switch (node->type)
		{
		case AST_VARIABLE_DEFINITION:
			return this->visitVariableDefinition(node);
			break;
		case AST_VARIABLE:
			return this->visitVariable(node);
			break;
		case AST_FUNCTION_CALL:
			return this->visitFunctionCall(node);
			break;
		case AST_FUNCTION_DEFINITION:
			return this->visitFunctionDefinition(node);
			break;
		case AST_STRING:
			return this->visitString(node);
			break;
		case AST_COMPOUND:
			return this->visitCompound(node);
			break;
		case AST_NOOP: 
			return node; 
			break;
		default:
			printf("Uncaught statement of type %d\n", node->type);
			exit(1);
			return new AST(AST_NOOP);
		}
	}

	AST* Visitor::visitVariableDefinition(AST* node)
	{
		addVariableDefinition(node->scope, node);

		return node;
	}

	AST* Visitor::visitVariable(AST* node)
	{
		AST* vdef = getVariableDefinition(node->scope, node->variableName);

		if (vdef != nullptr)
			return this->visit(vdef->variableDefinitionValue);

		if (!IS_BUILTIN(node->variableName.c_str()))
		{
			printf("Undefined variable '%s'\n", node->variableName.c_str());
			exit(1);
		}

		return node;
	}

	AST* Visitor::visitString(AST* node)
	{
		return node;
	}

	AST* Visitor::visitFunctionCall(AST* node)
	{
		if (IS_BUILTIN(node->functionCallName.c_str())) {
			if (node->functionCallName == "print")
				return builtin_print(this, node->functionCallArguments, node->functionCallArgumentsSize);
			else if (node->functionCallName == "println")
				return builtin_println(this, node->functionCallArguments, node->functionCallArgumentsSize);
			else if (node->functionCallName == "pbrkp")
				return builtin_breakpoint(this, node->functionCallArguments, node->functionCallArgumentsSize);
		}
		AST* fdef = getFunctionDefinition(
			node->scope,
			node->functionCallName
		);

		if (fdef == nullptr) {
			printf("Undefined method `%s`\n", node->functionCallName.c_str());
			exit(1);
		}
		if (node->functionCallArguments[0]->type != AST_NOOP && node->functionCallArgumentsSize > fdef->functionDefinitionArgs.size())
		{
			printf("Too many arguments passed to `%s()`, accepts only: %d argument(s)\n", node->functionCallName.c_str(), fdef->functionDefinitionArgs.size());
			exit(1);
		}
		if (node->functionCallArgumentsSize < fdef->functionDefinitionArgs.size())
		{
			printf("Too few arguments passed to `%s()`, needs min: %d argument(s)\n", node->functionCallName.c_str(), fdef->functionDefinitionArgs.size());
			exit(1);
		}

		for (int i = 0; i < fmin(fdef->functionDefinitionArgs.size(), node->functionCallArgumentsSize); i++)
		{
			auto var = (AST*)fdef->functionDefinitionArgs[i];
			auto value = (AST*)node->functionCallArguments[i];
			
			AST* var_def = new AST(AST_VARIABLE_DEFINITION);
			var_def->variableDefinitionVariableName = var->variableName;
			var_def->variableDefinitionValue = value;
			
			addVariableDefinition(fdef->functionDefinitionBody->scope, var_def);
		}

		return this->visit(fdef->functionDefinitionBody);
	}

	AST* Visitor::visitFunctionDefinition(AST* node)
	{		
		addFunctionDefinition(node->scope, node);

		return node;
	}

	AST* Visitor::visitCompound(AST* node)
	{
		for (auto const& compoundChild : node->compoundValue)
		{
			this->visit(compoundChild);
		}
		return NOOPAST;
	}
}