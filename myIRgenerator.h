/*
*Batch Number 18
*SWATI SHARMA (2014H112176P)
*SAGAR CHOUDHARI (2014H112183P)
*/
#ifndef _MY_IR_GENERATOR_H
#define _MY_IR_GENERATOR_H

#include <stdio.h>
#include "Tree.h"
#include "Boolean.h"
//Quadruple Type
typedef enum a_quad_type 
{
		START,EXIT,
		NOP, ASSIGNMENT,
		MULTIPLY, DIVIDE,
		PLUS, MINUS,
		GREATER_OR_EQUAL, LESS_OR_EQUAL, EQUAL, NOT_EQUAL, GREATER, LESS,
		AND,OR,NOT,
		GOTO,IF,LABLE,RETURN,
		PRINT,FUNC_PAR,FUNC_ID,FUNC,FUNC_SAVE,FUNC_COMP
		
} quad_type;
//Quadruple Structure
typedef struct a_quadruple
{
	quad_type type;
	char* operand_1;
	char* operand_2;
	quad_type operators;
	char* result;
	int line;
	int leader;
	struct a_quadruple* next;
	struct a_quadruple* goto_next;
	int blkno;
	int def;
	Boolean loopinv;
} quadruple;

void init_quadruples();	
void generateircode( Tree ast);
char* generatequadruple(TreeLink astRoot);
quadruple* new_quadruple(char* result, quad_type operators, char* operand_1, char* operand_2);
void compile_quadruplecode();
void append_quadrupel(quadruple* quad);
quadruple* new_empty_quad();
void printSymbolTableIR();
void genquad(TreeLink astf);
char* returnstring(char* value);
void printQuadruple();
quadruple* myOptimization(quadruple* quadruple);
void displaycfg(quadruple* quadruple);

#endif
