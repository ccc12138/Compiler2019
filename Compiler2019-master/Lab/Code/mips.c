#include "mips.h"

VarDesc varList = NULL;
RegDesc regs;
int bb_num=0;
BasicBlock bb;
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
	InitFirstCode();
	InitBasicBlocks();
	InitActiveVar();
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
	InterCode ic = codeHead;
	do{
		PrintMipsCode(ic,fp);
		ic = ic->next;
	}while(ic!=codeHead);

	// free malloc spaces
	free(regs);
	free(bb);
}

void PrintMipsCode(InterCode ic, FILE *fp){
	switch(ic->kind){
	case IC_ASSIGN:
		MipsCodeAssign(ic,fp);
		break;
	case IC_ADD:
	case IC_SUB:
	case IC_MUL:
	case IC_DIV:
		MipsCodeAddSubMulDiv(ic,fp);
		break;
	case IC_LABEL:
		MipsCodeLabel(ic,fp);
		break;
	case IC_FUNCTION:
		MipsCodeFunction(ic,fp);
		break;
	case IC_GOTO:
		MipsCodeGoto(ic,fp);
		break;
	case IC_IFGOTO:
		MipsCodeIfgoto(ic,fp);
		break;
	case IC_RETURN:
		MipsCodeReturn(ic,fp);
		break;
	case IC_DEC:
		MipsCodeDec(ic,fp);
		break;
	case IC_ARG:
		MipsCodeArg(ic,fp);
		break;
	case IC_CALL:
		MipsCodeCall(ic,fp);
		break;
	case IC_PARAM:
		MipsCodeParam(ic,fp);
		break;
	case IC_READ:
		MipsCodeRead(ic,fp);
		break;
	case IC_WRITE:
		MipsCodeWrite(ic,fp);
		break;
	default:
		assert(0);
	}
	return;
}

// Basic Blocks
void InitFirstCode(){
#ifdef DEBUG
	printf("Init First Code.\n");
#endif
	InterCode ic=codeHead;
	ic->first_code=true;
	++bb_num;
	// printf("bb_num+1,1\n");
	ic=ic->next;
	while(ic!=codeHead){
		if(ic->first_code==false&&(ic->kind==IC_LABEL||ic->kind==IC_FUNCTION)){
			ic->first_code=true;
			// printf("bb_num+1,2\n");
			++bb_num;
		}
		else if(ic->next->first_code==false&&(ic->kind==IC_IFGOTO||ic->kind==IC_GOTO)){
			ic->next->first_code=true;
			// printf("bb_num+1,3\n");
			++bb_num;
		}
		ic = ic->next;
	};
}

void InitBasicBlocks(){
#ifdef DEBUG
	printf("Init Basic Blocks.\n");
	// printf("bb_num=%d\n",bb_num);
#endif
	InterCode ic=codeHead;
	bb=(BasicBlock)malloc(sizeof(struct BasicBlock_)*bb_num);
	int index=0;
	do{
		if(ic->first_code==true){
// #ifdef DEBUG
// 			printf("current index=%d.\nlast index=%d.\n",index,(index+bb_num-1)%bb_num);
// 			printf("reach here?\n");
// #endif			
			bb[index].first_ic=ic;
			bb[(int)((index+bb_num-1)%bb_num)].last_ic=ic->prev;
			++index;
// #ifdef DEBUG
// 			printf("reach here?\n");
// #endif	
		}
		ic=ic->next;
	}while(ic!=codeHead);
	// printf("index=%d\n",index);
	assert(index==bb_num);
	return;
}

void InitActiveVar(){
#ifdef DEBUG
	printf("Init Active Var.\n");
#endif
	for(int i=0;i<bb_num;++i){
		InterCode cur_ic=bb[i].last_ic;
		InterCode fir_ic=bb[i].first_ic->prev;
		int active_var=0;
		//get num of active variables and temp variables
		while(cur_ic!=fir_ic){

			cur_ic=cur_ic->prev;
		}
#ifdef DEBUG
		printf("Block %d: succ getting num.\n",i);
#endif
		// generate bit vector to get ready for the active var analysis

		// do active var analysis
		cur_ic=bb[i].last_ic;
		while(cur_ic!=fir_ic){

			cur_ic=cur_ic->prev;
		}
#ifdef DEBUG
		printf("Block %d: succ do active var analysis\n",i);
#endif
	}
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
void MipsCodeAssign(InterCode ic,FILE *fp){
	Operand op_left=ic->u.assign.left;
	Operand op_right=ic->u.assign.right;
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

void MipsCodeAddSubMulDiv(InterCode ic,FILE *fp){
	Operand op_res=ic->u.binOp.result;
	Operand op1=ic->u.binOp.op1;
	Operand op2=ic->u.binOp.op2;
	int res_id, op1_id, op2_id;
	bool op1_cons=(op1->kind==OP_CONSTANT)?true:false;
	bool op2_cons=(op2->kind==OP_CONSTANT)?true:false;
	bool op_var=((op1->kind==OP_VARIABLE||op1->kind==OP_TEMP_VAR)
		&&(op2->kind==OP_VARIABLE||op2->kind==OP_TEMP_VAR))?true:false;
	res_id=getReg(op_res);
	if(op1_cons){
		op2_id=getReg(op2);
		switch(ic->kind){
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
		switch(ic->kind){
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
		switch(ic->kind){
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

void MipsCodeLabel(InterCode ic,FILE *fp){
	fprintf(fp, "label%d:\n", ic->u.sinOp.op->u.var_no);
}

void MipsCodeFunction(InterCode ic,FILE *fp){
	/*****************************
	/* Still need implementation *
	*****************************/
	// sp-=4, store ret addr
	printf("to print function,\n");
	fprintf(fp, "%s:\n"
		,ic->u.sinOp.op->u.name);
	printf("end print function.\n");
}

void MipsCodeGoto(InterCode ic,FILE *fp){
	printf("to print goto.\n");
	fprintf(fp,"\tj label%d\n",ic->u.sinOp.op->u.var_no);
	printf("end print goto.\n");
}

void MipsCodeIfgoto(InterCode ic,FILE *fp){
	Operand op1=ic->u.triOp.op1;
	Operand op2=ic->u.triOp.op2;
	int label_num=ic->u.triOp.label->u.var_no;
	char* relop=(char*)malloc(sizeof(char *));
	relop=ic->u.triOp.relop;
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

void MipsCodeReturn(InterCode ic,FILE *fp){
	/*****************************
	/* Still need implementation *
	*****************************/
	Operand op=ic->u.sinOp.op;
	printf("to print return.\n");
	if(op->kind==OP_CONSTANT){
		fprintf(fp,"\tmove $v0, $%d\n\tjr $ra\n",op->u.value);
	}
	printf("end print return.\n");
}

void MipsCodeDec(InterCode ic,FILE *fp){
	/*****************************
	/* Still need implementation *
	*****************************/
}

void MipsCodeArg(InterCode ic,FILE *fp){
	/*****************************
	/* Still need implementation *
	*****************************/
}

void MipsCodeCall(InterCode ic,FILE *fp){
	/*****************************
	/* Still need implementation *
	*****************************/
}

void MipsCodeParam(InterCode ic,FILE *fp){
	/*****************************
	/* Still need implementation *
	*****************************/
}

void MipsCodeRead(InterCode ic,FILE *fp){
	fprintf(fp, "\tjal read\n");
}

void MipsCodeWrite(InterCode ic,FILE *fp){
	fprintf(fp, "%sjal write\n");
}
