/*
*Batch Number 6
*Abhinav Bhatia (2011A7PS371P)
*Mukul Bhutani (2011A7PS343P)
*/
/*
*Modified by Batch Number 18
*SWATI SHARMA (2014H112176P)
*SAGAR CHOUDHARI (2014H112183P)
*/

#include "compiler.h"
#include "first.h"
#include "follow.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AST.h"
#include "SymbolTable.h"
#include "typeChecker.h"
#include "codeGenerator.h"
#include "myIRgenerator.h"
#include "myCodeGenerator.h"
#include "myOptimizer.h"

#define GRAMMAR_INPUT_FILENAME "realGrammar.txt"
#define KEYWORDS_INPUT_FILENAME "keywords.txt"
#define DEFAULT_OUTPUT_PARSE_TREE_FILE "parseTreeOutFile.txt"
#define AST_RULES_FILENAME "astRules.txt"

#define PARSER_NOT_INVOKED 0
#define PARSING_FAILED 1
#define PARSED_SUCCESSFULLY 2

int parseOnlySourceCode(Parser* p, Lexer lex)
{
	int result = parseInputSourceCode(p, lex);
	if (result)
	{
		printf("\n\nThe input is syntactically correct.  :)\n\n");
		return PARSED_SUCCESSFULLY;
	}
	else
	{
		printf("\n\nThe input is NOT syntactically correct.  :(\n\n");
		return PARSING_FAILED;
	}
}

int printOnlyParsetree(Parser* p, Lexer lex, char* outPutTreeFile, int isParsed)
{
	if (isParsed==PARSER_NOT_INVOKED)
	{
		isParsed = parseOnlySourceCode(p, lex);
	}

	if (isParsed == PARSED_SUCCESSFULLY)
	{
		printParseTree(p->parseTree, outPutTreeFile);
		return isParsed;
	}
	else
	{
		return isParsed;
	}
}



int main(int argc, char** argv)
{

	////////////////Basic Printing/////////////////////////
	//printf("Submitted by Batch No. 06:\n%30s\t(%s)\n%30s\t(%s)\n\n\n", "Abhinav Bhatia", "2011A7PS371P", "Mukul Bhutani ", "2011A7PS343P");
	
	printf("LEVEL %d: %s", 3, "AST/Symbol Table/Type checking/Symantic Rules modules work\n");
	printf("Code generation implemented for most constructs\n\n");
	////////////////Basic Printing End/////////////////////

	FILE* pSourceFile = NULL;
	int choice;
	int isParsed = PARSER_NOT_INVOKED;


	if (argc > 2)
	{
		pSourceFile = fopen(argv[1], "r");
	}
	else if (argc == 2)
	{
		printf("\nLess number of arguments ...Three arguments required....\n");
		printf("1. Source Code File.\n");
		printf("2. File for printing IR code.\n");
                printf("3. File for printing assembly code.\n");

		char c;
		scanf("%c", &c);
		return 0;
	}

	if (pSourceFile == NULL)
	{
		printf("\nError: No Input File!\nExiting...........");
		char c;
		scanf("%c", &c);
		return -1;
	}

	FILE* pKeywordsFile = fopen(KEYWORDS_INPUT_FILENAME, "r");
	if (!pKeywordsFile)
	{
		printf("\nError: keywords file \"%s\" not found.\nExiting..........", KEYWORDS_INPUT_FILENAME);
		char c;
		scanf("%c", &c);
		return -1;
	}
	FILE* grammarInputFile = fopen(GRAMMAR_INPUT_FILENAME, "r");
	if (!grammarInputFile)
	{
		printf("\nError: Grammar file \"%s\" not found.\nExiting..........", GRAMMAR_INPUT_FILENAME);
		char c;
		scanf("%c", &c);
		return -1;
	}
	FILE* astRulesFile = fopen(AST_RULES_FILENAME, "r");
	if (!astRulesFile)
	{
		printf("\nError: AST Rules file \"%s\" not found.\nExiting..........", AST_RULES_FILENAME);
		char c;
		scanf("%c", &c);
		return -1;
	}

	Parser parser;
	Lexer lex = lexer_createNew(pSourceFile, pKeywordsFile);


	printf("\n\nPlease enter your choice\n");
	printf("1. Print list of tokens.\n");
	printf("2. Verify syntactic correctness of input source code and print parse tree\n");
	printf("3. Print Abstract Syntax Tree.\n");
	printf("4. Print Symbol Table.\n");
        printf("5. Display quadruple\n"); 
        printf("6. Display Control Flow Graph(Blockwise IR)\n"); 
        printf("7. Display Unoptimized IR\n"); 
        printf("8. Display Optimized IR\n"); 
        printf("9. Produce Unoptimized Assembly Code \n"); 
	printf("10. Produce Optimize Assembly Code.\n");
        printf("11. Display performance measure\n"); 
	printf("12. Exit.\n");

	char flushChar;
	scanf("%d%c", &choice, &flushChar);
	switch (choice)
	{
	case 1:
		lexer_runLexicalAnalyses(lex);
		break;
	case 2:
		parser = parser_initialise(grammarInputFile, astRulesFile);

		isParsed = printOnlyParsetree(&parser, lex, DEFAULT_OUTPUT_PARSE_TREE_FILE, isParsed);
		break;
	case 3:
		parser = parser_initialise(grammarInputFile, astRulesFile);
		isParsed = parseOnlySourceCode(&parser, lex);
		if (isParsed == PARSED_SUCCESSFULLY)
		{
			Tree ast = createAst(parser);
			printAST(ast);
		}
		break;
	case 4:
		parser = parser_initialise(grammarInputFile, astRulesFile);
		isParsed = parseOnlySourceCode(&parser, lex);
		if (isParsed == PARSED_SUCCESSFULLY)
		{
			Tree ast = createAst(parser);
			createSymbolTables(ast);
			turnOnReportingSemanticErrors(FALSE);
			typeExtractorandChecker(ast);
			printSymbolTable();
		}
		break;
        case 5: 
		//option 5: for displaying the quadruple (use printQuadruple( ) function that takes as input the quadruple structure populated by you)
                parser = parser_initialise(grammarInputFile, astRulesFile);
		isParsed = parseOnlySourceCode(&parser, lex);
		quadruple* quadList;
		if (isParsed == PARSED_SUCCESSFULLY)
		{
			Tree ast = createAst(parser);
			createSymbolTables(ast);
			turnOnReportingSemanticErrors(TRUE);
			if (typeExtractorandChecker(ast))
			{
				printf("\nCode compiles successfully..........:)");
				quadruple* quadList = (quadruple*) malloc(sizeof(quadruple));
				printf("\nGenerating quadruples ......\n");
				//generate quadruple code
				quadList=generateirCode(ast);
				//print quadruple
				print_IR(quadList);
				printf("\n\nFinished quadruple generation.");
			}
		}
		break;
	case 6:
	{
		//option 6: for displaying control flow graph (block wise IR with execution flow details)
		parser = parser_initialise(grammarInputFile, astRulesFile);
		isParsed = parseOnlySourceCode(&parser, lex);
		quadruple* quadList;
		if (isParsed == PARSED_SUCCESSFULLY)
		{
			Tree ast = createAst(parser);
			createSymbolTables(ast);
			turnOnReportingSemanticErrors(TRUE);
			if (typeExtractorandChecker(ast))
			{
				quadruple* quadList = (quadruple*) malloc(sizeof(quadruple));
				quadList=generateirCode(ast);
				//printf("\nBasic Blocks of IR ......");
				printf("\n------------------------------------------------------------------------------\n");
				//generate basic block and cfg
				displaycfg(quadList);
			}
		}


		break;
	}
	case 7:
	{
		//option 7: for printing unoptimized IR on the screen
		parser = parser_initialise(grammarInputFile, astRulesFile);
		isParsed = parseOnlySourceCode(&parser, lex);
		quadruple* quadList;
		if (isParsed == PARSED_SUCCESSFULLY)
		{
			Tree ast = createAst(parser);
			createSymbolTables(ast);
			turnOnReportingSemanticErrors(TRUE);
			if (typeExtractorandChecker(ast))
			{
				printf("\nCode compiles successfully..........:)\n");
				FILE* irg = fopen(argv[2], "w");
				quadruple* quadList = (quadruple*) malloc(sizeof(quadruple));
				printf("\n------------------------------------------------------------------------------\n");
				quadList=generateirCode(ast);
				printf("\nUnoptimized IR Code......");
				//print unoptimized IR code on screen
				print_IRD(quadList);
			}
		}
		break;
	}

	case 8:
	{
		//option 8: for printing optimized IR
		parser = parser_initialise(grammarInputFile, astRulesFile);
		isParsed = parseOnlySourceCode(&parser, lex);
		quadruple* quadList;
		if (isParsed == PARSED_SUCCESSFULLY)
		{
			Tree ast = createAst(parser);
			createSymbolTables(ast);
			turnOnReportingSemanticErrors(TRUE);
			if (typeExtractorandChecker(ast))
			{
				quadruple* quadList = (quadruple*) malloc(sizeof(quadruple));
				quadList=generateirCode(ast);
				printf("\nBasic Blocks of IR ......\n");
				printf("\n------------------------------------------------------------------------------\n");
				//call optimization module				
				quadList=myOptimization(quadList);
				printf("\nOptimized IR Code......\n");
				//print optimized IR
				print_IRD(quadList);
			}
		}

		break;
	}

	case 9:
	{
 		parser = parser_initialise(grammarInputFile, astRulesFile);
		isParsed = parseOnlySourceCode(&parser, lex);
		quadruple* quadList;
		if (isParsed == PARSED_SUCCESSFULLY)
		{
			Tree ast = createAst(parser);
			createSymbolTables(ast);
			turnOnReportingSemanticErrors(TRUE);
			if (typeExtractorandChecker(ast))
			{
				printf("\nCode compiles successfully..........:)");
				FILE* asmFile = fopen(argv[2], "w");
				quadruple* quadList = (quadruple*) malloc(sizeof(quadruple));
				//generate unoptimized IR
				quadList=generateirCode(ast);
				printf("\n\nStarted asm code generation.");
				//create asm for unoptimized IR
				generateasmCode(quadList,asmFile);
				printf("\n\nFinished asm code generation.");
				printf("\n\nasm code saved in %s.",argv[2]);
			}
		}		
		break;
	}
	case 10:
	{
		//option 10: for generating assembly code with optimization
		
		parser = parser_initialise(grammarInputFile, astRulesFile);
		isParsed = parseOnlySourceCode(&parser, lex);
		quadruple* quadList;
		if (isParsed == PARSED_SUCCESSFULLY)
		{
			Tree ast = createAst(parser);
			createSymbolTables(ast);
			turnOnReportingSemanticErrors(TRUE);
			if (typeExtractorandChecker(ast))
			{
				printf("\nCode compiles successfully..........:)");
				FILE* asmFile = fopen(argv[2], "w");
				quadruple* quadList = (quadruple*) malloc(sizeof(quadruple));
				quadList=generateirCode(ast);
				//call optimization module
				quadList=myOptimization(quadList);
				//generate asm code for optimized IR	
				printf("\n\nStarted asm code generation with optimization.");
				generateasmCode(quadList,asmFile);
				printf("\n\nFinished asm code generation.");
				printf("\n\nasm code saved in %s.",argv[2]);
			}
		}		
		break;
	}
//Note: the module for optimization is implemented. but the output obtained is not correct. there is some mismatch as compared to the expected output. Hence the performance measure comparing optimized and unoptimized code is not implemented
	case 11:
	{
		//option 11: for displaying the performance measures
		printf("the feature to display performance measures not implemented yet");
		break;
	}

	case 12:
		return 0;
		break;
	default:
		printf("Invalid Choice...please enter correct choice (1-8)");
		break;
	}

	char c;
	scanf("%c", &c);
	return 0;
}



/*
case13:
//asm use AST 
parser = parser_initialise(grammarInputFile, astRulesFile);

		isParsed = parseOnlySourceCode(&parser, lex);
		if (isParsed == PARSED_SUCCESSFULLY)
		{
			Tree ast = createAst(parser);
			createSymbolTables(ast);

			turnOnReportingSemanticErrors(TRUE);
			if (typeExtractorandChecker(ast))
			{
				printf("\n\nCode compiles successfully..........:)");
				printf("\n\nGenerating Code......");
				FILE* asmm = fopen(argv[2], "w");
				generateCode(ast, asmm);
				printf("\n\nFinished code generation.");
				//Call code generation here
			}
		}
		break;*/
/*case 5:
//point on simantic analysis using AST
		parser = parser_initialise(grammarInputFile, astRulesFile);
		isParsed = parseOnlySourceCode(&parser, lex);
		if (isParsed == PARSED_SUCCESSFULLY)
		{
			Tree ast = createAst(parser);
			createSymbolTables(ast);
			printf("\n\nRunning semantic analysis....");

			turnOnReportingSemanticErrors(TRUE);
			if (typeExtractorandChecker(ast))
			{

				printf("\n\nCode compiles successfully..........:)");
			}
		}

		break;*/
