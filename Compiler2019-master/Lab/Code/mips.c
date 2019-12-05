#include "mips.h"

VarDesc varList = NULL;
RegDesc regs;
char* regNameArr[] = {
	"$zero",//Constant value 0
	"$at",//Reserved for assembler

	// Can use
	// BEGIN:
	"$v0","$v1",//Values for results and expression evaluation, use carefully
	"$a0","$a1","$a2","$a3",//Arguments for function, use carefully, inside function is equal to t0-t9 and s0-s7
	"$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7",//Temp var, sui bian use
	"$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7",//Saved, sui bian use
	"$t8","$t9",//Temp var, sui bian use
	// END

	"$k0","$k1",//Reserved for OS Kernel
	"$gp",//Global pointer

	// Can use
	// BEGIN:
	"$sp",//Stack pointer
	"$fp",//Frame pointer
	"$ra"//Return address, used by function call
	// END
};

void PrintMips(FILE *fp){
#ifdef DEBUG
	printf("Print Mips.\n");
#endif
	InitRegs();
#ifdef DEBUG
	printf("Init Regs succ!\n");
#endif
	fputs(".data\n", fp);
	fputs("_prompt: .asciiz \"Enter an integer:\"\n", fp);
	fputs("_ret: .asciiz \"\\n\"\n", fp);
	fputs(".globl main\n", fp);
	fputs(".text\n",fp);
	// FUNCTION read
	fputs("\nread:\n", fp);
	fputs("\tli $v0, 4\n", fp);
	fputs("\tla $a0, _prompt\n",fp);
	fputs("\tsyscall\n", fp);
	fputs("\tli $v0, 5\n", fp);
	fputs("\tsyscall\n", fp);
	fputs("\tjr $ra\n", fp);
	// FUNCTION write
	fputs("\nwrite:\n",fp);
	fputs("\tli $v0, 1\n", fp);
	fputs("\tsyscall\n", fp);
	fputs("\tli $v0, 4\n", fp);
	fputs("\tla $a0, _ret\n", fp);
	fputs("\tsyscall\n", fp);
	fputs("\tmove $v0, $0\n", fp);
	fputs("\tjr $ra\n\n", fp);

	// printf("reach here\n");
	InterCode it = codeHead;
	do{
		PrintMipsCode(it);
		it = it->next;
	}while(it!=codeHead);

	// free malloc spaces
	free(regs);
}

void PrintMipsCode(InterCode it){
	switch(it->kind){
	case IC_ASSIGN:
		MipsCodeAssign(it);
		break;
	case IC_ADD:
		MipsCodeAdd(it);
		break;
	case IC_SUB:
		MipsCodeSub(it);
		break;
	case IC_MUL:
		MipsCodeMul(it);
		break;
	case IC_DIV:
		MipsCodeDiv(it);
		break;
	case IC_LABEL:
		MipsCodeLabel(it);
		break;
	case IC_FUNCTION:
		MipsCodeFunction(it);
		break;
	case IC_GOTO:
		MipsCodeGoto(it);
		break;
	case IC_IFGOTO:
		MipsCodeIfgoto(it);
		break;
	case IC_RETURN:
		MipsCodeReturn(it);
		break;
	case IC_DEC:
		MipsCodeDec(it);
		break;
	case IC_ARG:
		MipsCodeArg(it);
		break;
	case IC_CALL:
		MipsCodeCall(it);
		break;
	case IC_PARAM:
		MipsCodeParam(it);
		break;
	case IC_READ:
		MipsCodeRead(it);
		break;
	case IC_WRITE:
		MipsCodeWrite(it);
		break;
	default:
		assert(0);
	}
	return;
}

// Register
void InitRegs(){
	regs=(RegDesc)malloc(sizeof(struct RegDesc_)*_REG_NUM_);
#ifdef DEBUG
	printf("Init Regs.\n");
#endif
	for(int i=0; i<_REG_NUM_; ++i){
		// printf("regNameArr=%s\n",regNameArr[i]);
		regs[i].name = regNameArr[i];
		// printf("reg name assign succ!\n");
		regs[i].var = NULL;
	}
}

/*****************
 **Gen mips code**
*****************/
void MipsCodeAssign(InterCode it){

}

void MipsCodeAdd(InterCode it){

}

void MipsCodeSub(InterCode it){

}

void MipsCodeMul(InterCode it){

}

void MipsCodeDiv(InterCode it){

}

void MipsCodeLabel(InterCode it){

}

void MipsCodeFunction(InterCode it){
	// char str[_STR_LEN_];
	// memset(str, 0, sizeof(str));
	// // sp-=4, store ret addr, update fp, sp-=enough space
	// fprintf(fp, "%s:\n
	// 	\tsubu $sp, $sp, 4\n
	// 	\tsw $fp, 0($sp)\n
	// 	\tmove $fp, $sp\n
	// 	\tsubu $sp, $sp, %d\n"
	// 	,it->u.sinOp.op->u.name,_STACK_SIZE_);
}

void MipsCodeGoto(InterCode it){

}

void MipsCodeIfgoto(InterCode it){

}

void MipsCodeReturn(InterCode it){

}

void MipsCodeDec(InterCode it){

}

void MipsCodeArg(InterCode it){

}

void MipsCodeCall(InterCode it){

}

void MipsCodeParam(InterCode it){

}

void MipsCodeRead(InterCode it){

}

void MipsCodeWrite(InterCode it){

}
