#include "includes/Lexer.h"
#include <string>
#include <ctype.h>
#include <iostream>
#include "includes/global.h"

namespace Hivo {

	Token* advanceWithToken(Lexer* lexer, Token* token);

	Lexer::Lexer(std::string contents)
	{
		this->contents = contents;
		this->i = 0;
		this->c = contents[this->i];

	};
	/*Lexer::~Lexer() {}*/

	void Lexer::advance() 
	{

		if (this->c != '\0' && this->i < this->contents.length())
		{
			this->i++;
			this->c = this->contents[this->i];
		}
	}

	void Lexer::skipWhitespace() 
	{
		while (isspace(this->c) || this->c == 10)
		{
			this->advance();
		}
	}

	Token* Lexer::getNextToken(Lexer* lexer)
	{

		while (lexer->c != '\0' || lexer->i < lexer->contents.length()) 
		{

			if (isspace(lexer->c) || lexer->c == END_OF_FIELD)
			{
				lexer->skipWhitespace();
			}
			if (lexer->c == '"' || lexer->c == 39) 
				return lexer->collectString(lexer);
			if (isalnum(lexer->c)) 
				return collectID(lexer);

			switch (lexer->c)
			{
				case '=': {
					return advanceWithToken(lexer, initToken(TOKEN_EQUALS, lexer->getCurrentCharAsString(lexer)));
					break;
				}
				case ';': {
					return advanceWithToken(lexer, initToken(TOKEN_SEMI, lexer->getCurrentCharAsString(lexer)));
					break;
				}
				case '(': {
					return advanceWithToken(lexer, initToken(TOKEN_LPAREN, lexer->getCurrentCharAsString(lexer)));
					break;
				}
				case ')': {
					return advanceWithToken(lexer, initToken(TOKEN_RPAREN, lexer->getCurrentCharAsString(lexer)));
					break;
				}
				case ',': {
					return advanceWithToken(lexer, initToken(TOKEN_COMMA, lexer->getCurrentCharAsString(lexer)));
					break;
				}
			}
			
		}
		return initToken(TOKEN_EOF, "\0");
	}

	Token* Lexer::collectString(Lexer* lexer) 
	{
		lexer->advance();

		std::string value;

		while (lexer->c != '"' && lexer->c != 39)
		{
			std::string s = getCurrentCharAsString(lexer);

			value += s;

			lexer->advance();
		}
		lexer->advance();

		return initToken(TOKEN_STRING, value);
	}
	Token* Lexer::collectID(Lexer* lexer)
	{
		std::string value;

		while (isalnum(lexer->c))
		{
			std::string s = getCurrentCharAsString(lexer);

			value.append(s);

			lexer->advance();
		}

		return initToken(TOKEN_ID, value);
	}

	Token* advanceWithToken(Lexer* lexer, Token* token)
	{
		lexer->advance();

		return token;
	}

	std::string Lexer::getCurrentCharAsString(Lexer* lexer) 
	{	
		std::string str = {lexer->c};

		return str;
	}

	char* Lexer::getCurrentCharAsCharArray(Lexer* lexer) {
		char* str = new char[2];
		str[0] = lexer->c;
		str[1] = '\0';

		return str;
	}
}