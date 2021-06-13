#include "includes/Visitor.h"
#include "includes/Utils.h"
#include "includes/global.h"
#include <iostream>
#include <stdio.h>
#include "includes/nameof.h"
#include "includes/AST.h"
#include "includes/builtin.h"

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
		case AST_FUNCTION_DECLARATION:
			return this->visitFuncionDeclaration(node);
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
		
		this->variableDefinitionsSize++;
		this->variableDefinitions.push_back(node);

		return node;
	}

	AST* Visitor::visitVariable(AST* node)
	{
		for (auto const& vardef : this->variableDefinitions)
		{
			if (vardef->variableDefinitionVariableName == node->variableName)
			{
				return this->visit(vardef->variableDefinitionValue);
			}
		}
		if(!IS_BUILTIN(node->variableName.c_str()))
			printf("Undefined variable '%s'\n", node->variableName.c_str());

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

		}
		return NOOPAST;
	}

	AST* Visitor::visitFuncionDeclaration(AST* node)
	{
		throw NotImplemented(__func__);
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