#pragma once
#include <iostream>

namespace Hivo {
	typedef enum
	{
		TOKEN_ID,
		TOKEN_EQUALS,
		TOKEN_STRING,
		TOKEN_SEMI,
		TOKEN_LPAREN,
		TOKEN_RPAREN,
		TOKEN_COMMA,
		TOKEN_LBRACE,
		TOKEN_RBRACE,
		TOKEN_EOF
	} TokenType;

	typedef struct
	{
		TokenType type;

		std::string value;
	} Token;

	Token* initToken(int type, std::string value);

	static Token* currentLexerToken = nullptr;
	static Token* prevLexerToken = nullptr;
	static Token* prevPrevLexerToken = nullptr;
}