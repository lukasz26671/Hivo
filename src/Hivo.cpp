#include <iostream>
#include <stdio.h>
#include <numeric>
#include "includes/Hivo.h"

using namespace Hivo;

void PrintTrace(Hivo::AST* root)
{
    std::cout << '\n';

    for (auto const& node : root->compoundValue)
    {
        auto nodeType = node->type;

        std::string value;
        std::string adValue;
        std::string bltn;

        int k = 0;
        switch (nodeType) {

        case AST_FUNCTION_CALL:
            bltn = IS_BUILTIN(node->functionCallName.c_str()) ? "BUILTIN_" : "";
            value = "Function call _[" + bltn + node->functionCallName + "]_";
            adValue = " with params: ";
            for (auto const& param : node->functionCallArguments)
            {
                if (k == node->functionCallArgumentsSize - 1)
                    adValue.append(param->variableName);
                else
                    adValue.append(param->variableName + ", ");

                k++;

            }
            break;
        case AST_VARIABLE_DEFINITION:
            value = "Variable Definition _[" + node->variableDefinitionVariableName + "]_";
            adValue = " with value: ";
            adValue.append(node->variableDefinitionValue->stringValue);
            break;
        case AST_FUNCTION_DEFINITION:
            value = "Function Definition _[" + node->functionName + "]_ WITH PARAMS []";
            break;
        case AST_VARIABLE:
            value = "Variable _[" + node->variableName + "]_";
            break;
        case AST_STRING:
            value = "String _[" + node->stringValue + "]_";
            break;
        }

        std::cout << value << adValue << "\n";
    }
}

typedef struct HIVO_STRUCT{
    Lexer* lexer;
    Parser* parser;
    AST* root;
    Visitor* visitor;

    void init(const std::string& sourceCode, bool printTrace=false) {
        lexer = new Lexer(sourceCode);
        parser = new Parser(lexer);
        root = parser->parse(parser, parser->globalScope);
        visitor = new Visitor();

        std::cout << '\n';

        if (printTrace)
            PrintTrace(root);

        std::cout << '\n';

        try {
            visitor->visit(root);
        }
        catch (NotImplemented ex) {
            std::cout << ex.what();
        }

    }
    void deinit() {
        delete parser;
        delete root;
        delete visitor;
    }
} HivoInternals;


/* 
    ARG[0] -> Hivo.exe
    ARG[1] -> File to open
    ARG[2] -> Trace
*/
int main(int argc, char** argv)
{
#ifdef _DEBUG
    bool debug = true;
#else
    bool debug = false;
#endif

    HivoInternals HivoLanguage;
    if (argc > 1) {

        bool debug = false;

        std::string sourceCode = getFileContents(argv[1], debug);

        if (argc > 2) 
            debug = strcmp(argv[2], "-d") == 0;
        
        HivoLanguage.init(sourceCode, debug);

        HivoLanguage.deinit();
    }
    else {
#ifndef _DEBUG
        printf("Usage:\nHivo <filename> [-d]");
#else
        std::string sourceCode = getFileContents("./examples/Test.hv", debug);

        if (argc > 2)
            debug = strcmp(argv[2], "-d") == 0;

        HivoLanguage.init(sourceCode, debug);

        HivoLanguage.deinit();
#endif
    }
    //delete HivoLanguage;

    std::cout << "\n" << "Press enter or return key to end." << "\n";

    std::string ps;

    std::getline(std::cin, ps);

    return 0;
}

