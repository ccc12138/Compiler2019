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
void PrintMipsCode(InterCode it);

// Register
void InitRegs();

// Generate Mips Code
void MipsCodeAssign(InterCode it);
void MipsCodeAdd(InterCode it);
void MipsCodeSub(InterCode it);
void MipsCodeMul(InterCode it);
void MipsCodeDiv(InterCode it);
void MipsCodeLabel(InterCode it);
void MipsCodeFunction(InterCode it);
void MipsCodeGoto(InterCode it);
void MipsCodeIfgoto(InterCode it);
void MipsCodeReturn(InterCode it);
void MipsCodeDec(InterCode it);
void MipsCodeArg(InterCode it);
void MipsCodeCall(InterCode it);
void MipsCodeParam(InterCode it);
void MipsCodeRead(InterCode it);
void MipsCodeWrite(InterCode it);

#endif