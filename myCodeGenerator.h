/*
*Batch Number 18
*SWATI SHARMA (2014H112176P)
*SAGAR CHOUDHARI (2014H112183P)
*/
#ifndef _MYCODEGENERATOR_H_
#define _MYCODEGENERATOR_H_

#include <stdio.h>
#include "Tree.h"
#include "myIRgenerator.h"

void generateasmCode( quadruple* quadList, FILE* asmFile
);
void _generateasmCode(quadruple* quadList);
void initasmRegisters();
int getasmEmptyRegister();
quadruple* _generatewhileasmCode(quadruple* whilequad);
quadruple* _generatefunctionasmCode(quadruple* funcquad);
quadruple* _generatefunctioncallasmCode(quadruple* funcquad);
quadruple* _generateifasmCode(quadruple* ifquad);
void declarationInfoasm();
void initasmBasicIo(fin, asmm);


#endif
