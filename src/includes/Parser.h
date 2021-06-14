#pragma once
#include <iostream>
#include "Lexer.h"
#include "AST.h"
#include "scope.h"

namespace Hivo {

	class Parser {

	public:
		Lexer* lexer;
		Token* currentToken;
		Token* prevToken;
		Token* prevPrevToken;
		Scope* globalScope;

		Parser(Lexer* lexer);
		~Parser();
		void eat(int tokenType);

		AST* parse(Parser* parser, Scope* scope);

		AST* parseStatement(Parser* parser, Scope* scope);

		AST* parseStatements(Parser* parser, Scope* scope);

		AST* parseExpr(Parser* parser, Scope* scope);

		AST* parseFactor(Parser* parser, Scope* scope);

		AST* parseTerm(Parser* parser, Scope* scope);

		AST* parseFunctionCall(Parser* parser, Scope* scope);

		AST* parseVariable(Parser* parser, Scope* scope);

		AST* parseVariableDefinition(Parser* parser, Scope* scope);

		AST* parseFunctionDefinition(Parser* parser, Scope* scope);

		AST* parseString(Parser* parser, Scope* scope);

		AST* parseID(Parser* parser, Scope* scope);

	};

}
