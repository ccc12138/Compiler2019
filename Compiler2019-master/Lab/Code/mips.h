#ifndef _MIPS_H
#define _MIPS_H

#include "translate.h"

#define _REG_NUM_ 32
#define _STR_LEN_ 256
#define _SAVED_VAR_ 16

extern InterCode codeHead;
extern InterCode codeTail;
extern char* regsNameArr[];

// #define GET_VAR_REG(op)\



typedef struct VarDesc_* VarDesc;
typedef struct RegDesc_* RegDesc;
typedef struct BasicBlock_* BasicBlock;
typedef struct ArgList_* ArgList;

struct VarDesc_{//Var Descripter
	int reg;//register match
	int offset;//for param
};

struct RegDesc_ {//Register Descripter
	char *name;//Register name
	VarDesc var;//Describe register
};

// Double linked list
struct BasicBlock_{
	InterCode first_ic;
	InterCode last_ic;
};

struct ArgList_{
	int reg_id;
	ArgList next;
};

void PrintMips(FILE *fp);
void PrintMipsCode(InterCode ic,FILE *fp);

// Basic Blocks
void InitFirstCode();
void InitBasicBlocks();
void InitActiveVar();

// Register
void InitRegs();
void InitVars();
int getReg(Operand op, FILE *fp);
int findVar(Operand op);//just find where it is

// Generate Mips Code
void MipsCodeAssign(InterCode ic,FILE *fp);
void MipsCodeAddSubMulDiv(InterCode ic,FILE *fp);
// void MipsCodeSub(InterCode ic,FILE *fp);
// void MipsCodeMul(InterCode ic,FILE *fp);
// void MipsCodeDiv(InterCode ic,FILE *fp);
void MipsCodeLabel(InterCode ic,FILE *fp);
void MipsCodeFunction(InterCode ic,FILE *fp);
void MipsCodeGoto(InterCode ic,FILE *fp);
void MipsCodeIfgoto(InterCode ic,FILE *fp);
void MipsCodeReturn(InterCode ic,FILE *fp);
void MipsCodeDec(InterCode ic,FILE *fp);
void MipsCodeArg(InterCode ic,FILE *fp);
void MipsCodeCall(InterCode ic,FILE *fp);
void MipsCodeParam(InterCode ic,FILE *fp);
void MipsCodeRead(InterCode ic,FILE *fp);
void MipsCodeWrite(InterCode ic,FILE *fp);

#endif