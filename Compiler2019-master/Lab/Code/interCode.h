#ifndef _INTERCODE_H
#define _INTERCODE_H

typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;

struct Operand_{
	enum{
		VARIABLE, TEMPVAR, CONSTANT, 
		ADDRESS, LABEL, FUNCTION
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

struct InterCode{
	enum{// ref P64
		ASSIGN, ADD, SUB, MUL, DIV, 
		LABEL, FUNCTION, ADDRESS, 
		GOTO, IF_GOTO, RETURN, 
		DEC, ARG, CALL, PARAM, 
		READ, WRITE
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

// May be we should finish intercode gen at semantic.c instead of using new func
// InterCode translate_Exp(treeNode* root);
// InterCode translate_Stmt(treeNode* root);
// InterCode translate_Func(treeNode* root);
// InterCode translate_Stmt(treeNode* root);

#endif