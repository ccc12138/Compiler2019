#ifndef _INTERCODE_H
#define _INTERCODE_H

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STRLEN 50

// define some useful macros
#define PRINT_ASSIGN(assign_str)\
	PrintOperand(ic->u.assign.left,fp);\
	fputs(assign_str,fp);\
	PrintOperand(ic->u.assign.right,fp);


#define PRINT_BINOP(op_str)\
	PrintOperand(ic->u.binOp.result,fp);\
	fputs(":= ",fp);\
	PrintOperand(ic->u.binOp.op1,fp);\
	fputs(op_str,fp);\
	PrintOperand(ic->u.binOp.op2,fp);

#define PRINT_SINOP(kind_str)\
	fputs(kind_str,fp);\
	PrintOperand(ic->u.sinOp.op,fp);

#define PRINT_TRIOP()\
	fputs("IF ",fp);\
	PrintOperand(ic->u.triOp.op1,fp);\
	fputs(ic->u.triOp.relop,fp);\
	fputs(" ",fp);\
	PrintOperand(ic->u.triOp.op2,fp);\
	fputs("GOTO ",fp);\
	PrintOperand(ic->u.triOp.label,fp);

#define PRINT_DEC()\
	fputs("DEC ",fp);\
	PrintOperand(ic->u.dec.op,fp);\
	fprintf(fp,"%d",ic->u.dec.size);


#define PRINTF_ASSIGN(assign_str)\
	PrintfOperand(ic->u.assign.left);\
	printf("%s",assign_str);\
	PrintfOperand(ic->u.assign.right);


#define PRINTF_BINOP(op_str)\
	PrintfOperand(ic->u.binOp.result);\
	printf(":= ");\
	PrintfOperand(ic->u.binOp.op1);\
	printf("%s",op_str);\
	PrintfOperand(ic->u.binOp.op2);

#define PRINTF_SINOP(kind_str)\
	printf("%s",kind_str);\
	PrintfOperand(ic->u.sinOp.op);

#define PRINTF_TRIOP()\
	printf("IF ");\
	PrintfOperand(ic->u.triOp.op1);\
	printf("%s",ic->u.triOp.relop);\
	printf(" ");\
	PrintfOperand(ic->u.triOp.op2);\
	printf("GOTO ");\
	PrintfOperand(ic->u.triOp.label);

#define PRINTF_DEC()\
	printf("DEC ");\
	PrintfOperand(ic->u.dec.op);\
	printf("%d",ic->u.dec.size);

#define UPDATE_RELOP(str)\
	char* newRelop = (char *)malloc(sizeof(char *));\
	memset(newRelop,0,sizeof(char*));\
	strcpy(newRelop,str);\
	c1->u.triOp.relop=newRelop;

typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;

struct Operand_{
	enum{
		OP_VARIABLE, OP_TEMP_VAR, OP_CONSTANT, 
		OP_VAR_ADDR, OP_TEMP_VAR_ADDR,
		OP_LABEL, OP_FUNCTION, OP_GET_ADDR
		// may still need sth
	}kind;
	union{
		unsigned var_no;
		int value;
		char* name;
		Operand addr;
	}u;
};

/*
 * Double linked-list is easy for optimization of inter code? so
 */
struct InterCode_{
	enum{// ref P64
		IC_ASSIGN, IC_ADD, IC_SUB, IC_MUL, IC_DIV, 
		IC_LABEL, IC_FUNCTION,
		IC_GOTO, IC_IFGOTO, IC_RETURN, 
		IC_DEC, IC_ARG, IC_CALL, IC_PARAM, 
		IC_READ, IC_WRITE
		// may still need sth
	}kind;
	union{
		struct { Operand right, left; }assign;
		struct { Operand op; }sinOp;
		struct { Operand result, op1, op2; }binOp;
		struct { Operand op1, op2, label; char *relop; }triOp;
		struct { Operand op; int size; }dec;
		// may still need sth
	}u;
	InterCode prev;
	InterCode next;
	// 64 bits
	unsigned long long def_vbitv;
	unsigned long long def_tbitv;
	unsigned long long use_vbitv;
	unsigned long long use_tbitv;
	bool first_code;
};

bool InsertCode(InterCode node);
bool InsertCode_func(char * func_name);
bool InsertCode_label(Operand label);
bool DeleteCode(InterCode node);
void PrintfOCode(InterCode ic);
void PrintCode(FILE* fp);// fp should comes from main.c
void PrintOperand(Operand op, FILE* fp);// fp should comes from PrintCode
void PrintfCode();
void PrintfOperand(Operand op);
void OptimizeCode();
bool OptimizeGoto();
bool OptimizeLabel();

// May be we should finish intercode gen at semantic.c instead of using new func
// InterCode translate_Exp(treeNode* root);
// InterCode translate_Stmt(treeNode* root);
// InterCode translate_Func(treeNode* root);
// InterCode translate_Stmt(treeNode* root);

#endif
