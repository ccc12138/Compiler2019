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
		PrintMipsCode(it,fp);
		it = it->next;
	}while(it!=codeHead);

	// free malloc spaces
	free(regs);
}

#define NOT_MENTIONED

void PrintMipsCode(InterCode it, FILE *fp){
	switch(it->kind){
#ifdef NOT_MENTIONED
	case IC_ASSIGN:
		MipsCodeAssign(it,fp);
		break;
	case IC_ADD:
		MipsCodeAdd(it,fp);
		break;
	case IC_SUB:
		MipsCodeSub(it,fp);
		break;
	case IC_MUL:
		MipsCodeMul(it,fp);
		break;
	case IC_DIV:
		MipsCodeDiv(it,fp);
		break;
	case IC_LABEL:
		MipsCodeLabel(it,fp);
		break;
#endif
	case IC_FUNCTION:
		MipsCodeFunction(it,fp);
		break;

#ifdef NOT_MENTIONED
	case IC_GOTO:
		MipsCodeGoto(it,fp);
		break;

	case IC_IFGOTO:
		MipsCodeIfgoto(it,fp);
		break;
// #endif
	case IC_RETURN:
		MipsCodeReturn(it,fp);
		break;
// #ifdef NOT_MENTIONED
	case IC_DEC:
		MipsCodeDec(it,fp);
		break;
	case IC_ARG:
		MipsCodeArg(it,fp);
		break;
	case IC_CALL:
		MipsCodeCall(it,fp);
		break;
	case IC_PARAM:
		MipsCodeParam(it,fp);
		break;
	case IC_READ:
		MipsCodeRead(it,fp);
		break;
	case IC_WRITE:
		MipsCodeWrite(it,fp);
		break;
#endif
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
void MipsCodeAssign(InterCode it,FILE *fp){

}

void MipsCodeAdd(InterCode it,FILE *fp){

}

void MipsCodeSub(InterCode it,FILE *fp){

}

void MipsCodeMul(InterCode it,FILE *fp){

}

void MipsCodeDiv(InterCode it,FILE *fp){

}

void MipsCodeLabel(InterCode it,FILE *fp){

}

void MipsCodeFunction(InterCode it,FILE *fp){
	// sp-=4, store ret addr
	printf("to print function,\n");
	fprintf(fp, "%s:\n\taddi $sp, $sp, -4\n\tsw $ra, 0($sp)\n"
		,it->u.sinOp.op->u.name);
	printf("end print function.\n");
}

void MipsCodeGoto(InterCode it,FILE *fp){
	// printf("to print goto.\n");
	// fprintf(fp,"\tj %s\n",it->u.sinOp.op->u.name);
	// printf("end print goto.\n");
}

void MipsCodeIfgoto(InterCode it,FILE *fp){

}

void MipsCodeReturn(InterCode it,FILE *fp){
	Operand op=it->u.sinOp.op;
	printf("to print return.\n");
	if(op->kind==OP_CONSTANT){
		fprintf(fp,"\tmove $v0, $%d\n\tjr $ra\n",op->u.value);
	}
	printf("end print return.\n");
}

void MipsCodeDec(InterCode it,FILE *fp){

}

void MipsCodeArg(InterCode it,FILE *fp){

}

void MipsCodeCall(InterCode it,FILE *fp){

}

void MipsCodeParam(InterCode it,FILE *fp){

}

void MipsCodeRead(InterCode it,FILE *fp){

}

void MipsCodeWrite(InterCode it,FILE *fp){

}
