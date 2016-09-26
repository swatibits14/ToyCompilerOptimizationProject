/*
*Batch Number 18
*SWATI SHARMA (2014H112176P)
*SAGAR CHOUDHARI (2014H112183P)
*/


#include "myOptimizer.h"
#include "Boolean.h"

quadruple* quadList; //Quadrupple List
int blockno=1;
BasicBlock* blocklist;//Blocks List
BasicBlock* nextblk;
int noofblock=0;
int loopfound;
int loopstart,loopend;
cfg* cfgs;

void print_IR(quadruple* quadList)
{
	int prevblk=-1;
	int count;
	quadruple* current_quad = quadList;
		if (current_quad == NULL) 
	{
		printf("Nothing to generate\n");
		return;
	}
	printf("Block_No  INST_NO\tINST_TYPE\tINST_OPERATOR\tINST_LHS\tINST_OPND1\tINST_OPND2\n");	
	do 
	{
		if (current_quad->operators == NOP) 
		{
			continue;
		}
		if(current_quad->blkno!=0)
		{	if(current_quad->blkno!=prevblk)
			{
				printf("%d\t\n", current_quad->blkno);//Printing the block of current quadruple
			}
		prevblk=current_quad->blkno;
		}
		printf("         %i\t", current_quad->line);
		count=current_quad->line;
  		switch (current_quad->operators) //Printing Of IR for Each Operator
        	{
			case START:
			{
				printf("        START\t%20s\n", current_quad->result);
				break;
			}
			case ASSIGNMENT:
			{
				printf("        Assignment\tASSIGNMENT %10s %10s \n", current_quad->result, current_quad->operand_1);
				break;
			}
			case MULTIPLY:
				printf("	Multiply\tMULTIPLY   %10s  %10s  %10s\n", current_quad->result, current_quad->operand_1, current_quad->operand_2);
				break;
			case DIVIDE:
				printf("	Divide\tDIVIDE %10s  %10s  %10s\n", current_quad->result, current_quad->operand_1, current_quad->operand_2);
				break;
			case PLUS:					
				printf("	Plus\t PLUS%10s  %10s  %10s\n", current_quad->result, current_quad->operand_1, current_quad->operand_2);
				break;
			case MINUS:
				printf("	Minus\tMINUS %10s  %10s  %10s\n", current_quad->result, current_quad->operand_1, current_quad->operand_2);
				break;
			case GREATER_OR_EQUAL:
				printf("\t%s = (%s >= %s)\n" , current_quad->result,current_quad->operand_1, current_quad->operand_2);
				break;
			case LESS_OR_EQUAL:
				printf("\t%s = (%s <= %s)\n" , current_quad->result,current_quad->operand_1, current_quad->operand_2);
				break;
			case GREATER:
				printf("\t%s = (%s > %s)\n" , current_quad->result,current_quad->operand_1, current_quad->operand_2);
				break;
			case LESS:
				printf("\t%s = (%s < %s)\n" , current_quad->result,current_quad->operand_1, current_quad->operand_2);
				break;
			case NOT_EQUAL:
				printf("\t%s = (%s != %s)\n" , current_quad->result,current_quad->operand_1, current_quad->operand_2);
				break;
			case EQUAL:	     
		                printf("\tEQUAL %s  %10s  %10s)\n" , current_quad->result,current_quad->operand_1, current_quad->operand_2);
				break;
			case IF:   		
				printf("IF 	GOTO	%s   %s\n",current_quad->result,current_quad->operand_1);
				break;
			case GOTO:
				printf("GOTO	GOTO %s\n", current_quad->operand_1);
				break;
			case RETURN:
				printf("\t return: \n");
				break;
			case LABLE: 
				{
					if(current_quad->operand_1 !=NULL && strcmp(current_quad->operand_1,"function")==0)
					{
						printf("%s: %s\n",current_quad->result,current_quad->operand_1);
					}
					else
					{
						printf("%s: \n",current_quad->result);
					}
					break;
				}
			case PRINT: 
				printf("\tprint(%s)\n",current_quad->operand_1);
				break;
			case FUNC_PAR: 
			{
				if(current_quad->operand_2 !=NULL)
				{	
					printf("\t%s = %s , %s\n", current_quad->result, current_quad->operand_1, 
					current_quad->operand_2);
				}
				else
				{
					printf("\t%s = %s \n", current_quad->result, current_quad->operand_1);

				}			
				break;	
			}
			case FUNC_ID: 
			{
				if(current_quad->operand_2 !=NULL)
				{
					printf("\t(%s) = function %s (%s) \n", current_quad->result, 
					current_quad->operand_1,current_quad->operand_2);
				
				}
				else
				{
					printf("\t(%s) = function %s  \n", current_quad->result, current_quad->operand_1);
				}
				break;	
			}
			case FUNC: 
			{		
				if(current_quad->operand_2 !=NULL)
				{
					printf("\t(%s) = call %s  (%s)\n", current_quad->result, current_quad->operand_1, 
					current_quad->operand_2);
				}
				else
				{
					printf("\t(%s) = call %s  \n", current_quad->result, current_quad->operand_1);

				}
				break;	
			}
			case FUNC_SAVE: 
			{		
				if(current_quad->operand_2 !=NULL)
				{	
					printf("\t%s = %s , %s\n", current_quad->result, current_quad->operand_1, 
					current_quad->operand_2);
				}
				else
				{
					printf("\t%s = %s \n", current_quad->result, current_quad->operand_1);
				}	
				break;	
			}
			case FUNC_COMP: 
			{		
				if(current_quad->operand_2 !=NULL)
				{
					printf("\t%s = %s , %s\n", current_quad->result, current_quad->operand_1, 
					current_quad->operand_2);					
				}
				else
				{
					printf("\t%s = %s \n", current_quad->result, current_quad->operand_1);
				}
				break;	
			}
			case EXIT:
			{
				printf("%s\n", current_quad->result);
				break;
			}
			default:
			{
				printf("\tInvalid operation!\n");
				break;
			}
		}
	} while ((current_quad = current_quad->next) != NULL);
	printf("------------------------------------------------------------------------------\n");
	
}


//For Finding Leader Statements For each quadruple whether it is leader or not

void findLeaderStatements(quadruple* quad)
{
	quadList=quad;
	quadruple* current_quad = quadList;
	quadruple* temp;
	if (current_quad == NULL) 
	{
		return;
	}
	current_quad=current_quad->next;
	current_quad->leader=1;	
	current_quad=current_quad->next;
	current_quad->leader=1;	
	
	while ((current_quad=current_quad->next)!= NULL)
	{
		if((current_quad->operators==LABLE)||(current_quad->operators==EXIT))
		{
			current_quad->leader=1;
		}
		if((current_quad->operators==IF)||(current_quad->operators==GOTO))
		{
			temp=current_quad->next;
			temp->leader=1;
		}
		if(current_quad->goto_next!=NULL)
		{
			temp=current_quad->goto_next;
			temp->leader=1;
		}
	}
}

	//Creation of an Empty Block 
BasicBlock* emptyblock()
{
	BasicBlock* bb=(BasicBlock*)malloc(sizeof(BasicBlock));	
	bb->BlockNo=blockno++;
	bb->succ=NULL;
	return bb;		
}
//Initialization of the First Block
void initblock()
{
	nextblk=emptyblock();
}
//Adding the Newly Created Block into the Preveious Block List
void appendblk(BasicBlock* bb)
{
	if (blocklist == NULL) //If List is empty 
	{
		blocklist = bb;//Add the Block as the First Block of BlockList
	} 
	else 
	{
		BasicBlock* bblock = blocklist;
		while (bblock->succ) 
		{
			bblock=bblock->succ;
		}
		bblock->succ = bb;
	}
}
//Creation of Blocks
void createBlocks()
{
	quadruple* current_quad = quadList;
	quadruple* temp;
	quadruple* start;
	quadruple* end;
	initblock();
	current_quad=current_quad->next;
	do
	{
		if(current_quad->operators==NOP)
		{
			break;
		}
		if(current_quad->leader==1) //If Leader is one then put the current quadruple as start point of Block
		{
			start=current_quad;	
			temp=current_quad->next;		
			if(current_quad->operators==EXIT)//Start and End will remain same for this exit block 
			{	
				end=current_quad;
				createblock(start,end);
				break;
			}
			if(temp->leader==1)//If leader is following another leader
			{
				end=current_quad;
				createblock(start,end);
			}
			else
			{ 
				current_quad=current_quad->next;
				while(current_quad->leader!=1)
				{
					if(current_quad->next->leader==1)
					{
						end=current_quad;	
						createblock(start,end);
						break;
					}
					current_quad=current_quad->next;
				}
			}	
		}
	}while ((current_quad = current_quad->next) != NULL);
}
//Creation of a new block with start and end passed as parameters
void createblock(quadruple* start,quadruple* end)
{
	BasicBlock* block=nextblk;
	block->start=start;
	block->end=end;
	appendblk(block);
	nextblk=emptyblock();
}
//Putting Block No in the start and end quadruples for let them know that which quadruple they belong
void populateblock()  
{
	BasicBlock* cblk=blocklist;
	BasicBlock* bb;
	quadruple* temp;
	while(cblk!=NULL)
	{
		cblk->start->blkno=cblk->BlockNo;
		cblk->end->blkno=cblk->BlockNo;
		noofblock++;
		cblk=cblk->succ;
	}
	print_IR(quadList);
}

//Finding the Block which contains the quadruple temp
BasicBlock* findblock(quadruple* temp)
{
	BasicBlock* te=blocklist;	
	int t1;
	t1=temp->blkno;
	te=te->succ;
	while((te)!=NULL)
	{
		if(te->BlockNo==t1)
		{
			//te=te->succ;
			break;
		}
		te=te->succ;
	}
	return te;
}
//Creating CFG from Basic Blocks
cfg* createCFG()
{
	BasicBlock* bb=blocklist;
	quadruple* temp;
	BasicBlock* bd;
	node* newnode;
	//cfg* cfgs;
	int i,b;
	cfgs=(cfg*)malloc(sizeof(cfg));
	cfgs->noofblocks=noofblock;
	b=noofblock;
	cfgs->arrayofblocks=(list*)malloc(b*sizeof(list));//allocating memory for each Basic Block
	for(i=0;i<noofblock;i++)
	{
		cfgs->arrayofblocks[i].succ=NULL;
		
	}
	
	for(i=1;i<b;i++)
	{
		if(bb->end->operators!=GOTO)//If Operator is not of goto type
		{		

			newnode=listnodepopulate(bb->succ);//Put the immediate successor in the List 
			cfgs->arrayofblocks[i].succ=newnode;
			if(bb->end->goto_next!=NULL)
			{
				temp=bb->end->goto_next;
				bd=findblock(temp);
				cfgs->arrayofblocks[i].succ->next=listnodepopulate(bd);
			}
		}
		else
		{
			temp=bb->end->goto_next;
			bd=findblock(temp);
			cfgs->arrayofblocks[i].succ=listnodepopulate(bd);
		}
		bb=bb->succ;
	}
	printf("\nCFG of the blocks\n"); 
	printf("\nBlocK \t:\tSuccessors\n");
	for(i=1;i<b;i++)
	{
		printf("\nB%d\t:\tB%d",i,cfgs->arrayofblocks[i].succ->bg->BlockNo);
		if(cfgs->arrayofblocks[i].succ->next!=NULL)
		{
			printf(", B%d",cfgs->arrayofblocks[i].succ->next->bg->BlockNo);
		}
	}
	printf("\n");
return cfgs;
	
}
//CFG Link List node Creation	
node* listnodepopulate(BasicBlock* bh)
{
    node* newNode =(node*) malloc(sizeof(node));
    newNode->bg = bh;
    newNode->next = NULL;
    return newNode;
}

//Dominance Tree Creation
void createdominance(cfg* cfgs)
{

	int i,c,d=0,b;
	dom* dominance;
	dominance=(dom*)malloc(sizeof(dom));
	dominance->noofblock=noofblock;
	b=noofblock;
	dominance->arrayofdominator=(domlist*)malloc((b+1)*sizeof(domlist));
	for(i=0;i<=b;i++)
	{
		dominance->arrayofdominator[i].succc=NULL;
	}
	for(i=1;i<b;i++)
	{
		c=cfgs->arrayofblocks[i].succ->bg->BlockNo;
		if(cfgs->arrayofblocks[i].succ->next!=NULL)
		{
			d=cfgs->arrayofblocks[i].succ->next->bg->BlockNo;
		}
		if(i>c)
		{
			loopfound=1;
			loopstart=c;
			loopend=i;
		}
		else if(cfgs->arrayofblocks[i].succ->next!=NULL&&dominance->arrayofdominator[d].succc==NULL)
		{	
			dominance->arrayofdominator[d].succc=nodepopulate(i);
			dominance->arrayofdominator[c].succc=nodepopulate(i);
		}	
		else
		{
			if((dominance->arrayofdominator[c].succc==NULL))
			{
				dominance->arrayofdominator[c].succc=nodepopulate(i);			
			}	
			else
			{			
				dominance->arrayofdominator[c].succc->next=nodepopulate(i);
			}
		}
		d=0;
	}
	for(i=2;i<=b;i++)
	{
		domnode* dominator=dominance->arrayofdominator[i].succc;
		while(dominator->next!=NULL)
		{
			dominator=dominator->next;
		}
		dominator->next=dominance->arrayofdominator[dominator->blockno].succc;
	}
	printf("\nDominance Tree");
	for(i=2;i<=b;i++)
	{
		domnode* domi=dominance->arrayofdominator[i].succc;
		
printf("\nB%d\t:",i);
		while(domi!=NULL)
		{ 
			printf("\tB%d",domi->blockno);
			domi=domi->next;
		}
	}
	printf("\n%d  %d\n",loopstart,loopend);
	myoptimization(dominance);
}
//Dominance Tree Node creation for the Block
domnode* nodepopulate(int i)
{
	domnode* newNode =(struct domnode*) malloc(sizeof(struct domnode));
	newNode->blockno = i;
	newNode->next = NULL;
	return newNode;
}
//Optimization for Loop Invariant Code Motion 

//Detection of loop through the Dominance Tree and finding the Blocks inside the Loop. 
void myoptimization(dom* dominance)
{
	quadruple* quad=quadList;
	quadruple* quad1=quadList;
	quadruple* temp;
	int i=0,j,a[20],n;
	domnode* domi;
	BasicBlock* prevblk;
	int no;
	char* t1;
	char* t2;
	int def;
	domi=dominance->arrayofdominator[loopend].succc;
	a[0]=loopstart;
	i=1;
	Boolean oper1=FALSE, oper2=FALSE,optr=FALSE;
	while(domi->blockno!=loopstart)	
	{
		a[i]=domi->blockno;
		i++;
		domi=domi->next;
	}
	a[i]=loopend;
	n=i;
	for(j=0;j<=n;j++)
	printf("   %d   ",a[j]);
	
	while(quad->blkno!=(loopstart+2))
		quad=quad->next;
	quad=quad->next;	
	while(quad1->blkno!=(loopstart+2))
		quad1=quad1->next;
	quad1=quad1->next;
	quad1=quad1->next;	
		
	printf("%d",quad->line);
	/*while(quad->next!=NULL)
	{
		if(quad->operator==ASSIGNMENT)
		{
			while(quad1->next!=NULL)
			{
				if(quad1->operator==ASSIGNMENT)
				{	if((quad1->result==quad->operand_1)
					{
						temp=quad;	
					}	
						
						
	
	




	/*while((quad=quad->next)!=NULL)
	{

		if(quad->operators==ASSIGNMENT)
		{
			t1=quad->operand_1;
			if(quad->operand_2!=NULL)
			t2=quad->operand_2;			
			
		
		while((quad1=quad1->next)!=NULL)
		{
					
			if(quad1->operators==ASSIGNMENT)
			{
				if((quad->line!=quad1->line)&&((quad1->result==t1)||(quad1->result==t1)))
				{
					quad->def=1;
					printf("%d",quad->def);	
				}
			}
		
		}
			quad->def=2;
		}
		quad->def=0;


	}*/			
				
				
				
	
	/*while(cblk->BlockNo!=a[0])
	{
		cblk=cblk->succ;
	}
	cblk=cblk->succ;
	while(cblk->BlockNo!=a[n])
	{
		while(tblk->BlockNo!=cblk->BlockNo)
		{
			tblk=tblk->succ;
		}			
		t1=cblk->start;
		if(t1->operators==ASSIGNMENT || t1->operators==PLUS || t1->operators==MINUS || t1->operators==MULTIPLY || t1->operators==DIVIDE)
		{
			while(tblk->BlockNo!=a[n])
			{
				t2=tblk->start;
				while(t1->line != t2->line)
				{
					t2=t2->next;
				}
				t2=t2->next;
				while(t2->line <= tblk->end)
				{
					if(t1->operand_1!= NULL && t2->result!= NULL && strcmp(t1->operand_1,t2->result)==0)
					{
						oper1=TRUE;
						break;
					}
					t2=t2->next;
				}
				t2=tblk->start;
				while(t1->line != t2->line)
				{
					t2=t2->next;
				}
				t2=t2->next;
				while(t2->line<=tblk->end)
				{
					if(t1->operand_2!= NULL && t2->result!= NULL && strcmp(t1->operand_1,t2->result)==0)
					{
						oper2=TRUE;
						break;
					}
					t2=t2->next;
				}	
				t2=tblk->start;
				while(t1->line != t2->line)
				{
					t2=t2->next;
				}
				t2=t2->next;
				while(t2->line<=tblk->end)
				{
					if(t1->result!= NULL && t2->result!= NULL && strcmp(t1->result,t2->result)==0)
					{
						optr=TRUE;
						break;
					}
					t2=t2->next;
				}
				tblk=tblk->succ;
			}
			if(oper1==FALSE && oper2==FALSE && optr==FALSE)
			{
				quad=t1;
				quadruple* loop=prevblk->start;
				while(loop->line!=t1->line-1)
				{
					loop=loop->next;
				}
				//quad->next=loop->next;
				loop->next=t1;
					
			}
			else if(oper1==FALSE && oper2==FALSE && optr==TRUE)
			{
				char* temp;
				temp=generatevariable();
				quad=new_empty_quad(); 
				quad->result=temp;
				quad->operators=t1->operators;
				quad->operand_1=t1->operand_1;
				quad->operand_2=t1->operand_2;
				t1->operators=ASSIGNMENT;
				t1->operand_1=temp;
				t1->operand_2=NULL;
			}
			prevblk=dominance->arrayofdominator[cblk->BlockNo].succc;
			quadruple* loop=prevblk->start;
			while(loop->line!=prevblk->end->line)
			{
				loop=loop->next;
			}
			quad->next=loop->next;
			loop->next=quad;
		}
		int count=0;
		quadruple* current_quadruple=quadList;
		while(current_quadruple!=NULL)
		{
			current_quadruple->line=count;
			count++;
			current_quadruple=current_quadruple->next;
		}
		cblk=cblk->succ;
	}*/
}
