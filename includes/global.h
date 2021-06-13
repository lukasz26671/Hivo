#pragma once
#include <string>
#include "nameof.h"
#include <iostream>
#include "AST.h"
namespace Hivo {
	static AST* NOOPAST = new AST(AST_NOOP);

	constexpr const char* const VARIABLE_DEFINITION_KEYWORDS[] = { "let", "var" };
	constexpr const char* const BUILTIN_FUNCTIONS[] = { "print", "println" };
	constexpr const char* const FUNCTION_DEFINITION_KEYWORDS[] = { "function" };

	constexpr const bool IS_VAR_DEFKW(const char* def) {
		for (auto const& keyword : VARIABLE_DEFINITION_KEYWORDS)
		{
			if (strcmp(keyword, def) == 0 && strlen(keyword) == strlen(def)) return true;
		}
		return false;
	}
	constexpr const bool IS_FN_DEFKW(const char* def) {
		for (auto const& keyword : FUNCTION_DEFINITION_KEYWORDS)
		{
			if (strcmp(keyword, def) == 0 && strlen(keyword) == strlen(def)) return true;
		}
		return false;
	}

	constexpr const bool IS_BUILTIN(const char* def) {
		for (auto const& fn : BUILTIN_FUNCTIONS)
		{
			if (strcmp(fn, def) == 0 && strlen(fn) == strlen(def)) return true;
		}
		return false;
	}
	constexpr const char* IS_BUILTIN_GET(const char* def) {
		for (auto const& fn : BUILTIN_FUNCTIONS)
		{
			if (strcmp(fn, def) == 0 && strlen(fn) == strlen(def)) return fn;
		}
		return NULL;
	}
	constexpr char const END_OF_FIELD = 10;

	class NotImplemented : public std::exception
	{
	private:
		char msg[100];
	public:
		NotImplemented(const char* fnName = "") {
			strcpy_s(msg, "Function ");
			strcat_s(msg, fnName);
			strcat_s(msg, " not implemented.");
		};

		virtual const char* what() const throw()
		{
			return msg;
		}
	};

}