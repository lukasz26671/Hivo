#pragma once
#include <iostream>
#include "Lexer.h"
#include "AST.h"


namespace Hivo {

	class Parser {

	public:
		Lexer* lexer;
		Token* currentToken;
		Token* prevToken;
		Token* prevPrevToken;

		Parser(Lexer* lexer);
		~Parser();
		void eat(int tokenType);

		AST* parse(Parser* parser);

		AST* parseStatement(Parser* parser);

		AST* parseStatements(Parser* parser);

		AST* parseExpr(Parser* parser);

		AST* parseFactor(Parser* parser);

		AST* parseTerm(Parser* parser);

		AST* parseFunctionCall(Parser* parser);

		AST* parseVariable(Parser* parser);

		AST* parseVariableDefinition(Parser* parser);

		AST* parseString(Parser* parser);

		AST* parseID(Parser* parser);

	};

}
