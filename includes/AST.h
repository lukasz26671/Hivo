#pragma once
#include <iostream>
#include <vector>
#include "Utils.h"
#include "AST.h"
namespace Hivo {

	typedef enum  {
		AST_VARIABLE_DEFINITION,
		AST_VARIABLE,
		AST_FUNCTION_CALL,
		AST_FUNCTION_DECLARATION,
		AST_STRING,
		AST_COMPOUND,
		AST_NOOP
	} AstType;
	
	class AST
	{
	public:
		AstType type = AstTypeCast(0);
		
		/*AST_VARIABLE_DEFINITION */
		std::string variableDefinitionVariableName = "";
		AST* variableDefinitionValue = nullptr;
		
		/* AST_VARIABLE */
		std::string variableName = "";
		
		/* AST_FUNCTION_CALL */
		std::string functionCallName = "";
		std::vector<AST*> functionCallArguments;
		size_t functionCallArgumentsSize = 0;

		/* AST_STRING */
		std::string stringValue = "";

		/* AST_COMPOUND */

		std::vector<AST*> compoundValue;
		size_t compoundSize = 0;

		AST(int type);
		~AST();

		
	};
}