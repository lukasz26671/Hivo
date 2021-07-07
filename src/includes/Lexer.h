#pragma once
#include <iostream>
#include "Token.h"

namespace Hivo {

	class Lexer {
	public:
		char c = '\0';
		unsigned int i = 0;
		std::string contents = "";

		Lexer(const std::string& contents);
		//~Lexer();
		void advance();

		void skipWhitespace();

		Token* getNextToken(Lexer* lexer);

		Token* collectString(Lexer* lexer);

		Token* collectID(Lexer* lexer);

		std::string getCurrentCharAsString(Lexer* lexer);

		char* getCurrentCharAsCharArray(Lexer* lexer);
	};

}

 