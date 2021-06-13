#pragma once
#include <iostream>
#include <stdio.h>
#include "AST.h"
#include "global.h"
namespace Hivo {

	static AST* builtin_print(Visitor* visitor, std::vector<AST*> args, int argc, bool newline=false)
	{
		for (int i = 0; i < argc; i++)
		{
			AST* visited = visitor->visit(args[i]);

			const char* builtin_name = visitor->prevPreviousNode->functionCallName.c_str();
			switch (visited->type)
			{
			case AST_STRING: {
				if(newline)
					printf("%s\n", visited->stringValue.c_str());
				else
					printf("%s", visited->stringValue.c_str());
				break;
			}
			default:
				printf("%s", visitor->prevPreviousNode->functionCallName.c_str());
				if ((builtin_name = IS_BUILTIN_GET(builtin_name)) != "")
					if (newline)
						printf("<Function builtin_%s> @ 0x%p\n", builtin_name, visited);
					else 
						printf("<Function builtin_%s> @ 0x%p", builtin_name, visited);
				else
					printf("%p", visited);

				break;
			}
		}

		return NOOPAST;
	}
	static AST* builtin_println(Visitor* visitor, std::vector<AST*> args, int argc)
	{
		return builtin_print(visitor, args, argc, true);
	}
}