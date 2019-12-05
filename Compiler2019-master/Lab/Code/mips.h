#ifndef _MIPS_H
#define _MIPS_H

#include "translate.h"

#define _REG_NUM_ 32
#define _STR_LEN_ 256

extern InterCode codeHead;
extern InterCode codeTail;
extern char* regsNameArr[];

typedef struct VarDesc_* VarDesc;
typedef struct RegDesc_* RegDesc;

struct VarDesc_{//Var Descripter
	char *name;//Var name
	int reg;//register match
	int offset;//for param
	VarDesc next;//next var descripter
};

struct RegDesc_ {//Register Descripter
	char *name;//Register name
	VarDesc var;//Describe register
};

void PrintMips(FILE *fp);
void PrintMipsCode(InterCode it,FILE *fp);

// Register
void InitRegs();

// Generate Mips Code
void MipsCodeAssign(InterCode it,FILE *fp);
void MipsCodeAdd(InterCode it,FILE *fp);
void MipsCodeSub(InterCode it,FILE *fp);
void MipsCodeMul(InterCode it,FILE *fp);
void MipsCodeDiv(InterCode it,FILE *fp);
void MipsCodeLabel(InterCode it,FILE *fp);
void MipsCodeFunction(InterCode it,FILE *fp);
void MipsCodeGoto(InterCode it,FILE *fp);
void MipsCodeIfgoto(InterCode it,FILE *fp);
void MipsCodeReturn(InterCode it,FILE *fp);
void MipsCodeDec(InterCode it,FILE *fp);
void MipsCodeArg(InterCode it,FILE *fp);
void MipsCodeCall(InterCode it,FILE *fp);
void MipsCodeParam(InterCode it,FILE *fp);
void MipsCodeRead(InterCode it,FILE *fp);
void MipsCodeWrite(InterCode it,FILE *fp);

#endif