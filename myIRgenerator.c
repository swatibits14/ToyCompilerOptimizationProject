/*
*Batch Number 18
*SWATI SHARMA (2014H112176P)
*SAGAR CHOUDHARI (2014H112183P)
*/
#include "SymbolTableDef.h"
#include "ASTDef.h"
#include "typeChecker.h"
#include "myIRgenerator.h"
#include "gvl.h" 
#include "Tree.h"
#include "myOptimizer.h"
#include "Boolean.h"
int current_quad_line=0;
quadruple* quadList;
quadruple* next_quad;
LinkList listOfSymbols;
char* function_jump;
char* temp;
FILE* irg;

//create a new empty quadruple
quadruple* new_empty_quad() 
{
	quadruple* quad = (quadruple*) malloc(sizeof(quadruple));
	quad->operand_1 = NULL;
	quad->operand_2 = NULL;
	quad->operators = NOP;
	quad->result = NULL;
	quad->next = NULL;
	quad->goto_next = NULL;
	quad->line = current_quad_line++;
	quad->leader=0;
	quad->blkno=0;
	quad->def=0;
	quad->loopinv=FALSE;
	return quad;
}

//initialize quadruple 
void init_quadruples()
{
	next_quad = new_empty_quad();
}

//add details in the new empty quadruples
quadruple* new_quadruple(char *result, quad_type operators, char *operand_1, char *operand_2) 
{
	quadruple* quad = next_quad;
	quad->operand_1 = operand_1;
	quad->operand_2 = operand_2;
	quad->operators = operators;
	quad->result=result;
	append_quadrupel(quad);
	next_quad = new_empty_quad();
	return quad;
}
//append creaded quadruple in the quadruple list
void append_quadrupel(quadruple* quad) 
{
       
	if (quadList == NULL) 
	{
		quadList = quad;
	} 
	else 
	{
	quadruple* current_quad = quadList;
		while (current_quad->next) 
		{
		current_quad = current_quad->next;
		}
	current_quad->next = quad;
	}
}

//print quadruple list(IR) on the scree
void print_IRD(quadruple* quadList)
{

	int count;
	printf("\nBlock_No   Inst_No    Inst_Type     Inst_Op      Inst_LHS      Inst_Opnd1      Inst_Opnd2\n");
	quadruple* current_quad = quadList;
		if (current_quad == NULL) 
	{
		printf("Nothing to generate\n");
		return;
	}
	do 
	{
		if (current_quad->operators == NOP) 
		{
			continue;
		}
	
		count=current_quad->line;
  		switch (current_quad->operators) 
        	{
			case START:
			{
				printf("%d    \t    %d  \t   Start    \t    %s\n",current_quad->blkno,current_quad->line, current_quad->result);
				break;
			}
			case ASSIGNMENT:
			{
				printf("\tAssignment%s = %s \n", current_quad->result, current_quad->operand_1);
				break;
			}
			case MULTIPLY:
				printf("\tMultiply%s = %s * %s\n", current_quad->result, current_quad->operand_1, current_quad->operand_2);
				break;
			case DIVIDE:
				printf("\tDivide%s = %s / %s\n", current_quad->result, current_quad->operand_1, current_quad->operand_2);
				break;
			case PLUS:					
				printf("\tPlus%s = %s + %s\n", current_quad->result, current_quad->operand_1, current_quad->operand_2);
				break;
			case MINUS:
				printf("\tMinus%s = %s - %s\n", current_quad->result, current_quad->operand_1, current_quad->operand_2);
				break;
			case GREATER_OR_EQUAL:
				printf("\tGE%s = (%s >= %s)\n" , current_quad->result,current_quad->operand_1, current_quad->operand_2);
				break;
			case LESS_OR_EQUAL:
				printf("\tLE%s = (%s <= %s)\n" , current_quad->result,current_quad->operand_1, current_quad->operand_2);
				break;
			case GREATER:
				printf("\tG%s = (%s > %s)\n" , current_quad->result,current_quad->operand_1, current_quad->operand_2);
				break;
			case LESS:
				printf("\tL%s = (%s < %s)\n" , current_quad->result,current_quad->operand_1, current_quad->operand_2);
				break;
			case NOT_EQUAL:
				printf("\tNE%s = (%s != %s)\n" , current_quad->result,current_quad->operand_1, current_quad->operand_2);
				break;
			case EQUAL:	     
		                printf("\tE%s = (%s == %s)\n" , current_quad->result,current_quad->operand_1, current_quad->operand_2);
				break;
			case IF:   		
				printf("\tIF( %s ) GOTO %s\n",current_quad->operand_1,current_quad->result);
				break;
			case GOTO:
				printf("\tGOTO %s %d\n", current_quad->operand_1,current_quad->goto_next->line);
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

//save quadruple in the file
void compile_quadruplecode() 
{
	int count;
	quadruple* current_quad = quadList;

	printf("\nQuadruple Code saved in file: IR_quadruple.txt\n");
	printf("------------------------------------------------------------------------------\n");
	if (current_quad == NULL) 
	{
		printf("Nothing to generate\n");
		return;
	}
	do 
	{
		if (current_quad->operators == NOP) 
		{
			continue;
		}
		fprintf(irg,"%i\t", current_quad->line);
		count=current_quad->line;
  		switch (current_quad->operators) 
        	{
			case START:
			{
				fprintf(irg,"%s\n", current_quad->result);
				break;
			}
			case ASSIGNMENT:
			{
				fprintf(irg,"\t%s = %s \n", current_quad->result, current_quad->operand_1);
				break;
			}
			case MULTIPLY:
				fprintf(irg,"\t%s = %s * %s\n", current_quad->result, current_quad->operand_1, current_quad->operand_2);
				break;
			case DIVIDE:
				fprintf(irg,"\t%s = %s / %s\n", current_quad->result, current_quad->operand_1, current_quad->operand_2);
				break;
			case PLUS:					
				fprintf(irg,"\t%s = %s + %s\n", current_quad->result, current_quad->operand_1, current_quad->operand_2);
				break;
			case MINUS:
				fprintf(irg,"\t%s = %s - %s\n", current_quad->result, current_quad->operand_1, current_quad->operand_2);
				break;
			case GREATER_OR_EQUAL:
				fprintf(irg,"\t%s = (%s >= %s)\n" , current_quad->result,current_quad->operand_1, current_quad->operand_2);
				break;
			case LESS_OR_EQUAL:
				fprintf(irg,"\t%s = (%s <= %s)\n" , current_quad->result,current_quad->operand_1, current_quad->operand_2);
				break;
			case GREATER:
				fprintf(irg,"\t%s = (%s > %s)\n" , current_quad->result,current_quad->operand_1, current_quad->operand_2);
				break;
			case LESS:
				fprintf(irg,"\t%s = (%s < %s)\n" , current_quad->result,current_quad->operand_1, current_quad->operand_2);
				break;
			case NOT_EQUAL:
				fprintf(irg,"\t%s = (%s != %s)\n" , current_quad->result,current_quad->operand_1, current_quad->operand_2);
				break;
			case EQUAL:	     
		                fprintf(irg,"\t%s = (%s == %s)\n" , current_quad->result,current_quad->operand_1, current_quad->operand_2);
				break;
			case IF:   		
				fprintf(irg,"\tIF( %s ) GOTO %s\n",current_quad->operand_1,current_quad->result);
				break;
			case GOTO:
				fprintf(irg,"\tGOTO %s\n", current_quad->operand_1);
				break;
			case RETURN:
				fprintf(irg,"\t return: \n");
				break;
			case LABLE: 
				{
					if(current_quad->operand_1 !=NULL && strcmp(current_quad->operand_1,"function")==0)
					{
						fprintf(irg,"%s: %s\n",current_quad->result,current_quad->operand_1);
					}
					else
					{
						fprintf(irg,"%s: \n",current_quad->result);
					}
					break;
				}
			case PRINT: 
				fprintf(irg,"\tprint(%s)\n",current_quad->operand_1);
				break;
			case FUNC_PAR: 
			{
				if(current_quad->operand_2 !=NULL)
				{	
					fprintf(irg,"\t%s = %s , %s\n", current_quad->result, current_quad->operand_1, 
					current_quad->operand_2);
				}
				else
				{
					fprintf(irg,"\t%s = %s \n", current_quad->result, current_quad->operand_1);
				}			
				break;	
			}
			case FUNC_ID: 
			{
				if(current_quad->operand_2 !=NULL)
				{
					fprintf(irg,"\t(%s) = function %s (%s) \n", current_quad->result, 
					current_quad->operand_1,current_quad->operand_2);
				
				}
				else
				{
					fprintf(irg,"\t(%s) = function %s  \n", current_quad->result, current_quad->operand_1);
				}
				break;	
			}
			case FUNC: 
			{		
				if(current_quad->operand_2 !=NULL)
				{
					fprintf(irg,"\t(%s) = call %s  (%s)\n", current_quad->result, current_quad->operand_1, 
					current_quad->operand_2);
				}
				else
				{
					fprintf(irg,"\t(%s) = call %s  \n", current_quad->result, current_quad->operand_1);

				}
				break;	
			}
			case FUNC_SAVE: 
			{		
				if(current_quad->operand_2 !=NULL)
				{	
					fprintf(irg,"\t%s = %s , %s\n", current_quad->result, current_quad->operand_1, current_quad->operand_2);
				}
				else
				{
					fprintf(irg,"\t%s = %s \n", current_quad->result, current_quad->operand_1);
				}	
				break;	
			}
			case FUNC_COMP: 
			{		
				if(current_quad->operand_2 !=NULL)
				{
					fprintf(irg,"\t%s = %s , %s\n", current_quad->result, current_quad->operand_1, 
					current_quad->operand_2);					
				}
				else
				{
					fprintf(irg,"\t%s = %s \n", current_quad->result, current_quad->operand_1);
				}
				break;	
			}
			case EXIT:
			{
				fprintf(irg,"%s\n", current_quad->result);
				break;
			}
			default:
			{
				printf("\tInvalid operation!\n");
				break;
			}
		}
	} while ((current_quad = current_quad->next) != NULL);
	
	fclose(irg);
	
}

//generate IR code- function called by driver	
quadruple* generateirCode(Tree ast)
{
	int i;
	quadruple *temp;

	irg = fopen("IR_quadruple.txt", "w");
	quadList=new_empty_quad();
	init_quadruples(ast);
	temp=new_quadruple("Start",START,NULL,NULL);
	for (i = 0; i < ast.root->no_of_children; i++)
	{
		genquad(ast.root->children[i]);
	}
	temp=new_quadruple("Exit",EXIT,NULL,NULL);
	//print_IRD(quadList);
	return quadList;
}

//create and display basic block and CFG dominance tree which calls optimization module
quadruple* myOptimization(quadruple* quadruple)
{
	cfg* cfgs;
	quadList=quadruple;
	findLeaderStatements(quadList);
	createBlocks();
	populateblock();
	cfgs=createCFG();
	createdominance(cfgs);
	return quadList;
}

//create and display basic block and CFG.
void displaycfg(quadruple* quadruple)
{
	cfg* cfgs;
	quadList=quadruple;
	findLeaderStatements(quadList);
	createBlocks();
	populateblock();
	//cfgs=createCFG();
}

//convert AST to quadruples
void genquad(TreeLink astf)
{
	char *temp1,*temp2,*inp1,*inp2,*temp3,*temp4;
	int j,k;
	TreeLink astg,asth;
	quadruple *quad,*quad2,*tempo;
	char *label1,*label2;
//assignment operations
	if(strcmp(((ASTNodeData*)astf->data)->symbol->symbolName, "ASSIGNOP") == 0)
	{
		//function call 
		if(strcmp(((ASTNodeData*)astf->children[1]->data)->symbol->symbolName,"<funCallStmt>")==0)
		{
			asth=astf->children[0];
			astg=astf->children[1];
			if(strcmp(((ASTNodeData*)astf->children[0]->data)->symbol->symbolName, "<leftHandSide_listVar>") == 0)
			{
				if(asth->no_of_children==2)
				{
					inp1=returnstring(((ASTNodeData*)asth->children[0]->data)->tokenInfo.lexeme);
					inp2=returnstring(((ASTNodeData*)asth->children[1]->data)->tokenInfo.lexeme);
					if(strcmp(((ASTNodeData*)asth->children[0]->data)->symbol->symbolName ,"ID")==0 &&
						 strcmp(((ASTNodeData*)asth->children[1]->data)->symbol->symbolName ,"ID")==0)
					{	
						temp=generatevariable();
						tempo=new_quadruple(temp,FUNC_SAVE,inp1,inp2);
					}
				}
				else 
				{	
					inp1=returnstring(((ASTNodeData*)asth->children[0]->data)->tokenInfo.lexeme);
					inp2=returnstring(((ASTNodeData*)asth->children[1]->data)->tokenInfo.lexeme);
					if(strcmp(((ASTNodeData*)asth->children[0]->data)->symbol->symbolName ,"ID")==0 &&
						 strcmp(((ASTNodeData*)asth->children[1]->data)->symbol->symbolName ,"ID")==0)

					{	
						temp=generatevariable();
						tempo=new_quadruple(temp,FUNC_SAVE,inp1,inp2);
					}
					for(k=2;k<asth->no_of_children;k++)
					{

						inp1=returnstring(((ASTNodeData*)asth->children[k]->data)->tokenInfo.lexeme);
						if(strcmp(((ASTNodeData*)asth->children[k]->data)->symbol->symbolName ,"ID")==0)
						{	
							temp1=generatevariable();
							tempo=new_quadruple(temp1,FUNC_SAVE,temp,inp1);
							temp=temp1;
						}
					}

				}
			}
			else
			{
				inp1=returnstring(((ASTNodeData*)astf->children[0]->data)->tokenInfo.lexeme);
				if(strcmp(((ASTNodeData*)astf->children[0]->data)->symbol->symbolName ,"ID")==0 )
					{	
						temp=generatevariable();
						tempo=new_quadruple(temp,FUNC_SAVE,inp1,NULL);
					}

			}
			if(astg->no_of_children==2)
			{
				inp1=returnstring(((ASTNodeData*)astg->children[1]->data)->tokenInfo.lexeme);
				if(strcmp(((ASTNodeData*)astg->children[1]->data)->symbol->symbolName ,"ID")==0|| 
		                    (strcmp(((ASTNodeData*)astg->children[1]->data)->symbol->symbolName,"RNUM")==0) || 
        		            (strcmp(((ASTNodeData*)astg->children[1]->data)->symbol->symbolName ,"ID")==0))
				{	
					temp2=generatevariable();
					tempo=new_quadruple(temp2,FUNC_COMP,inp1,NULL);
				}
			}
			else 
			{
				inp1=returnstring(((ASTNodeData*)astg->children[1]->data)->tokenInfo.lexeme);
				inp2=returnstring(((ASTNodeData*)astg->children[2]->data)->tokenInfo.lexeme);
				if((strcmp(((ASTNodeData*)astg->children[1]->data)->symbol->symbolName ,"ID")==0|| 
		                    (strcmp(((ASTNodeData*)astg->children[1]->data)->symbol->symbolName,"RNUM")==0) || 
        		            (strcmp(((ASTNodeData*)astg->children[1]->data)->symbol->symbolName ,"ID")==0))
				&&
				    (strcmp(((ASTNodeData*)astg->children[2]->data)->symbol->symbolName ,"ID")==0|| 
		                    (strcmp(((ASTNodeData*)astg->children[2]->data)->symbol->symbolName,"RNUM")==0) || 
        		            (strcmp(((ASTNodeData*)astg->children[2]->data)->symbol->symbolName ,"ID")==0)))
				{	
					temp2=generatevariable();
					tempo=new_quadruple(temp2,FUNC_COMP,inp1,inp2);
				}
				for(k=3;k<astg->no_of_children;k++)
				{
					inp1=returnstring(((ASTNodeData*)astg->children[k]->data)->tokenInfo.lexeme);
					if((strcmp(((ASTNodeData*)astg->children[k]->data)->symbol->symbolName ,"ID")==0|| 
		                    (strcmp(((ASTNodeData*)astg->children[k]->data)->symbol->symbolName,"RNUM")==0) || 
        		            (strcmp(((ASTNodeData*)astg->children[k]->data)->symbol->symbolName ,"ID")==0)))
					{	
						temp3=generatevariable();
						tempo=new_quadruple(temp3,FUNC_COMP,temp2,inp1);
						temp2=temp3;
					}
				}
				
			}
			tempo=new_quadruple(temp,FUNC,
					((ASTNodeData*)astg->children[0]->data)->tokenInfo.lexeme,temp2);
			
		}
		else if ((strcmp(((ASTNodeData*)astf->children[1]->data)->symbol->symbolName ,"NUM")==0) || 
                    (strcmp(((ASTNodeData*)astf->children[1]->data)->symbol->symbolName,"RNUM")==0) || 
                    (strcmp(((ASTNodeData*)astf->children[1]->data)->symbol->symbolName ,"ID")==0))
		{
			quad=new_quadruple(((ASTNodeData*)astf->children[0]->data)->tokenInfo.lexeme,ASSIGNMENT,
                                           ((ASTNodeData*)astf->children[1]->data)->tokenInfo.lexeme,NULL);
		}
		else
 		{
		 	temp=generatequadruple(astf->children[1]);
			quad=new_quadruple(((ASTNodeData*)astf->children[0]->data)->tokenInfo.lexeme,ASSIGNMENT,temp,NULL);
        	}
	}
//for if-else construct
	else if(strcmp(((ASTNodeData*)astf->data)->symbol->symbolName, "<ifStmt>") == 0)
	{      
		char *label1,*label2,*label3;
		
		quadruple *quad1,*quad2,*quad3,*quad4,*quad5,*quad6;
	
		temp=generatequadruple(astf->children[0]);
		label1=generatelable();
		quad=new_quadruple(label1,IF,temp,NULL);
		label2=generatelable();
		quad1=new_quadruple(NULL,GOTO,label2,NULL);
		quad6=new_quadruple(label1,LABLE,"ifstart",NULL);
		label3=generatelable();
		astg=astf->children[1];
		for(j = 0; j < astg->no_of_children; j++)
		{
			asth=astg->children[j];	
			genquad(asth);			
		}
		quad3=new_quadruple(NULL,GOTO,label3,NULL);
		if(astf->children[2]!=NULL)
		{
			quad2=new_quadruple(label2,LABLE,"elsestart",NULL);
			astg=astf->children[2];
			for(j = 0; j < astg->no_of_children; j++)
			{
				asth=astg->children[j];	
				genquad(asth);			
			}
			quad4=new_quadruple(NULL,GOTO,label3,NULL);
		}
		quad5=new_quadruple(label3,LABLE,"postif",NULL);
		quad->goto_next=quad6;		
		quad1->goto_next=quad2;
		quad4->goto_next=quad5;
		quad3->goto_next=quad5;
	}
//for while construct
	else if(strcmp(((ASTNodeData*)astf->data)->symbol->symbolName, "<whileStmt>") == 0)
	{      
		char *label1,*label2,*label3;
		int k;
		quadruple *quad1,*quad2,*quad3,*quad4,*quad5;
		label1=generatelable();		
		quad=new_quadruple(label1,LABLE,"whilelabel",NULL);
		temp=generatequadruple(astf->children[0]);
		label2=generatelable();
		quad1=new_quadruple(label2,IF,temp,NULL);
		label3=generatelable();
		quad2=new_quadruple(NULL,GOTO,label3,NULL);
		quad3=new_quadruple(label2,LABLE,"whilestart",NULL);
		astg=astf->children[1];
		for(j = 0; j < astg->no_of_children; j++)
		{
			asth=astg->children[j];	
			genquad(asth);			
		}
		quad4=new_quadruple(NULL,GOTO,label1,NULL);
		quad5=new_quadruple(label3,LABLE,"afterwhilelabel",NULL);
		quad1->goto_next=quad3;	
		quad2->goto_next=quad5;	
		quad4->goto_next=quad;
	}
//for function defination
	else if(strcmp(((ASTNodeData*)astf->data)->symbol->symbolName, "<functionDef>") == 0)
	{      
		char *label1,*label2,*label3,*temp1;
		int k;
		quadruple *quad1,*quad2,*quad3,*quad4,*quad5;
		label2=generatelable();	
		quad1=new_quadruple(NULL,GOTO,label2,NULL);
		function_jump=label2;
		label1=generatelable();		
		quad=new_quadruple(label1,LABLE,"function",NULL);		
		temp=generatequadruple(astf->children[0]);
		temp1=generatequadruple(astf->children[2]);
		quad1=new_quadruple(temp,FUNC_ID,((ASTNodeData*)astf->children[1]->data)->tokenInfo.lexeme,temp1);
		astg=astf->children[3];
		genquad(astg);	
		tempo=new_quadruple(NULL,RETURN,NULL,NULL);	
		quad5=new_quadruple(function_jump,LABLE,NULL,NULL);
	}
	else if(strcmp(((ASTNodeData*)astf->data)->symbol->symbolName, "<stmtsAndFunctionDefs>") == 0)
	{      
		for(j = 0; j < astf->no_of_children; j++)
		{
	        	asth=astf->children[j];	
			genquad(asth);			
		}
	}
//for print statement
	else if(strcmp(((ASTNodeData*)astf->data)->symbol->symbolName, "PRINT") == 0)
	{      
		quad=new_quadruple(NULL,PRINT,((ASTNodeData*)astf->children[0]->data)->tokenInfo.lexeme,NULL);
	}
}

	

// populating quadruple, generateing temporary variables on the fly and adding them to symbol table
char* generatequadruple(TreeLink astRoot)
{
	quad_type OPERATOR;
	char *temp;
	char *temp1;
	quadruple *tempo;
	SymbolTableEntry* entry = createSymbolTableEntry();
	ASTNodeData* data=((ASTNodeData*)astRoot->data);

	if(strcmp(((ASTNodeData*)astRoot->data)->symbol->symbolName, "PLUS") == 0)
		OPERATOR=PLUS;
	else if (strcmp(((ASTNodeData*)astRoot->data)->symbol->symbolName, "MUL") == 0)
		OPERATOR=MULTIPLY;
	else if (strcmp(((ASTNodeData*)astRoot->data)->symbol->symbolName, "MINUS") == 0)
		OPERATOR=MINUS;
	else if (strcmp(((ASTNodeData*)astRoot->data)->symbol->symbolName, "DIV") == 0)
		OPERATOR=DIVIDE;
	else if(strcmp(((ASTNodeData*)astRoot->data)->symbol->symbolName, "LT") == 0)
		OPERATOR=LESS;
	else if (strcmp(((ASTNodeData*)astRoot->data)->symbol->symbolName, "GT") == 0)
		OPERATOR=GREATER;
	else if (strcmp(((ASTNodeData*)astRoot->data)->symbol->symbolName, "LE") == 0)
		OPERATOR=LESS_OR_EQUAL;
	else if (strcmp(((ASTNodeData*)astRoot->data)->symbol->symbolName, "GE") == 0)
		OPERATOR=GREATER_OR_EQUAL;
	else if (strcmp(((ASTNodeData*)astRoot->data)->symbol->symbolName, "EQ") == 0)
		OPERATOR=EQUAL;
	else if (strcmp(((ASTNodeData*)astRoot->data)->symbol->symbolName, "NE") == 0)
		OPERATOR=NOT_EQUAL;
	else 
		OPERATOR=NOP;
	if(OPERATOR != NOP)
	{
		if((strcmp(((ASTNodeData*)astRoot->children[0]->data)->symbol->symbolName ,"NUM")==0)||
		  (strcmp(((ASTNodeData*)astRoot->children[0]->data)->symbol->symbolName,"RNUM")==0)||
		  (strcmp(((ASTNodeData*)astRoot->children[0]->data)->symbol->symbolName ,"ID")==0))
		{
			if((strcmp(((ASTNodeData*)astRoot->children[1]->data)->symbol->symbolName ,"NUM")==0) ||
		          (strcmp(((ASTNodeData*)astRoot->children[1]->data)->symbol->symbolName,"RNUM")==0) ||
		          (strcmp(((ASTNodeData*)astRoot->children[1]->data)->symbol->symbolName ,"ID")==0))
			{
				temp=generatevariable();
				tempo=new_quadruple(temp,OPERATOR,((ASTNodeData*)astRoot->children[0]->data)->tokenInfo.lexeme
		                             ,((ASTNodeData*)astRoot->children[1]->data)->tokenInfo.lexeme);
				TokenInfo td;
				strcpy(td.lexeme,temp);
				strcpy(td.token,"Temporary");
			
                               	entry->tkInfo=td;
 				
				entry->scope = data->scope;
				
				*((HashTable*)(data->symbolTables.head->element)) = hashTable_add(*((HashTable*)(data->symbolTables.head->element)), entry);
				listOfSymbols = linkList_addToTail(listOfSymbols, entry);
				calculateOffsets();				
				return temp;
			}
			else
			{
				temp1=generatequadruple(astRoot->children[1]);
				temp=generatevariable();
				tempo=new_quadruple(temp,OPERATOR,
				((ASTNodeData*)astRoot->children[0]->data)->tokenInfo.lexeme,temp1);
				TokenInfo td;
				strcpy(td.lexeme,temp);
				strcpy(td.token,"Temporary");
			
                               	entry->tkInfo=td;
 				
				entry->scope = data->scope;
				
				*((HashTable*)(data->symbolTables.head->element)) = hashTable_add(*((HashTable*)(data->symbolTables.head->element)), entry);
				listOfSymbols = linkList_addToTail(listOfSymbols, entry);
				calculateOffsets();
				return temp;
			}
			 
		}
        
		else
		{ 
			char* temp2;
		       temp2=generatequadruple(astRoot->children[0]);
		        if((strcmp(((ASTNodeData*)astRoot->children[1]->data)->symbol->symbolName ,"NUM")==0)||
		       	  (strcmp(((ASTNodeData*)astRoot->children[1]->data)->symbol->symbolName,"RNUM")==0)||
		    	  (strcmp(((ASTNodeData*)astRoot->children[1]->data)->symbol->symbolName ,"ID")==0))
			{
				temp=generatevariable();
			        tempo=new_quadruple(temp,OPERATOR,temp2,
				((ASTNodeData*)astRoot->children[1]->data)->tokenInfo.lexeme);
			        return temp;
		       }
		       else
		       {
				char* tem;
			        tem=generatequadruple(astRoot->children[1]);
				temp=generatevariable();
				tempo=new_quadruple(temp,OPERATOR,temp2,tem);
		                return temp;
		       }
		}
	}
	else  if(strcmp(((ASTNodeData*)astRoot->data)->symbol->symbolName, "<parameter_list>") == 0)
	{
		int k;
		char *temp, *inp1,*inp2,*temp1;
		quadruple* tempo;

		inp1=returnstring(((ASTNodeData*)astRoot->children[1]->data)->tokenInfo.lexeme);
		if(astRoot->no_of_children==2)
		{
		inp1=returnstring(((ASTNodeData*)astRoot->children[1]->data)->tokenInfo.lexeme);
		if(strcmp(((ASTNodeData*)astRoot->children[1]->data)->symbol->symbolName ,"ID")==0)
			{	
				temp=generatevariable();
				tempo=new_quadruple(temp,FUNC_PAR,inp1,NULL);
			}
		}
		else 
		{
			inp1==returnstring(((ASTNodeData*)astRoot->children[1]->data)->tokenInfo.lexeme);
			inp2=returnstring(((ASTNodeData*)astRoot->children[3]->data)->tokenInfo.lexeme);
			if(strcmp(((ASTNodeData*)astRoot->children[1]->data)->symbol->symbolName ,"ID")==0 &&
				 strcmp(((ASTNodeData*)astRoot->children[3]->data)->symbol->symbolName ,"ID")==0)
				{	
					temp=generatevariable();
					tempo=new_quadruple(temp,FUNC_PAR,inp1,inp2);
				}
			for(k=4;k<astRoot->no_of_children;k++)
			{
				inp1=returnstring(((ASTNodeData*)astRoot->children[k]->data)->tokenInfo.lexeme);
				if(strcmp(((ASTNodeData*)astRoot->children[k]->data)->symbol->symbolName ,"ID")==0)
				{	
			
					temp1=generatevariable();
					tempo=new_quadruple(temp1,FUNC_PAR,temp,inp1);
					temp=temp1;
				}
			}
		}
		
		return temp;
	}

}


char*	returnstring(char* value)
{
return value;
}
