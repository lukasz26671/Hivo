#pragma once
#include "includes/Parser.h"
#include "includes/AST.h"
#include "includes/Lexer.h"
#include "includes/Token.h"
#include "includes/global.h"
#include "includes/Visitor.h"
#include "includes/io.h"
#include "includes/builtin.h"

void PrintTrace(Hivo::AST* root);

void ClearMemory(Hivo::Visitor* visitor, Hivo::Parser* parser, Hivo::AST* root);
