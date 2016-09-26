/*
*Batch Number 18
*SWATI SHARMA (2014H112176P)
*SAGAR CHOUDHARI (2014H112183P)
*/
#ifndef _MY_OPTIMIZER_H_
#define _MY_OPTIMIZER_H_

#include "myIRgenerator.h"
//Basic Block Structure
typedef struct basic
{
	int BlockNo;
	quadruple* start;
	quadruple* end;
	struct basic* succ;
}BasicBlock;

typedef struct listnode
{
    BasicBlock* bg;
    struct listnode* next;
}node;
// A structure to represent an adjacency list

typedef struct list
{
    node *succ;
}list;
//CFG Data Structure
typedef struct CFG 
{
	int noofblocks;
	list* arrayofblocks;
}cfg;

typedef struct domnode
{
	int blockno;
	struct domnode* next;
}domnode;

typedef struct domlist
{
	domnode* succc;
}domlist;
//Dominance Tree Structure
typedef struct dominance
{
	int noofblock;
	domlist* arrayofdominator;
}dom;

void createBlocks();
void findLeaderStatements(quadruple* quad);
void createblock();
BasicBlock* emptyblock();
void initblock();
void appendblk(BasicBlock* bb);
BasicBlock* findblock();
cfg* createCFG();
void populateblock();
BasicBlock* findblock(quadruple* temp);
node* listnodepopulate(BasicBlock* bh);
void createdominance(cfg* cfgs);
domnode* nodepopulate(int i);
void printBasicBlock();

#endif;

