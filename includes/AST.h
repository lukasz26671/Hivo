#pragma once
#include <iostream>
#include <vector>
#include "Utils.h"

namespace Hivo {

	typedef enum {
		AST_VARIABLE_DEFINITION,
		AST_VARIABLE,
		AST_FUNCTION_CALL,
		AST_FUNCTION_DEFINITION,
		AST_STRING,
		AST_COMPOUND,
		AST_NOOP
	} AstType;

	class AST
	{
	public:
		AstType type = AstTypeCast(0);

		struct SCOPE_STRUCT* scope = nullptr;

		/*AST_VARIABLE_DEFINITION */
		std::string variableDefinitionVariableName = "";
		AST* variableDefinitionValue = nullptr;

		/* AST_VARIABLE */
		std::string variableName = "";

		/* AST_FUNCTION_CALL */
		std::string functionCallName = "";
		std::vector<AST*> functionCallArguments;
		size_t functionCallArgumentsSize = 0;

		/* AST_FUNCTION DEFINITION */
		std::string functionName = "";
		std::vector<AST*> functionDefinitionArgs;
		AST* functionDefinitionBody = nullptr;

		/* AST_STRING */
		std::string stringValue = "";

		/* AST_COMPOUND */

		std::vector<AST*> compoundValue;
		size_t compoundSize = 0;

		AST(int type);
		~AST();
	};
}