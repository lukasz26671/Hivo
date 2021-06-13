#include <iostream>
#include <stdio.h>
#include "includes/Parser.h"
#include "includes/AST.h"
#include "includes/Lexer.h"
#include "includes/Token.h"
#include "includes/global.h"

namespace Hivo {
	Parser::Parser(Lexer* lexer) 
	{
		this->lexer = lexer;
		this->prevPrevToken = nullptr;
		this->prevToken = nullptr;
		this->currentToken = lexer->getNextToken(lexer);
	}
	Parser::~Parser() {
		delete this->lexer;
		delete this->currentToken;
	}


	void Parser::eat(int tokenType) 
	{
		if (this->currentToken->type == tokenType)
		{
			this->prevPrevToken = this->prevToken;
			this->prevToken = this->currentToken;
			this->currentToken = lexer->getNextToken(this->lexer);

			if (this->currentToken == NULL)
			{
				//End parsing.
				return;
			}
		}
		else {
			printf(
				"Unexpected token '%s' with type %i at index %i",
				this->currentToken->value.c_str(),
				this->currentToken->type,
				this->lexer->i
			);
			exit(1);
		}
	}

	AST* Parser::parse(Parser* parser)
	{
		return parser->parseStatements(parser);
	}

	AST* Parser::parseStatement(Parser* parser)
	{
		switch (parser->currentToken->type) 
		{
			case TOKEN_ID: return parser->parseID(parser); 	
			case TOKEN_EOF: return NOOPAST;
			default: return NOOPAST;
		}
		
	}

	AST* Parser::parseStatements(Parser* parser)
	{
		AST* compound = new AST(AST_COMPOUND);
		AST* statement = parser->parseStatement(parser);
		if (statement) {
			compound->compoundValue.push_back(statement);
			compound->compoundSize++;

			while (parser->currentToken->type == TOKEN_SEMI && parser->currentToken->type != TOKEN_EOF)
			{
				parser->eat(TOKEN_SEMI);
				AST* statement = parser->parseStatement(parser);
				compound->compoundValue.push_back(statement);
				compound->compoundSize++;
			}
		}
		return compound;
	}

	AST* Parser::parseExpr(Parser* parser)
	{
		switch (parser->currentToken->type)
		{
			case TOKEN_STRING: return parser->parseString(parser);
			case TOKEN_ID: return parser->parseID(parser);
			default: return NOOPAST;
		}

	}

	AST* Parser::parseFactor(Parser* parser)
	{
		return nullptr;
	}

	AST* Parser::parseTerm(Parser* parser)
	{
		return nullptr;
	}

	AST* Parser::parseFunctionCall(Parser* parser)
	{
		AST* functionCall = new AST(AST_FUNCTION_CALL);

		/*Expect argument pass */
		parser->eat(TOKEN_LPAREN);
		functionCall->functionCallName = parser->prevPrevToken->value;

		std::string varName = parser->currentToken->value;

		AST* param = parser->parseExpr(parser);
		param->variableName = varName;

		/* Add argument to arguments list*/
		functionCall->functionCallArguments.push_back(param);
		functionCall->functionCallArgumentsSize++;

		while (parser->currentToken->type != TOKEN_RPAREN && parser->currentToken->type == TOKEN_COMMA)
		{
			parser->eat(TOKEN_COMMA);
			/* Assign arguments to a function */
			std::string varName = parser->currentToken->value;
			AST* param = parser->parseExpr(parser);
			param->variableName = varName;

			/* Add argument to arguments list*/
			functionCall->functionCallArguments.push_back(param);
			functionCall->functionCallArgumentsSize++;

			/*Expect argument to be a variable*/
			//parser->eat(TOKEN_ID);
		}
		parser->eat(TOKEN_RPAREN);
		
		return functionCall;
	}

	AST* Parser::parseVariable(Parser* parser)
	{
		std::string tokenValue = parser->currentToken->value;
		/* Variable name or function call */
		parser->eat(TOKEN_ID);

		/* Parse function call */
		if (parser->currentToken->type == TOKEN_LPAREN)
			return parser->parseFunctionCall(parser);

		/* Assign a variable */
		AST* variable = new AST(AST_VARIABLE);
		variable->variableName = tokenValue;

		return variable;
	}

	AST* Parser::parseVariableDefinition(Parser* parser)
	{
		/* Variable definition keyword */
		parser->eat(TOKEN_ID); 

		/* Variable name */
		std::string variableName = parser->currentToken->value;
		parser->eat(TOKEN_ID); 

		/* Variable assign token */
		parser->eat(TOKEN_EQUALS);

		/* Parse expression */ 
		AST* variableValue = parser->parseExpr(parser);

		/* Create a new variable definition */
		AST* variableDefinition = new AST(AST_VARIABLE_DEFINITION);

		variableDefinition->variableDefinitionVariableName = variableName;
		variableDefinition->variableDefinitionValue = variableValue;


		return variableDefinition;
	}

	AST* Parser::parseString(Parser* parser)
	{
		AST* string = new AST(AST_STRING);
		string->stringValue = parser->currentToken->value;

		parser->eat(TOKEN_STRING);

		return string;
	}
	AST* Parser::parseID(Parser* parser)
	{
		if (IS_VAR_DEFKW(parser->currentToken->value.c_str())) {
			return parser->parseVariableDefinition(parser);
		}

		return parser->parseVariable(parser);
	}

}