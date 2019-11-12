#include "interCode.h"

InterCode codeHead=NULL;
InterCode codeTail=NULL;

bool InsertCode(InterCode node){
	assert(node!=NULL);
	if(codeHead==NULL&&codeTail==NULL){
		codeHead=node;
		codeTail=node;
		node->next=NULL;
		node->prev=NULL;
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

bool DeleteCode(InterCode node){
	assert(node!=NULL&&codeHead!=NULL&&codeTail!=NULL);
	if(node==codeHead){
		codeHead=node->next;
		codeHead->prev=codeTail;
		codeTail->next=codeHead;
		free(node);
	}
	else if(node==codeTail){
		codeTail=node->prev;
		codeTail->next=codeHead;
		codeHead->prev=codeTail;
		free(node);
	}
	else{
		node->prev->next=node->next;
		node->next->prev=node->prev;
		free(node);
	}
	return true;
}

void PrintOperand(Operand op, FILE* fp){
	assert(op!=NULL&&fp!=NULL);
	// char 
	return;
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
			case IC_ASSIGN://3,9,10
				PRINT_ASSIGN(":= ");
				break;
			case IC_ADD://4
				PRINT_BINOP("+ ");// don't forget space!
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
			case IC_ADDRESS://8
				PRINT_ASSIGN(":= &");
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
		ic=ic->next;
	}while(ic!=codeHead);

}