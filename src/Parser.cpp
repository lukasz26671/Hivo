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
		this->globalScope = new Scope();
	}
	Parser::~Parser() {
		delete this->lexer;
		delete this->currentToken;
		delete this->globalScope;
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

	static Scope* getNodeScope(Parser* parser, AST* node)
	{
		return node->scope == nullptr ? parser->globalScope : node->scope;
	}

	AST* Parser::parse(Parser* parser, Scope* scope)
	{
		return parser->parseStatements(parser, scope);
	}

	AST* Parser::parseStatement(Parser* parser, Scope* scope)
	{
		switch (parser->currentToken->type) 
		{
			case TOKEN_ID: return parser->parseID(parser, scope); 	
			case TOKEN_EOF: return NOOPAST;
			default: return NOOPAST;
		}
		
	}

	AST* Parser::parseStatements(Parser* parser, Scope* scope)
	{
		AST* compound = new AST(AST_COMPOUND);
		compound->scope = scope;

		AST* statement = parser->parseStatement(parser, scope);
		statement->scope = scope;

		if (statement) {
			compound->compoundValue.push_back(statement);
			compound->compoundSize++;

			while (parser->currentToken->type == TOKEN_SEMI && parser->currentToken->type != TOKEN_EOF)
			{
				parser->eat(TOKEN_SEMI);
				AST* statement = parser->parseStatement(parser, scope);
				compound->compoundValue.push_back(statement);
				compound->compoundSize++;
			}
		}
		return compound;
	}

	AST* Parser::parseExpr(Parser* parser, Scope* scope)
	{
		switch (parser->currentToken->type)
		{
			case TOKEN_STRING: return parser->parseString(parser, scope);
			case TOKEN_ID: return parser->parseID(parser, scope);
			default: return NOOPAST;
		}

	}

	AST* Parser::parseFactor(Parser* parser, Scope* scope)
	{
		throw new NotImplemented();
	}

	AST* Parser::parseTerm(Parser* parser, Scope* scope)
	{
		throw new NotImplemented();
	}

	AST* Parser::parseFunctionCall(Parser* parser, Scope* scope)
	{
		AST* functionCall = new AST(AST_FUNCTION_CALL);

		/*Expect argument pass */
		parser->eat(TOKEN_LPAREN);
		functionCall->functionCallName = parser->prevPrevToken->value;

		std::string varName = parser->currentToken->value;

		AST* param = parser->parseExpr(parser, scope);
		param->variableName = varName;

		/* Add argument to arguments list*/
		functionCall->functionCallArguments.push_back(param);
		functionCall->functionCallArgumentsSize++;

		while (parser->currentToken->type != TOKEN_RPAREN && parser->currentToken->type == TOKEN_COMMA)
		{
			parser->eat(TOKEN_COMMA);
			/* Assign arguments to a function */
			std::string varName = parser->currentToken->value;
			AST* param = parser->parseExpr(parser, scope);
			param->variableName = varName;

			/* Add argument to arguments list*/
			functionCall->functionCallArguments.push_back(param);
			functionCall->functionCallArgumentsSize++;

			/*Expect argument to be a variable*/
			//parser->eat(TOKEN_ID);
		}
		parser->eat(TOKEN_RPAREN);
		
		functionCall->scope = scope;

		return functionCall;
	}

	AST* Parser::parseVariable(Parser* parser, Scope* scope)
	{
		std::string tokenValue = parser->currentToken->value;
		/* Variable name or function call */
		parser->eat(TOKEN_ID);

		/* Parse function call */
		if (parser->currentToken->type == TOKEN_LPAREN)
			return parser->parseFunctionCall(parser, scope);

		/* Assign a variable */
		AST* variable = new AST(AST_VARIABLE);
		variable->variableName = tokenValue;

		variable->scope = scope;

		return variable;
	}
	AST* Parser::parseFunctionDefinition(Parser* parser, Scope* scope)
	{
		AST* functionDef = new AST(AST_FUNCTION_DEFINITION);

		/* Function definition keyword */
		parser->eat(TOKEN_ID);

		/* Function name */
		std::string functionName = parser->currentToken->value;
		parser->eat(TOKEN_ID);

		parser->eat(TOKEN_LPAREN);		
		if (parser->currentToken->type != TOKEN_RPAREN) {
			AST* arg = parser->parseVariable(parser, scope);
			functionDef->functionDefinitionArgs.push_back(arg);
		}
		while (parser->currentToken->type == TOKEN_COMMA)
		{
			parser->eat(TOKEN_COMMA);

			AST* arg = parser->parseVariable(parser, scope);
			functionDef->functionDefinitionArgs.push_back(arg);
		}

		parser->eat(TOKEN_RPAREN);
		parser->eat(TOKEN_LBRACE);
		
		AST* compound = parser->parseStatements(parser, scope);

		functionDef->functionName = functionName;
		functionDef->functionDefinitionBody = compound;

		parser->eat(TOKEN_RBRACE);
		
		functionDef->scope = scope;

		return functionDef;
	}
	AST* Parser::parseVariableDefinition(Parser* parser, Scope* scope)
	{
		/* Variable definition keyword */
		parser->eat(TOKEN_ID); 

		/* Variable name */
		std::string variableName = parser->currentToken->value;
		parser->eat(TOKEN_ID); 

		/* Variable assign token */
		parser->eat(TOKEN_EQUALS);

		/* Parse expression */ 
		AST* variableValue = parser->parseExpr(parser, scope);

		/* Create a new variable definition */
		AST* variableDefinition = new AST(AST_VARIABLE_DEFINITION);

		variableDefinition->variableDefinitionVariableName = variableName;
		variableDefinition->variableDefinitionValue = variableValue;

		variableDefinition->scope = scope;

		return variableDefinition;
	}

	AST* Parser::parseString(Parser* parser, Scope* scope)
	{
		AST* string = new AST(AST_STRING);
		string->stringValue = parser->currentToken->value;

		parser->eat(TOKEN_STRING);
		string->scope = scope;
		return string;
	}
	AST* Parser::parseID(Parser* parser, Scope* scope)
	{
		if (IS_VAR_DEFKW(parser->currentToken->value.c_str())) {
			return parser->parseVariableDefinition(parser, scope);
		}
		else if (IS_FN_DEFKW(parser->currentToken->value.c_str()))
		{
			return parser->parseFunctionDefinition(parser, scope);
		}

		return parser->parseVariable(parser, scope);
	}

}