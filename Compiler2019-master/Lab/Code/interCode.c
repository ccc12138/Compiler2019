#include "interCode.h"

extern InterCode codeHead;
extern InterCode codeTail;
extern unsigned labelNum;

bool InsertCode(InterCode node){
	assert(node!=NULL);
	if(codeHead==NULL&&codeTail==NULL){
		codeHead=node;
		codeTail=node;
		node->next=node;
		node->prev=node;
	}
	else{
		node->prev=codeTail;
		node->next=codeHead;
		codeTail->next=node;
		codeHead->prev=node;
		codeTail=node;
	}
	return true;
}

bool InsertCode_func(char * func_name){
	InterCode newcode = malloc ( sizeof ( struct InterCode_ ) );
	newcode -> kind = IC_FUNCTION;
	newcode -> u.sinOp.op = malloc ( sizeof ( struct Operand_ ) );
	newcode -> u.sinOp.op -> kind = OP_FUNCTION;
	newcode -> u.sinOp.op -> u.name = func_name;
	return InsertCode(newcode);
}

bool InsertCode_label(Operand label){
	InterCode newcode = malloc ( sizeof ( struct InterCode_ ) );
	newcode -> kind = IC_LABEL;
	newcode -> u.sinOp.op = label;
	return InsertCode(newcode);
}


bool DeleteCode(InterCode node){
	assert(node!=NULL&&codeHead!=NULL&&codeTail!=NULL);
	if(node==codeHead){
		codeHead=node->next;
		codeHead->prev=codeTail;
		codeTail->next=codeHead;
		// printf("node=codeHead to del!\n");
		free(node);
	}
	else if(node==codeTail){
		codeTail=node->prev;
		codeTail->next=codeHead;
		codeHead->prev=codeTail;
		// printf("node=codeTail to del!\n");
		free(node);
	}
	else{
		node->prev->next=node->next;
		node->next->prev=node->prev;
		// printf("inner node to del!\n");
		free(node);
	}
	return true;
}

void PrintCode(FILE *fp){
	assert(codeHead!=NULL&&codeTail!=NULL);
	InterCode ic=codeHead;
	do{
		switch(ic->kind){
			case IC_LABEL://1
				PRINT_SINOP("LABEL ");
				fputs(": ",fp);
				break;//2
			case IC_FUNCTION:
				PRINT_SINOP("FUNCTION ");
				fputs(": ",fp);
				break;
			case IC_ASSIGN://3,8,9,10
				PRINT_ASSIGN(":= ");
				break;
			case IC_ADD://4
				PRINT_BINOP("+ ");
				break;
			case IC_SUB://5
				PRINT_BINOP("- ");
				break;
			case IC_MUL://6
				PRINT_BINOP("* ");
				break;
			case IC_DIV://7
				PRINT_BINOP("/ ");
				break;
			case IC_GOTO://11
				PRINT_SINOP("GOTO ");
				break;
			case IC_IFGOTO://12
				PRINT_TRIOP();
				break;
			case IC_RETURN://13
				PRINT_SINOP("RETURN ");
				break;
			case IC_DEC://14
				PRINT_DEC();
				break;
			case IC_ARG://15
				PRINT_SINOP("ARG ");
				break;
			case IC_CALL://16
				PRINT_ASSIGN(":= CALL ");
				break;
			case IC_PARAM://17
				PRINT_SINOP("PARAM ");
				break;
			case IC_READ://18
				PRINT_SINOP("READ ");
				break;
			case IC_WRITE://19
				PRINT_SINOP("WRITE ");
				break;
			default:// impossible to reach here
				assert(0);
		}
		fputs("\n",fp);
		ic=ic->next;
	}while(ic!=codeHead);
	return;
}

void PrintOperand(Operand op, FILE* fp){
	assert(op!=NULL&&fp!=NULL);
	char tempStr[STRLEN];
	switch(op->kind){
		case OP_VARIABLE://x
			fprintf(fp,"v%d ",op->u.var_no);
			break;
		case OP_TEMP_VAR://t
			fprintf(fp,"t%d ",op->u.var_no);
			break;
		case OP_CONSTANT://#
			fprintf(fp,"#%d ",op->u.value);
			break;
		case OP_VAR_ADDR://*
			assert(op->u.addr!=NULL);
			fprintf(fp,"*v%d ",op->u.addr->u.var_no);
			break;
		case OP_TEMP_VAR_ADDR://*t
			assert(op->u.addr!=NULL);
			fprintf(fp,"*t%d ",op->u.addr->u.var_no);
			break;
		case OP_LABEL://label x
			fprintf(fp,"label%d ",op->u.var_no);
			break;
		case OP_FUNCTION://x
			fprintf(fp,"%s ",op->u.name);
			break;
		case OP_GET_ADDR:
			fprintf(fp,"&v%d ",op->u.var_no);
			break;
		default://impossible to reach here
			assert(0);
	}
	return;
}

void PrintfCode(){
	assert(codeHead!=NULL&&codeTail!=NULL);
	InterCode ic=codeHead;
	do{
		switch(ic->kind){
			case IC_LABEL://1
				PRINTF_SINOP("LABEL ");
				printf(": ");
				break;//2
			case IC_FUNCTION:
				PRINTF_SINOP("FUNCTION ");
				printf(": ");
				break;
			case IC_ASSIGN://3,8,9,10
				PRINTF_ASSIGN(":= ");
				break;
			case IC_ADD://4
				PRINTF_BINOP("+ ");
				break;
			case IC_SUB://5
				PRINTF_BINOP("- ");
				break;
			case IC_MUL://6
				PRINTF_BINOP("* ");
				break;
			case IC_DIV://7
				PRINTF_BINOP("/ ");
				break;
			case IC_GOTO://11
				PRINTF_SINOP("GOTO ");
				break;
			case IC_IFGOTO://12
				PRINTF_TRIOP();
				break;
			case IC_RETURN://13
				PRINTF_SINOP("RETURN ");
				break;
			case IC_DEC://14
				PRINTF_DEC();
				break;
			case IC_ARG://15
				PRINTF_SINOP("ARG ");
				break;
			case IC_CALL://16
				PRINTF_ASSIGN(":= CALL ");
				break;
			case IC_PARAM://17
				PRINTF_SINOP("PARAM ");
				break;
			case IC_READ://18
				PRINTF_SINOP("READ ");
				break;
			case IC_WRITE://19
				PRINTF_SINOP("WRITE ");
				break;
			default:// impossible to reach here
				assert(0);
		}
		printf("\n");
		ic=ic->next;
	}while(ic!=codeHead);
	return;
}

void PrintfOperand(Operand op){
	assert(op!=NULL);
	char tempStr[STRLEN];
	switch(op->kind){
		case OP_VARIABLE://x
			printf("v%d ",op->u.var_no);
			break;
		case OP_TEMP_VAR://t
			printf("t%d ",op->u.var_no);
			break;
		case OP_CONSTANT://#
			printf("#%d ",op->u.value);
			break;
		case OP_VAR_ADDR://*
			assert(op->u.addr!=NULL);
			printf("*v%d ",op->u.addr->u.var_no);
			break;
		case OP_TEMP_VAR_ADDR://*t
			assert(op->u.addr!=NULL);
			printf("*t%d ",op->u.addr->u.var_no);
			break;
		case OP_LABEL://label x
			printf("label%d ",op->u.var_no);
			break;
		case OP_FUNCTION://x
			printf("%s ",op->u.name);
			break;
		case OP_GET_ADDR:
			printf("&v%d ",op->u.var_no);
			break;
		default://impossible to reach here
			assert(0);
	}
	return;
}


void OptimizeCode(){
	// TO IMPLEMENT
	OptimizeGoto();
	OptimizeLabel();
	return;
}

bool OptimizeGoto(){
	InterCode c=codeHead;
	do{
		if(c->kind==IC_IFGOTO){
			InterCode c1=c;
			InterCode c2=c->next;
			if(c2==NULL){
#ifdef DEBUG
				printf("Something Wrong?\n");
				return false;
#endif
				continue;
			}
			InterCode c3=c2->next;
			if(c3==NULL){
#ifdef DEBUG
				printf("Something Wrong?\n");
				return false;
#endif
				continue;
			}
			if(c2->kind==IC_GOTO&&c3->kind==IC_LABEL&&c2->u.sinOp.op==c3->u.sinOp.op){
				DeleteCode(c2);
			}
			else if(c2->kind==IC_GOTO&&c3->kind==IC_LABEL&&c1->u.triOp.label==c3->u.sinOp.op){
				c1->u.triOp.label=c2->u.sinOp.op;
				if(strcmp(c1->u.triOp.relop,"==")==0){
					UPDATE_RELOP("!=")
					// printf("succ find one == !\n");
				}
				else if(strcmp(c1->u.triOp.relop,"!=")==0){
					UPDATE_RELOP("==")
					// printf("succ find one != !\n");
				}
				else if(strcmp(c1->u.triOp.relop,">")==0){
					UPDATE_RELOP("<=")
					// printf("succ find one > !\n");
				}
				else if(strcmp(c1->u.triOp.relop,">=")==0){
					UPDATE_RELOP("<")
					// printf("succ find one >= !\n");
				}
				else if(strcmp(c1->u.triOp.relop,"<")==0){
					UPDATE_RELOP(">=")
					// printf("succ find one < !\n");
				}
				else if(strcmp(c1->u.triOp.relop,"<=")==0){
					UPDATE_RELOP(">");
					// printf("succ find one <= !\n");
				}
				// printf("\nEnter deletecode!\n");
				DeleteCode(c2);
			}
		}
		else if(c->kind==IC_GOTO)
		{
			InterCode c1=c;
			InterCode c2=c->next;
			if(c2==NULL){
#ifdef DEBUG
				printf("Something Wrong?\n");
				return false;
#endif
				continue;
			}
			if(c2->kind==IC_LABEL&&c1->u.sinOp.op==c2->u.sinOp.op){
				DeleteCode(c1);
			}
		}
		c=c->next;
	}while(c!=codeHead);
	return true;
}

bool OptimizeLabel(){
	// use bitmap to eliminate extra labels
	unsigned mapSize=sizeof(bool)*labelNum;
	bool *gotoMap=(bool*)malloc(mapSize);
	bool *labelMap=(bool*)malloc(mapSize);
	memset(gotoMap,false,mapSize);
	memset(labelMap,false,mapSize);
	InterCode ic=codeHead;
	do{
		if(ic->kind==IC_IFGOTO){
			gotoMap[ic->u.triOp.label->u.var_no]=true;
		}
		else if(ic->kind==IC_GOTO){
			gotoMap[ic->u.sinOp.op->u.var_no]=true;
		}
		else if(ic->kind==IC_LABEL){
			labelMap[ic->u.sinOp.op->u.var_no]=true;
		}
		ic=ic->next;
	}while(ic!=codeHead);
	ic=codeHead;
	do{
		if(ic->kind==IC_LABEL){
			unsigned index=ic->u.sinOp.op->u.var_no;
			if(labelMap[index]==true&&gotoMap[index]==false){
				InterCode tempic=ic;
				ic=ic->next;
				DeleteCode(tempic);
				continue;
			}
		}
		ic=ic->next;
	}while(ic!=codeHead);
	free(gotoMap);
	free(labelMap);
	return true;
}