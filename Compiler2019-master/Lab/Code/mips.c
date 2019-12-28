#include "mips.h"

RegDesc regs;
int param_num=0;
int bb_num=0;
BasicBlock bb;
VarDesc var;
VarDesc temp_var;
int cur_reg_var=0;//var index
int cur_reg_temp_var=0;//temp var index
int offset=0;
int cur_arg=0;
int cur_param=0;
ArgList arg_head=NULL;
ArgList arg_tail=NULL;
char* regNameArr[] = {
	"$zero",//Constant value 0
	"$at",//Reserved for assembler

	// Can use
	// BEGIN:
	"$v0","$v1",//Values for results and expression evaluation, use carefully
	"$a0","$a1","$a2","$a3",//Arguments for function, use carefully, inside function is equal to t0-t9 and s0-s7
	"$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$t8","$t9",//Temp var, sui bian use
	"$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7",//Saved, sui bian use
	// END
	///////////////////////////////////////////////////////////////////////
	// NOTE: I CHANGE THE ORDER HERE FOR SIMPLIFICATION, BUT MEI GUAN XI //
	///////////////////////////////////////////////////////////////////////

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
	// printf("Print Mips.\n");
#endif
	InitRegs();
	InitVars();
	InitFirstCode();
	InitBasicBlocks();
	InitActiveVar();
#ifdef DEBUG
	// printf("Init Regs succ!\n");
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

	InterCode ic = codeHead;
	do{
		PrintMipsCode(ic,fp);
		ic = ic->next;
	}while(ic!=codeHead);
	// printf("finish!!!\n");
	// free malloc spaces
	// free(regs);
	// free(bb);
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
	// printf("Init First Code.\n");
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
	// printf("Init Basic Blocks.\n");
	// printf("bb_num=%d\n",bb_num);
#endif
	InterCode ic=codeHead;
	bb=(BasicBlock)malloc(sizeof(struct BasicBlock_)*bb_num);
	int index=0;
	do{
		if(ic->first_code==true){		
			bb[index].first_ic=ic;
			bb[(int)((index+bb_num-1)%bb_num)].last_ic=ic->prev;
			++index;
		}
		ic=ic->next;
	}while(ic!=codeHead);
	// printf("index=%d\n",index);
	assert(index==bb_num);
	return;
}

void InitActiveVar(){
#ifdef DEBUG
	// printf("Init Active Var.\n");
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
		// printf("Block %d: succ getting num.\n",i);
#endif
		// generate bit vector to get ready for the active var analysis

		// do active var analysis
		cur_ic=bb[i].last_ic;
		while(cur_ic!=fir_ic){

			cur_ic=cur_ic->prev;
		}
#ifdef DEBUG
		// printf("Block %d: succ do active var analysis\n",i);
#endif
	}
}

// Register
void InitRegs(){
	regs=(RegDesc)malloc(sizeof(struct RegDesc_)*_REG_NUM_);
#ifdef DEBUG
	// printf("Init Regs.\n");
#endif
	for(int i=0; i<_REG_NUM_; ++i){
		// printf("regNameArr=%s\n",regNameArr[i]);
		regs[i].name = regNameArr[i];
		// printf("reg name assign succ!\n");
		regs[i].var = NULL;
	}
}

void InitVars(){
#ifdef DEBUG
	// printf("Init Var and Temp Var.\n");
#endif
	var=(VarDesc)malloc(sizeof(struct VarDesc_)*(varNum+1024));
	temp_var=(VarDesc)malloc(sizeof(struct VarDesc_)*(tempVarNum+1024));
	for(int i=0;i<varNum;i++){
		var[i].reg=0;//constant value 0
		var[i].offset=0;
	}
	for(int i=0;i<tempVarNum;i++){
		temp_var[i].reg=0;
		temp_var[i].offset=0;
	}
}

int getReg(Operand op, FILE *fp){
	/*****************************
	/* Still need implementation *
	*****************************/
	/*************************
	/* Wrong: Alloc new regs *
	*************************/
#ifdef DEBUG
	// printf("Enter getReg!\n");
#endif
	unsigned id=op->u.var_no;
	int ret;
	int pointer;
	bool has_looped=true;
	// PrintfOperand(op);
	switch(op->kind){
	//use switch and macro to speed up
	case OP_VARIABLE:
		// printf("case variable\n");
		ret=var[id].reg;
		pointer=cur_reg_var;
 		if(ret==0){
			do{
				if(regs[pointer+18].var==NULL){
					has_looped=false;
					break;
				}
				pointer=(pointer+1)%8;
			}while(pointer!=cur_reg_var);
			// printf("get over while!\npointer=%d\n",pointer);
			if(has_looped==true&&pointer==cur_reg_var){//store old and get new id
				pointer=(pointer+1)%8;
				// wrong here
				// how to deal with fp?
				regs[pointer+18].var->offset=offset;
				fprintf(fp,"\tsw %s, %d($fp)\n"
					, regs[pointer+18].name,offset);
				offset-=4;
				if(regs[pointer+18].var->reg==pointer+18)
					regs[pointer+18].var->reg=0;
			}
			// printf("get over if\n");
			cur_reg_var=pointer;
			regs[cur_reg_var+18].var=var+id*sizeof(struct VarDesc_);
			var[id].reg=cur_reg_var+18;
			ret=cur_reg_var+18;
		}
		return ret;
	case OP_TEMP_VAR:
		// printf("case tmp var\n");
		ret=temp_var[id].reg;
		pointer=cur_reg_temp_var;
		if(ret==0){
			// printf("ready for loop\n");
			do{
				if(regs[pointer+8].var==NULL){
					has_looped=false;
					break;
				}
				pointer=(pointer+1)%10;
			}while(pointer!=cur_reg_temp_var);
			// printf("ret=0 and loop end\n");
			if(has_looped==true&&pointer==cur_reg_temp_var){
				pointer=(pointer+1)%10;
				regs[pointer+8].var->offset=offset;
				offset-=4;
				fprintf(fp,"\tsw %s, %d($fp)\n"
					, regs[pointer+8].name,offset);
				if(regs[pointer+8].var->reg==pointer+8)
					regs[pointer+8].var->reg=0;
			}
			cur_reg_temp_var=pointer;
			regs[cur_reg_temp_var+8].var=temp_var+id*sizeof(struct VarDesc_);
			temp_var[id].reg=cur_reg_temp_var+8;
			ret=cur_reg_temp_var+8;
		}
		return ret;
	case OP_GET_ADDR:
		assert(0);
	case OP_VAR_ADDR:
	case OP_TEMP_VAR_ADDR:
		// printf("case var addr/temp var addr\n");
		return getReg(op->u.addr,fp);
	case OP_CONSTANT:
	default:
		assert(0);
	}
	return 0;
}

int findVar(Operand op){
	switch(op->kind){
	case OP_VARIABLE:
	case OP_TEMP_VAR:
		return op->u.var_no;
	default:
		assert(0);
	}
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
		left_id=getReg(op_left,fp);
		//x := 
		if(op_right->kind==OP_CONSTANT){
			//x := #k
			fprintf(fp,"\tli %s, %d\n",regs[left_id].name,op_right->u.value);
		}
		else if(op_right->kind==OP_TEMP_VAR||op_right->kind==OP_VARIABLE){
			//x := y
			right_id=getReg(op_right,fp);
			fprintf(fp,"\tmove %s, %s\n",regs[left_id].name,regs[right_id].name);
		}
		else if(op_right->kind==OP_VAR_ADDR||op_right->kind==OP_TEMP_VAR_ADDR){
			//x := *y
			right_id=getReg(op_right,fp);
			fprintf(fp,"\tlw %s, 0(%s)\n",regs[left_id].name,regs[right_id].name);
		}
		else if(op_right->kind==OP_GET_ADDR){
			//x := &y
			unsigned id=op_right->u.var_no;
			fprintf(fp,"\tla %s, %d($fp)\n",regs[left_id].name,var[id].offset);
		}
		else{
			assert(0);
		}
	}
	else if(op_left->kind==OP_VAR_ADDR||op_left->kind==OP_TEMP_VAR_ADDR){
		if(op_right->kind==OP_CONSTANT){
			//*x = #k;
			fprintf(fp,"\tsw %d, 0(%s)\n",op_right->u.value,regs[left_id].name);
		}
		else if(op_right->kind==OP_VARIABLE||op_right->kind==OP_TEMP_VAR){
			//*x = y;
			right_id=getReg(op_right,fp);	
			fprintf(fp,"\tsw %s, 0(%s)\n",regs[right_id].name,regs[left_id].name);
		}
		else{
			assert(0);
		}
	}
	else{
		assert(0);
	}
	if(op_left->u.var_no==11){
	}
}

void MipsCodeAddSubMulDiv(InterCode ic,FILE *fp){
#ifdef DEBUG
	switch(ic->kind){
		case IC_ADD://4
			//PRINTF_BINOP("+ ");
			break;
		case IC_SUB://5
			//PRINTF_BINOP("- ");
			break;
		case IC_MUL://6
			//PRINTF_BINOP("* ");
			break;
		case IC_DIV://7
			//PRINTF_BINOP("/ ");
			break;
		default:
			assert(0);
	}
#endif
	Operand op_res=ic->u.binOp.result;
	Operand op1=ic->u.binOp.op1;
	Operand op2=ic->u.binOp.op2;
	int res_id, op1_id, op2_id;
	bool op1_cons=(op1->kind==OP_CONSTANT)?true:false;
	bool op2_cons=(op2->kind==OP_CONSTANT)?true:false;
	bool op_var=((op1->kind==OP_VARIABLE||op1->kind==OP_TEMP_VAR||op1->kind==OP_GET_ADDR||op1->kind==OP_TEMP_VAR_ADDR)
		&&(op2->kind==OP_VARIABLE||op2->kind==OP_TEMP_VAR||op2->kind==OP_GET_ADDR||op2->kind==OP_TEMP_VAR_ADDR))?true:false;
	res_id=getReg(op_res,fp);	
	if(op1_cons){
		op2_id=getReg(op2,fp);
		switch(ic->kind){
		case IC_ADD:
			// x = #k + y, modified to x = y + #k
			fprintf(fp,"\taddi %s, %s, %d\n",regs[res_id].name,regs[op2_id].name,op1->u.value);
			break;
		case IC_SUB:
			/*****************************
			/* Still need implementation *
			*****************************/
			// x = #k - y may have bugs here? but who knows!
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
		op1_id=getReg(op1,fp);
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
		op1_id=getReg(op1,fp);
		op2_id=getReg(op2,fp);
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

void MipsCodeGoto(InterCode ic,FILE *fp){
	fprintf(fp,"\tj label%d\n",ic->u.sinOp.op->u.var_no);
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
		op1_id=getReg(op1,fp);
		if(op2->kind!=OP_CONSTANT){
			op2_id=getReg(op2,fp);
			if(strcmp(relop,"==")==0){
				fprintf(fp,"\tbeq %s, %s, label%d\n",regs[op1_id].name,regs[op2_id].name,label_num);
			}
			else if(strcmp(relop,"!=")==0){
				fprintf(fp,"\tbne %s, %s, label%d\n",regs[op1_id].name,regs[op2_id].name,label_num);
			}
			else if(strcmp(relop,">")==0){
				fprintf(fp,"\tbgt %s, %s, label%d\n",regs[op1_id].name,regs[op2_id].name,label_num);
			}
			else if(strcmp(relop,"<")==0){
				fprintf(fp,"\tblt %s, %s, label%d\n",regs[op1_id].name,regs[op2_id].name,label_num);
			}
			else if(strcmp(relop,">=")==0){
				fprintf(fp,"\tbge %s, %s, label%d\n",regs[op1_id].name,regs[op2_id].name,label_num);
			}
			else if(strcmp(relop,"<=")==0){
				fprintf(fp,"\tble %s, %s, label%d\n",regs[op1_id].name,regs[op2_id].name,label_num);
			}
			else{
				assert(0);
			}
		}
		else if(op2->kind==OP_CONSTANT){
			if(strcmp(relop,"==")==0){
				fprintf(fp,"\tbeq %s, %d, label%d\n",regs[op1_id].name,op2->u.value,label_num);
			}
			else if(strcmp(relop,"!=")==0){
				fprintf(fp,"\tbne %s, %d, label%d\n",regs[op1_id].name,op2->u.value,label_num);
			}
			else if(strcmp(relop,">")==0){
				fprintf(fp,"\tbgt %s, %d, label%d\n",regs[op1_id].name,op2->u.value,label_num);
			}
			else if(strcmp(relop,"<")==0){
				fprintf(fp,"\tblt %s, %d, label%d\n",regs[op1_id].name,op2->u.value,label_num);
			}
			else if(strcmp(relop,">=")==0){
				fprintf(fp,"\tbge %s, %d, label%d\n",regs[op1_id].name,op2->u.value,label_num);
			}
			else if(strcmp(relop,"<=")==0){
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
		op2_id=getReg(op2,fp);
		if(strcmp(relop,"==")==0){
			fprintf(fp,"\tbeq %s, %d, label%d\n",regs[op2_id].name,op1->u.value,label_num);
		}
		else if(strcmp(relop,"!=")==0){
			fprintf(fp,"\tbne %s, %d, label%d\n",regs[op2_id].name,op1->u.value,label_num);
		}
		else if(strcmp(relop,">")==0){
			fprintf(fp,"\tble %s, %d, label%d\n",regs[op2_id].name,op1->u.value,label_num);
		}
		else if(strcmp(relop,"<")==0){
			fprintf(fp,"\tbge %s, %d, label%d\n",regs[op2_id].name,op1->u.value,label_num);
		}
		else if(strcmp(relop,">=")==0){
			fprintf(fp,"\tblt %s, %d, label%d\n",regs[op2_id].name,op1->u.value,label_num);
		}
		else if(strcmp(relop,"<=")==0){
			fprintf(fp,"\tbgt %s, %d, label%d\n",regs[op2_id].name,op1->u.value,label_num);
		}
		else{
			assert(0);
		}
	}
}

void MipsCodeFunction(InterCode ic,FILE *fp){
	/*****************************
	/* May need implementation   *
	*****************************/
	// sp-=4, store ret addr
	int frame_sz=tempVarNum<<2;
	param_num=find_item(ic->u.sinOp.op->u.name,FUNCTION)->var_type->u.function->para_num;
#ifdef DEBUG
	// printf("to print function,%s:%d\n",ic->u.sinOp.op->u.name,param_num);
#endif
	offset=-4;//for a new func set offset = 0
	fprintf(fp, "%s:\n",ic->u.sinOp.op->u.name);
	fputs("\tsubu $sp, $sp, 4\n", fp);
	fputs("\tsw $fp, 0($sp)\n", fp);
	fputs("\tmove $fp, $sp\n", fp);
	fprintf(fp, "\tsubu $sp, $sp, %d\n", frame_sz);
#ifdef DEBUG
	// printf("end print function.\n");
#endif
}

void MipsCodeReturn(InterCode ic,FILE *fp){
	/*****************************
	/* May need implementation   *
	*****************************/
	Operand op=ic->u.sinOp.op;
	int frame_sz=tempVarNum<<2;
	param_num=0;
	cur_param=0;
	// printf("to print return.\n");
	if(op->kind==OP_CONSTANT){
		fprintf(fp, "\tli $v0, %d\n", op->u.value);
	}
	else{
		int t_id=getReg(op, fp);
		fprintf(fp, "\tmove $v0, %s\n", regs[t_id].name);
	}
	fprintf(fp, "\taddi $sp, $sp, %d\n", frame_sz);
	fputs("\tlw $fp, 0($sp)\n", fp);
	fputs("\taddi $sp, $sp, 4\n", fp);
	fputs("\tjr $ra\n", fp);
	// printf("end print return.\n");
}

void MipsCodeDec(InterCode ic,FILE *fp){
	/*****************************
	/* May need implementation   *
	*****************************/
	// printf("Enter MipsCodeDec!\n");
	// printf("------%d------------\n",offset);
	unsigned id=ic->u.dec.op->u.var_no;
	var[id].offset=offset;
	// printf("array:v%d\n",id);
	offset-=ic->u.dec.size;
	//int id=getReg(ic->u.dec.op, fp);
	//fprintf(fp, "li %s, %d\n",regs[id].name, ic->u.dec.size);
}

void MipsCodeArg(InterCode ic,FILE *fp){
	/*****************************
	/* May need implementation   *
	*****************************/
	//printf("Enter MipsCodeArg!\n");
	int t_id=-1;
	if(ic->u.sinOp.op->kind!=OP_CONSTANT)
		t_id=getReg(ic->u.sinOp.op,fp);
	// printf("arg regs:%s\n",regs[t_id].name);
	ArgList p=(ArgList)malloc(sizeof(struct ArgList_));
	p->op=ic->u.sinOp.op;
	p->reg_id=t_id;
	p->next=NULL;
	if(arg_head==NULL){
		arg_head=arg_tail=p;
	}
	else{
		arg_tail->next=p;
		arg_tail=p;
	}
	// if(cur_arg<4){
	// 	fprintf(fp, "\tmove $a%d, %s\n", cur_arg, regs[t_id].name);
	// }
	// else{
	// 	// wrong here, you should start from here
	// 	fprintf(fp, "\tlw $s0, \n");
	// 	sprintf(str, "\tlw $s0, %d($fp)\n\tsubu $sp, $sp, 4\n\tlw $s0, 0($sp)\n", arg->offset);
	// 	fprintf(fp, "\tsw %s, %d($sp)\n", regs[t_id].name, (cur_arg-4)<<2);
	// }
	++cur_arg;
}

// Stack Frame //
			// Saved Reg t0 //  -
			// Saved Reg t1 //   |>only save
			// Saved Reg .. //   | temp var in use 
			// Saved Reg t9 //  -
			// Saved Reg s0 //  -
			// Saved Reg s1 //   |>save all
			// Saved Reg .. //   |
			// Saved Reg s7 //  -
			// Parameter n  //
			// ...........  //
			// Parameter 6  //
			// Parameter 5  //
			// Return addr  //
			//  Temp var 1  //
			//  Temp var 2  //
			//  ..........  //
// organize stack just like showed above
void MipsCodeCall(InterCode ic,FILE *fp){
	/*****************************
	/* May need implementation  *
	*****************************/
	// printf("Enter MipsCodeCall\n");
	int temp_save_sz=0;
	bool flag[10];
	for(int i=8;i<18;i++){
		if(regs[i].var!=NULL){
			temp_save_sz+=4;
			fprintf(fp, "\tsw %s, -%d($sp)\n", regs[i].name, temp_save_sz);
			flag[i-8]=true;
		}
		else{
			flag[i-8]=false;
		}
	}
	for(int i=18;i<26;i++){
		temp_save_sz+=4;
		fprintf(fp, "\tsw %s, -%d($sp)\n", regs[i].name, temp_save_sz);
	}
	fprintf(fp, "\taddi $sp, $sp, -%d\n", temp_save_sz);
	int dec_sp=(cur_arg-4>0)?((cur_arg-4)<<2):0;
	dec_sp+=4+find_item(ic->u.sinOp.op->u.name,FUNCTION)->var_type->u.function->para_num*4;//for $ra
	fprintf(fp, "\taddi $sp, $sp, -%d\n", dec_sp);
	int id=0;
	ArgList p=arg_head;
	while(p!=NULL){
/*
		if(id<4){
			int t_id=getReg(p->op,fp);
			p->reg_id=t_id;
			printf("\tmove $a%d, %s\n", id, regs[p->reg_id].name);
			fprintf(fp, "\tmove $a%d, %s\n", id, regs[p->reg_id].name);
		}
		else{
*/
		if(p->reg_id!=-1)
			fprintf(fp, "\tsw %s, %d($sp)\n", regs[p->reg_id].name, (id+1)<<2);
		else{
			fprintf(fp,"\tli $a0, %d\n",p->op->u.value);
			fprintf(fp, "\tsw $a0, %d($sp)\n", (id+1)<<2);
		}
		//}
		++id;
		p=p->next;
	}
	fputs("\tsw $ra, 0($sp)\n", fp);
	fprintf(fp, "\tjal %s\n", ic->u.sinOp.op->u.name);
	// printf("ready to get reg\n");
	fputs("\tlw $ra, 0($sp)\n", fp);
	fprintf(fp, "\taddi $sp, $sp, %d\n", dec_sp);

	int cur_save_sz=temp_save_sz;
	for(int i=8;i<18;i++){
		if(flag[i-8]){
			cur_save_sz-=4;
			fprintf(fp, "\tlw %s, %d($sp)\n", regs[i].name, cur_save_sz);
		}
	}
	for(int i=18;i<26;i++){
		cur_save_sz-=4;
		fprintf(fp, "\tlw %s, %d($sp)\n", regs[i].name, cur_save_sz);
	}
	fprintf(fp, "\taddi $sp, $sp, %d\n", temp_save_sz);
	int t_id=getReg(ic->u.assign.left,fp);
	// printf("succ get reg\n");
	fprintf(fp, "\tmove %s, $v0\n", regs[t_id].name);
	//re init
	cur_arg=0;
	while(arg_head!=NULL){
		p=arg_head;
		arg_head=arg_head->next;
		free(p);
	}
	arg_head=NULL;
	arg_tail=NULL;
}

void MipsCodeParam(InterCode ic,FILE *fp){
	/*****************************
	/* May need implementation   *
	*****************************/
	// printf("Enter mips code param\n");
	Operand op=ic->u.sinOp.op;
	int id=getReg(op, fp);
	/*if(cur_param<4){
		fprintf(fp, "\tmove %s, $a%d\n", regs[id].name, cur_param);
	} 
	else{
	*/
		fprintf(fp, "\tlw %s, %d($fp)\n", regs[id].name, ((param_num-cur_param)<<2)+4);
	//}
	++cur_param;
}

void MipsCodeRead(InterCode ic,FILE *fp){
	fputs("\taddi $sp, $sp, -4\n", fp);
	fputs("\tsw $ra, 0($sp)\n", fp);
	fputs("\tjal read\n", fp);
	int t_id=getReg(ic->u.sinOp.op,fp);
	fprintf(fp, "\tmove %s, $v0\n", regs[t_id].name);
	fputs("\tlw $ra, 0($sp)\n", fp);
	fputs("\taddi $sp, $sp, 4\n", fp);
}

void MipsCodeWrite(InterCode ic,FILE *fp){
	fputs("\taddi $sp, $sp, -4\n", fp);
	fputs("\tsw $ra, 0($sp)\n", fp);
	if(ic->u.sinOp.op->kind==OP_CONSTANT){
		fprintf(fp, "\tli $a0, %d\n", ic->u.sinOp.op->u.value);
	}
	else{
		int t_id=getReg(ic->u.sinOp.op,fp);
		if(ic->u.sinOp.op->kind==OP_VARIABLE||ic->u.sinOp.op->kind==OP_TEMP_VAR
			||ic->u.sinOp.op->kind==OP_GET_ADDR){
			fprintf(fp, "\tmove $a0, %s\n", regs[t_id].name);
		}
		else if(ic->u.sinOp.op->kind==OP_VAR_ADDR||ic->u.sinOp.op->kind==OP_TEMP_VAR_ADDR){
			fprintf(fp, "\tlw $a0, 0(%s)\n", regs[t_id].name);
		}
	}
	fputs("\tjal write\n", fp);
	fputs("\tlw $ra, 0($sp)\n", fp);
	fputs("\taddi $sp, $sp, 4\n", fp);
}
