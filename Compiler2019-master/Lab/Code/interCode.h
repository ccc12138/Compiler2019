#ifndef _INTERCODE_H
#define _INTERCODE_H

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;

struct Operand_{
	enum{
		OP_VARIABLE, OP_TEMPVAR, OP_CONSTANT, 
		OP_ADDRESS, OP_LABEL, OP_FUNCTION
		// may still need sth
	}kind;
	union{
		int var_no;
		int value;
		Operand addr;
	}u;
};

/*
 * Double linked-list is easy for optimization of inter code? so
 */
struct InterCode_{
	enum{// ref P64
		IC_ASSIGN, IC_ADD, IC_SUB, IC_MUL, IC_DIV, 
		IC_LABEL, IC_FUNCTION, IC_ADDRESS, 
		IC_GOTO, IC_IFGOTO, IC_RETURN, 
		IC_DEC, IC_ARG, IC_CALL, IC_PARAM, 
		IC_READ, IC_WRITE
		// may still need sth
	}kind;
	union{
		struct { Operand right, left; }assign;
		struct { Operand op; }sin_op;
		struct { Operand result, op1, op2; }bin_op;
		struct { Operand op1, op2, label; char *op; }tri_op;
		struct { Operand op; int size; }dec;
		// may still need sth
	}u;
	InterCode prev;
	InterCode next;
};

InterCode codeHead=NULL;
InterCode codeTail=NULL;

bool InsertCode(InterCode node);
bool DeleteCode(InterCode node);
void PrintOperand(Operand op, FILE* fp);// fp should comes from main.c
void PrintCode(FILE* fp);// fp should comes from main.c


// May be we should finish intercode gen at semantic.c instead of using new func
// InterCode translate_Exp(treeNode* root);
// InterCode translate_Stmt(treeNode* root);
// InterCode translate_Func(treeNode* root);
// InterCode translate_Stmt(treeNode* root);

#endif