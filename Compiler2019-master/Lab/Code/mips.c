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

void PrintMipsCode(InterCode it, FILE *fp){
	switch(it->kind){
	case IC_ASSIGN:
		MipsCodeAssign(it,fp);
		break;
	case IC_ADD:
	case IC_SUB:
	case IC_MUL:
	case IC_DIV:
		MipsCodeAddSubMulDiv(it,fp);
		break;
	case IC_LABEL:
		MipsCodeLabel(it,fp);
		break;
	case IC_FUNCTION:
		MipsCodeFunction(it,fp);
		break;
	case IC_GOTO:
		MipsCodeGoto(it,fp);
		break;
	case IC_IFGOTO:
		MipsCodeIfgoto(it,fp);
		break;
	case IC_RETURN:
		MipsCodeReturn(it,fp);
		break;
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

int getReg(Operand op){
	/*****************************
	/* Still need implementation *
	*****************************/
	
	return 0;
}

/*****************
 **Gen mips code**
*****************/
void MipsCodeAssign(InterCode it,FILE *fp){
	Operand op_left=it->u.assign.left;
	Operand op_right=it->u.assign.right;
	int left_id, right_id;
	// Deal with assign here
	if(op_left->kind==OP_TEMP_VAR||op_left->kind==OP_VARIABLE){
		left_id=getReg(op_left);
		//x := 
		if(op_right->kind==OP_CONSTANT){
			//x := #k
			fprintf(fp,"\tli %s, %d\n",regs[left_id].name,op_right->u.value);
		}
		else if(op_right->kind==OP_TEMP_VAR||op_right->kind==OP_VARIABLE){
			//x := y
			right_id=getReg(op_right);
			fprintf(fp,"\tmove %s, %s\n",regs[left_id].name,regs[right_id].name);
		}
		else if(op_right->kind==OP_VAR_ADDR||op_right->kind==OP_TEMP_VAR_ADDR){
			//x := *y
			right_id=getReg(op_right);
			fprintf(fp,"\tlw %s, 0(%s)\n",regs[left_id].name,regs[right_id].name);
		}
		else{
			assert(0);
		}
	}
	else if(op_left->kind==OP_VAR_ADDR||op_left->kind==OP_TEMP_VAR_ADDR){
		left_id=getReg(op_left);
		if(op_right->kind==OP_CONSTANT){
			//*x = #k;
			fprintf(fp,"\tsw %s, %d\n",regs[left_id].name,op_right->u.value);
		}
		else if(op_right->kind==OP_VARIABLE||op_right->kind==OP_TEMP_VAR){
			//*x = y;
			right_id=getReg(op_right);
			fprintf(fp,"\tsw %s, 0(%s)\n",regs[left_id].name,regs[right_id].name);
		}
		else{
			assert(0);
		}
	}
	else{
		assert(0);
	}
}

void MipsCodeAddSubMulDiv(InterCode it,FILE *fp){
	Operand op_res=it->u.binOp.result;
	Operand op1=it->u.binOp.op1;
	Operand op2=it->u.binOp.op2;
	int res_id, op1_id, op2_id;
	bool op1_cons=(op1->kind==OP_CONSTANT)?true:false;
	bool op2_cons=(op2->kind==OP_CONSTANT)?true:false;
	bool op_var=((op1->kind==OP_VARIABLE||op1->kind==OP_TEMP_VAR)
		&&(op2->kind==OP_VARIABLE||op2->kind==OP_TEMP_VAR))?true:false;
	res_id=getReg(op_res);
	if(op1_cons){
		op2_id=getReg(op2);
		switch(it->kind){
		case IC_ADD:
			// x = #k + y, modified to x = y + #k
			fprintf(fp,"\taddi %s, %s, %d\n",regs[res_id].name,regs[op2_id].name,op1->u.value);
			break;
		case IC_SUB:
			// x = #k - y may have bugs here
			fprintf(fp,"\taddi %s, %s, -%d\n",regs[res_id].name,regs[op2_id].name,op1->u.value);
			fprintf(fp,"\tneg %s\n",regs[res_id].name);
			break;
		case IC_MUL:
			/*****************************
			/* Still need implementation *
			*****************************/
			// LOAD TO REGS FIRST
			break;
		case IC_DIV:
			/*****************************
			/* Still need implementation *
			*****************************/
			// LOAD TO REGS FIRST
			break;
		default:
			assert(0);
		}
	}
	else if(op2_cons){
		op1_id=getReg(op1);
		switch(it->kind){
		case IC_ADD:
			// x = y + #k
			fprintf(fp,"\taddi %s, %s, %d\n",regs[res_id].name,regs[op1_id].name,op2->u.value);
			break;
		case IC_SUB:
			// x = y - #k
			fprintf(fp,"\taddi %s, %s, -%d\n",regs[res_id].name,regs[op1_id].name,op2->u.value);
			break;
		case IC_MUL:
			/*****************************
			/* Still need implementation *
			*****************************/
			// LOAD TO REGS FIRST
			break;
		case IC_DIV:
			/*****************************
			/* Still need implementation *
			*****************************/
			// LOAD TO REGS FIRST
			break;
		default:
			assert(0);
		}
	}
	else if(op_var){
		op1_id=getReg(op1);
		op2_id=getReg(op2);
		switch(it->kind){
		case IC_ADD:
			//x = y + z
			fprintf(fp,"\tadd %s, %s, %s\n",regs[res_id].name,regs[op1_id].name,regs[op2_id].name);
			break;
		case IC_SUB:
			//x = y - z
			fprintf(fp,"\tsub %s, %s, %s\n",regs[res_id].name,regs[op1_id].name,regs[op2_id].name);
			break;
		case IC_MUL:
			//x = y * z
			fprintf(fp,"\tmul %s, %s, %s\n",regs[res_id].name,regs[op1_id].name,regs[op2_id].name);
			break;
		case IC_DIV:
			//x = y / z
			fprintf(fp, "\tdiv %s, %s\n",regs[op1_id].name,regs[op2_id].name);
			fprintf(fp, "\tmflo %s\n",regs[res_id]);
			break;
		default:
			assert(0);
		}
	}
	else{
		assert(0);
	}
}

void MipsCodeLabel(InterCode it,FILE *fp){
	fprintf(fp, "label%d:\n", it->u.sinOp.op->u.var_no);
}

void MipsCodeFunction(InterCode it,FILE *fp){
	/*****************************
	/* Still need implementation *
	*****************************/
	// sp-=4, store ret addr
	printf("to print function,\n");
	fprintf(fp, "%s:\n"
		,it->u.sinOp.op->u.name);
	printf("end print function.\n");
}

void MipsCodeGoto(InterCode it,FILE *fp){
	printf("to print goto.\n");
	fprintf(fp,"\tj label%d\n",it->u.sinOp.op->u.var_no);
	printf("end print goto.\n");
}

void MipsCodeIfgoto(InterCode it,FILE *fp){
	Operand op1=it->u.triOp.op1;
	Operand op2=it->u.triOp.op2;
	int label_num=it->u.triOp.label->u.var_no;
	char* relop=(char*)malloc(sizeof(char *));
	relop=it->u.triOp.relop;
	int op1_id;
	int op2_id;
	if(op1->kind!=OP_CONSTANT){
		op1_id=getReg(op1);
		if(op2->kind!=OP_CONSTANT){
			op2_id=getReg(op2);
			if(strcmp(relop,"==")){
				fprintf(fp,"\tbeq %s, %s, label%d\n",regs[op1_id].name,regs[op2_id].name,label_num);
			}
			else if(strcmp(relop,"!=")){
				fprintf(fp,"\tbne %s, %s, label%d\n",regs[op1_id].name,regs[op2_id].name,label_num);
			}
			else if(strcmp(relop,">")){
				fprintf(fp,"\tbgt %s, %s, label%d\n",regs[op1_id].name,regs[op2_id].name,label_num);
			}
			else if(strcmp(relop,"<")){
				fprintf(fp,"\tblt %s, %s, label%d\n",regs[op1_id].name,regs[op2_id].name,label_num);
			}
			else if(strcmp(relop,">=")){
				fprintf(fp,"\tbge %s, %s, label%d\n",regs[op1_id].name,regs[op2_id].name,label_num);
			}
			else if(strcmp(relop,"<=")){
				fprintf(fp,"\tble %s, %s, label%d\n",regs[op1_id].name,regs[op2_id].name,label_num);
			}
			else{
				assert(0);
			}
		}
		else if(op2->kind==OP_CONSTANT){
			if(strcmp(relop,"==")){
				fprintf(fp,"\tbeq %s, %d, label%d\n",regs[op1_id].name,op2->u.value,label_num);
			}
			else if(strcmp(relop,"!=")){
				fprintf(fp,"\tbne %s, %d, label%d\n",regs[op1_id].name,op2->u.value,label_num);
			}
			else if(strcmp(relop,">")){
				fprintf(fp,"\tbgt %s, %d, label%d\n",regs[op1_id].name,op2->u.value,label_num);
			}
			else if(strcmp(relop,"<")){
				fprintf(fp,"\tblt %s, %d, label%d\n",regs[op1_id].name,op2->u.value,label_num);
			}
			else if(strcmp(relop,">=")){
				fprintf(fp,"\tbge %s, %d, label%d\n",regs[op1_id].name,op2->u.value,label_num);
			}
			else if(strcmp(relop,"<=")){
				fprintf(fp,"\tble %s, %d, label%d\n",regs[op1_id].name,op2->u.value,label_num);
			}
			else{
				assert(0);
			}
		}
		else{
			assert(0);
		}
	}
	else if(op1->kind==OP_CONSTANT&&op2->kind!=OP_CONSTANT){
		op2_id=getReg(op2);
		if(strcmp(relop,"==")){
			fprintf(fp,"\tbeq %s, %d, label%d\n",regs[op2_id].name,op1->u.value,label_num);
		}
		else if(strcmp(relop,"!=")){
			fprintf(fp,"\tbne %s, %d, label%d\n",regs[op2_id].name,op1->u.value,label_num);
		}
		else if(strcmp(relop,">")){
			fprintf(fp,"\tble %s, %d, label%d\n",regs[op2_id].name,op1->u.value,label_num);
		}
		else if(strcmp(relop,"<")){
			fprintf(fp,"\tbge %s, %d, label%d\n",regs[op2_id].name,op1->u.value,label_num);
		}
		else if(strcmp(relop,">=")){
			fprintf(fp,"\tblt %s, %d, label%d\n",regs[op2_id].name,op1->u.value,label_num);
		}
		else if(strcmp(relop,"<=")){
			fprintf(fp,"\tbgt %s, %d, label%d\n",regs[op2_id].name,op1->u.value,label_num);
		}
		else{
			assert(0);
		}
	}
}

void MipsCodeReturn(InterCode it,FILE *fp){
	/*****************************
	/* Still need implementation *
	*****************************/
	Operand op=it->u.sinOp.op;
	printf("to print return.\n");
	if(op->kind==OP_CONSTANT){
		fprintf(fp,"\tmove $v0, $%d\n\tjr $ra\n",op->u.value);
	}
	printf("end print return.\n");
}

void MipsCodeDec(InterCode it,FILE *fp){
	/*****************************
	/* Still need implementation *
	*****************************/
}

void MipsCodeArg(InterCode it,FILE *fp){
	/*****************************
	/* Still need implementation *
	*****************************/
}

void MipsCodeCall(InterCode it,FILE *fp){
	/*****************************
	/* Still need implementation *
	*****************************/
}

void MipsCodeParam(InterCode it,FILE *fp){
	/*****************************
	/* Still need implementation *
	*****************************/
}

void MipsCodeRead(InterCode it,FILE *fp){
	fprintf(fp, "\tjal read\n");
}

void MipsCodeWrite(InterCode it,FILE *fp){
	fprintf(fp, "%sjal write\n");
}
