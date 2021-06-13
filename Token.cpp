#include "Token.h"
#include <iostream>
#include "Utils.h"
#include "global.h"

namespace Hivo {

	Token* initToken(int type, std::string value)
	{
		Token* token = new Token();
		token->type = TokenTypeCast(type);
		token->value = value;

		return token;
	}

}