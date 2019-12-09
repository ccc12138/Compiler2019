#include "translate.h"

// DEBUG macro is defined in syntaxTree.h

/* some useful functions */
Operand look_Up(char *name){
	// TO IMPLEMENT
	unsigned int index = hash_pjw(name);
	struct item *tableItem = table[index];
	while(tableItem!=NULL){
		if(strcmp(tableItem->var_name,name)==0){
			break;
		}
		tableItem=tableItem->next;
	}
#ifdef DEBUG
	assert(tableItem!=NULL);
#endif
	if(tableItem->op!= NULL){
		return tableItem->op;
	}
	Type p = tableItem->var_type;
	Operand tableOp=(Operand)malloc(sizeof(struct Operand_));
	memset(tableOp,0,sizeof(struct Operand_));
	switch(tableItem->var_type->kind){
		case BASIC:
			if(tableItem->var_type->u.basic==INT){
				tableOp->kind=OP_VARIABLE;
				tableOp->u.var_no=varNum;
				++varNum;
			}
#ifdef DEBUG
			else{// FLOAT is impossible
				assert(0);
			}
#endif // DEBUG
			break;
		case ARRAY:
			tableOp->kind=OP_VAR_ADDR;
			tableOp->u.addr=(Operand)malloc(sizeof(struct Operand_));
			Operand opp = tableOp->u.addr;
			while(p->kind==ARRAY&&p->u.array.elem->kind==ARRAY){
				opp->kind=OP_VAR_ADDR;
				opp->u.addr=(Operand)malloc(sizeof(struct Operand_));
				opp = opp->u.addr;
				p = p->u.array.elem;
			}
			opp->kind=OP_VARIABLE;
			opp->u.var_no=varNum;
			++varNum;
			break;
		case STRUCTURE:
			break;
		case FUNCTION:
			break;
		default:
			assert(0);
	}
	tableItem->op = tableOp;
	// printf("%s-----\n",name);
	// PrintfOperand(tableItem->op);
	return tableOp;
}

Operand new_Temp(){
	Operand tempOp=(Operand)malloc(sizeof(struct Operand_));
	memset(tempOp,0,sizeof(struct Operand_));
	tempOp->kind=OP_TEMP_VAR;
	tempOp->u.var_no=tempVarNum;
	++tempVarNum;
	return tempOp;
}

Operand new_Label(){
	Operand tempOp=(Operand)malloc(sizeof(struct Operand_));
	memset(tempOp,0,sizeof(struct Operand_));
	tempOp->kind=OP_LABEL;
	tempOp->u.var_no=labelNum;
	++labelNum;
	return tempOp;
}

/* High level Definitions */
void translate_Program(treeNode* root){
	switch(root->branch){
		case 1:
#ifdef DEBUG
			// printf("case 1\n");
#endif // DEBUG
			translate_ExtDefList(root->childp);
			break;
		default:
			assert(0);
	}
	return;
}

void translate_ExtDefList(treeNode* root){
/*
ExtDefList -> ExtDef ExtDefList | NULL
*/
	switch(root->branch){
		case 1:
#ifdef DEBUG
			// printf("case 1\n");
#endif // DEBUG
			translate_ExtDef(root->childp);
			translate_ExtDefList(root->childp->right);
			break;
		case 2:
#ifdef DEBUG
			// printf("case 2\n");
#endif // DEBUG
			break;
		default:
			assert(0);
	}
	return;
}

void translate_ExtDef(treeNode* root){
/*
ExtDef -> Specifier ExtDecList SEMI | Specifier SEMI | Specifier FunDec CompSt
*/
	// TO IMPLEMENT
	switch(root->branch){
		case 1:
			/* error: no use of global var */
			translate_Specifier(root->childp);
			// translate_ExtDecList(root->childp->right);
			assert(0);
			break;
		case 2:
			translate_Specifier(root->childp);
			break;
		case 3:
			/* only define function */
			translate_Specifier(root->childp);
			translate_FunDec(root->childp->right);
			translate_CompSt(root->childp->right->right);
			break;
		case 4:
			/* error */
			// translate_Specifier(root->childp);
			// translate_FunDec(root->childp->right);
			assert(0);
			break;
		default:
			assert(0);
	}
	return;
}

/*
void translate_ExtDecList(treeNode* root){

//ExtDecList -> VarDec | VarDec COMMA ExtDecList

	if( root->childnum == 3 )
		translate_ExtDecList()
	else
		
	return;
}
*/

/* Specifiers */

void translate_Specifier(treeNode* root){
	switch(root->branch){
		case 1:break;
		case 2://means it is a struct specifier
			// printf("line %d: ",root->childp->lineno);
			printf("Cannot translate: Code contains variables or parameters of structure type.\n");
			exit(-1);
		default:
			assert(0);
	}
	return;
}

// void translate_StructSpecifier(treeNode* root){
// 	return;
// }


/* Declarators */
int isArray(char * name){
	if(name==NULL)	return -1;
	unsigned int index = hash_pjw(name);
	struct item *tableItem = table[index];
	while(tableItem!=NULL){
		if(strcmp(tableItem->var_name,name)==0){
			break;
		}
		tableItem=tableItem->next;
	}
	if ( tableItem->var_type->kind!=ARRAY ){
		return -1;
	}
	else{
		Type p = tableItem->var_type;
		int res = 1;
		while ( p->kind!=BASIC ){
			res *= p->u.array.size;
			p = p->u.array.elem;
		}
		res *= 4;
		return res;
	}
}
void translate_VarDec(treeNode* root, char* var_name){
/*
VarDec -> ID | VarDec LB INT RB
*/
	treeNode * p = root;
	while( p->childnum != 1 )
		p = p->childp ;
	
	/*VarDec -> ID */
	strcpy(var_name, p->childp->data.strd);
	return;
}

void translate_FunDec(treeNode* root){
/*
FunDec -> ID LP VarList RP | ID LP RP
*/
	char* func_name = (char*)malloc ( sizeof ( char ) * 32 );
	strcpy(func_name, root->childp->data.strd);
	/* interCode : [FUNCTION name:] */
	InsertCode_func( func_name );
	// PrintfCode();
	/*FunDec ->  ID LP VarList RP*/
	if( root->childnum == 4 )
	{
		/* parameters VarList */
		translate_VarList(root->childp->right->right);
	}
	return;
}

void translate_VarList(treeNode* root){
/*
VarList -> ParamDec COMMA VarList | ParamDec
*/
	translate_ParamDec(root->childp);
	if ( root -> childnum == 3 )
	{
		translate_VarList(root->childp->right->right);
	}
	return;
}

/*
a) 一维数组类型的变量可以作为函数参数(但函数不会返回一维数组类型的值)。
b) 可以出现高维数组类型的变量(但高维数组类型的变量不会作为函数的参数或返
回类值)。
*/

void translate_ParamDec(treeNode* root){
/*
ParamDec -> Specifier VarDec
*/
	char* var_name = (char*)malloc (sizeof(char)*32);
	translate_VarDec(root->childp->right, var_name);
	int res = isArray(var_name);
	if ( res == -1 )
	{
		InterCode newcode = malloc ( sizeof ( struct InterCode_ ) );
		newcode -> first_code = false;
		newcode -> kind = IC_PARAM;
		newcode -> u.sinOp.op = look_Up(var_name);
		InsertCode(newcode);
	}
	else{
		Operand var_op = look_Up(var_name);
		InterCode newcode = malloc ( sizeof ( struct InterCode_ ) );
		newcode -> first_code = false;
		newcode -> kind = IC_PARAM;
		newcode -> u.sinOp.op = var_op->u.addr;
		InsertCode(newcode);
		assert(var_op->u.addr->kind==OP_VARIABLE);
	}
	// PrintfCode();
	return;
}

/* Statements*/
void translate_CompSt(treeNode* root){
/*
CompSt -> LC DefList StmtList RC
*/
	translate_DefList(root->childp->right);
	translate_StmtList(root->childp->right->right);
	return;
}

void translate_StmtList(treeNode* root){
/*
StmtList -> Stmt StmtList | NULL
*/
	if ( root->childp != NULL ){
		translate_Stmt(root->childp);
		translate_StmtList(root->childp->right);
	}
	return;
}

void translate_Stmt(treeNode* root){
/*
Stmt -> Exp SEMI | CompSt | RETURN Exp SEMI | IF LP Exp RP Stmt | IF LP Exp RP Stmt ELSE Stmt | WHILE LP Exp RP Stmt
*/
#ifdef DEBUG
	// printf("translate_Stmt:%d\n",root->branch);
#endif
	switch(root->branch){
		case 1:{
			translate_Exp(root->childp, NULL);
			break;
		}
		case 2:{
			translate_CompSt(root->childp);
			break;
		}
		case 3:{
			Operand t1 = new_Temp();
			translate_Exp(root->childp->right, &t1);
			InterCode newcode = (InterCode)malloc(sizeof(struct InterCode_));
			newcode -> first_code = false;
			newcode->kind = IC_RETURN;
			newcode->u.sinOp.op = t1;
			InsertCode(newcode);
			// PrintfCode();
			break;
		}
		case 4:{
			Operand label1 = new_Label();
			Operand label2 = new_Label();
			translate_Cond(root->childp->right->right, label1, label2);
			InsertCode_label(label1);
			// PrintfCode();
			translate_Stmt(root->childp->right->right->right->right);
			InsertCode_label(label2);
			// code1 + [LABEL label1] + code2 + [LABEL label2]
			// PrintfCode();
			break;
		}
		case 5:{
			Operand label1 = new_Label();
			Operand label2 = new_Label();
			Operand label3 = new_Label();
			translate_Cond(root->childp->right->right, label1, label2);
			InsertCode_label(label1);
			// PrintfCode();
			translate_Stmt(root->childp->right->right->right->right);

			InterCode newcode_ = malloc ( sizeof ( struct InterCode_ ) );
			newcode_ -> first_code = false;
			newcode_ -> kind = IC_GOTO;
			newcode_ -> u.sinOp.op = label3;
			InsertCode(newcode_);// [GOTO label3]

			InsertCode_label(label2);
			// PrintfCode();
			translate_Stmt(root->childp->right->right->right->right->right->right);
			InsertCode_label(label3);
			// code1 + [LABEL label1] + code2 + [GOTO label3] + [LABEL label2] + code3 + [LABEL label3]
			// PrintfCode();
			break;
		}
		case 6:{
			Operand label1 = new_Label();
			Operand label2 = new_Label();
			Operand label3 = new_Label();
			InsertCode_label(label1);// [LABEL label1]
			// PrintfCode();
			translate_Cond(root->childp->right->right, label2, label3);// code1 = translate_Cond(Exp, label2, label3, sym_table)
			InsertCode_label(label2);// [LABEL label2]
			// PrintfCode();
			translate_Stmt(root->childp->right->right->right->right);// code2 = translate_Stmt(Stmt1, sym_table)
			InterCode newcode_ = malloc ( sizeof ( struct InterCode_ ) );
			newcode_ -> first_code = false;
			newcode_ -> kind = IC_GOTO;
			newcode_ -> u.sinOp.op = label1;
			InsertCode(newcode_);// [GOTO label1]
			// PrintfCode();
			InsertCode_label(label3);// [LABEL label3]
			// PrintfCode();
			break;
		}
		default:
			assert(0);
	}
	return;
}

/* Local Definitions */
void translate_DefList(treeNode* root){
/*
DefList -> Def DefList | NULL
*/
	if ( root->childnum != 0 ){
		translate_Def(root->childp);
		translate_DefList(root->childp->right);
	}
	return;
}

void translate_Def(treeNode* root){
/*
Def -> Specifier DecList SEMI
*/
	translate_Specifier(root->childp);
	translate_DecList(root->childp->right);
	return;
}

void translate_DecList(treeNode* root){
/*
DecList -> Dec | Dec COMMA DecList
*/
	if ( root->childnum == 1 ){
		translate_Dec(root->childp);
	}
	if ( root->childnum == 3 ){
		translate_Dec(root->childp);
		translate_DecList(root->childp->right->right);
	}
	return;
}

Operand changeiop(char *name){
	// TO IMPLEMENT
	unsigned int index = hash_pjw(name);
	struct item *tableItem = table[index];
	while(tableItem!=NULL){
		if(strcmp(tableItem->var_name,name)==0){
			break;
		}
		tableItem=tableItem->next;
	}
#ifdef DEBUG
	assert(tableItem!=NULL);
#endif
	assert(tableItem->op!= NULL);
	Operand var_op = tableItem->op;
	while(var_op->kind!=OP_VARIABLE){
		var_op = var_op->u.addr;
	}
	tableItem->op = var_op;
	return tableItem->op;
}
void translate_Dec(treeNode* root){
/*
Dec -> VarDec | VarDec ASSIGNOP Exp
*/
	char * var_name = (char*)malloc(sizeof(char)*32);
	translate_VarDec(root->childp, var_name);
	int res = isArray(var_name);
	if ( res != -1){
		Operand var_op = look_Up(var_name);
		var_op = changeiop(var_name);
		// PrintfOperand(var_op);
		InterCode newcode = malloc ( sizeof ( struct InterCode_ ) );
		newcode -> first_code = false;
		newcode -> kind = IC_DEC;
		newcode -> u.dec.op = (Operand)malloc(sizeof(struct Operand_));
		newcode -> u.dec.op -> kind = var_op -> kind;
		newcode -> u.dec.op -> u.var_no = var_op -> u.var_no;
		newcode -> u.dec.size = res;
		InsertCode(newcode);
	}
	if ( root->childnum == 1 ){
	}
	if ( root->childnum == 3 ){
		Operand p = look_Up(var_name);
		Operand t1 = new_Temp();
		translate_Exp(root->childp->right->right, &t1);	
		InterCode newcode = malloc ( sizeof ( struct InterCode_ ) );
		newcode -> first_code = false;
		newcode -> kind = IC_ASSIGN;
		newcode -> u.assign.right = t1;
		newcode -> u.assign.left = p;
		InsertCode(newcode);	
	}
	return;
}

char* findExpID(treeNode* root){
	switch(root->branch){
		case 8:
			return findExpID(root->childp);
		case 10:
			return root->childp->data.strd;
		default:
			return NULL;
	}
}

/* Expressions */
void translate_Exp(treeNode* root, Operand* place){
	// TO IMPLEMENT
#ifdef DEBUG
	char *Exp[15];
	Exp[1] = "Exp ASSIGNOP Exp";
	Exp[2] = "Exp AND OR RELOP Exp, NOT Exp";
	Exp[3] = "Exp + = * / Exp";
	Exp[4] = "LP Exp RP";
	Exp[5] = "- Exp";
	Exp[6] = "ID LP Args RP";
	Exp[7] = "ID LP RP";
	Exp[8] = "Exp LB Exp RB";
	Exp[9] = "Exp DOT ID";
	Exp[10] = "ID";
	Exp[11] = "INT";
	Exp[12] = "FLOAT";
	// printf("translate_Exp:%s\n",Exp[root->branch]);
#endif
	switch(root->branch){
		case 1:{
			// Exp ASSIGNOP Exp
#ifdef DEBUG
#endif
			Operand v_t;
			if ( root->childp->childnum != 1 ){
				// An array
				v_t=new_Temp();
				translate_Exp(root->childp, &v_t);
			}
			else{
				v_t = look_Up(root->childp->childp->data.strd);
			}
			Operand t1 = new_Temp();
			translate_Exp(root->childp->right->right, &t1);
			
			InterCode newcode = malloc ( sizeof ( struct InterCode_ ) );
			newcode -> first_code = false;
			newcode -> kind = IC_ASSIGN;
			newcode -> u.assign.right = t1;
			newcode -> u.assign.left = v_t;
			InsertCode(newcode);	
			// PrintfCode();
			if ( place!=NULL ){
				InterCode newcode_ = malloc ( sizeof ( struct InterCode_ ) );
				newcode -> first_code = false;
				newcode_ -> kind = IC_ASSIGN;
				newcode_ -> u.assign.right = v_t;
				newcode_ -> u.assign.left = *place;
				InsertCode(newcode_);
				// PrintfCode();
			
			}
			
			// code2 = [variable.name := t1] +4 [place := variable.name] ?

			break;
		}
		case 2:{
			// Exp "AND" "OR" "RELOP" Exp, NOT Exp
			Operand label1 = new_Label();
			Operand label2 = new_Label();

			InterCode newcode = malloc ( sizeof ( struct InterCode_ ) );
			newcode -> first_code = false;
			newcode -> kind = IC_ASSIGN;
			Operand t1=(Operand)malloc(sizeof(struct Operand_));
			memset(t1,0,sizeof(struct Operand_));
			t1->kind=OP_CONSTANT;
			t1->u.value = 0;
			newcode -> u.assign.right = t1;
			newcode -> u.assign.left = *place;
			InsertCode(newcode);
			// PrintfCode();
			
			translate_Cond(root, label1, label2);

			Operand t2=(Operand)malloc(sizeof(struct Operand_));
			memset(t2,0,sizeof(struct Operand_));
			t2->kind=OP_CONSTANT;
			t2->u.value = 1;

			InsertCode_label(label1);
			// PrintfCode();

			InterCode newcode_ = malloc ( sizeof ( struct InterCode_ ) );
			newcode -> first_code = false;
			newcode_ -> kind = IC_ASSIGN;
			newcode_ -> u.assign.right = t2;
			newcode_ -> u.assign.left = *place;
			InsertCode(newcode);
			// PrintfCode();

			InsertCode_label(label2);
			// PrintfCode();
			break;
		}
		case 3:{
			// 	
			Operand t1 = new_Temp();
			Operand t2 = new_Temp();
			translate_Exp(root->childp,&t1);
			translate_Exp(root->childp->right->right,&t2);
			if ( place != NULL )
			{
				InterCode newcode = malloc ( sizeof ( struct InterCode_ ) );
				newcode -> first_code = false;
				newcode -> u.binOp.result = *place;
				newcode -> u.binOp.op1 = t1;
				newcode -> u.binOp.op2 = t2;
				if ( strcmp(secc(),"PLUS")==0 ){
					newcode -> kind = IC_ADD;
				}
				if ( strcmp(secc(),"MINUS")==0 ){
					newcode -> kind = IC_SUB;
				}
				if ( strcmp(secc(),"STAR")==0 ){
					newcode -> kind = IC_MUL;
				}
				if ( strcmp(secc(),"DIV")==0 ){
					newcode -> kind = IC_DIV;
				}
				InsertCode(newcode);
				// PrintfCode();
			}
			break;
		}
		case 4:{
			// LP Exp RP
			translate_Exp(root->childp->right, place);
			break;
		}
		case 5:{
			// - Exp
			Operand t2 = new_Temp();
			translate_Exp(root->childp->right,&t2);
			if ( place != NULL )
			{
				InterCode newcode = malloc ( sizeof ( struct InterCode_ ) );
				newcode -> first_code = false;
				newcode -> u.binOp.result = *place;
				Operand t1=(Operand)malloc(sizeof(struct Operand_));
				memset(t1,0,sizeof(struct Operand_));
				t1->kind=OP_CONSTANT;
				t1->u.value = 0;
				newcode -> u.binOp.op1 = t1;
				newcode -> u.binOp.op2 = t2;
				newcode -> kind = IC_SUB;
				InsertCode(newcode);
				// PrintfCode();
			}
			break;
		}
		case 6:{
			// ID LP Args RP
			Operand arg_list[MAX_LEN];
			int size = 0;
			translate_Args(root->childp->right->right, arg_list, &size);
			if (strcmp(root->childp->data.strd, "write")==0){
				InterCode newcode = malloc ( sizeof ( struct InterCode_ ) );
				newcode -> first_code = false;
				newcode -> u.sinOp.op = arg_list[0];
				newcode -> kind = IC_WRITE;
				InsertCode(newcode);
				// PrintfCode();
			}
			else{
				int i = 0;
				for ( i = size-1 ; i >= 0 ; i -- ){
					InterCode newcode = malloc ( sizeof ( struct InterCode_ ) );
					newcode -> first_code = false;
					newcode -> u.sinOp.op = arg_list[i];
					newcode -> kind = IC_ARG;
					InsertCode(newcode);
				}
				struct item* funcp = find_item(root->childp->data.strd, FUNCTION);
				InterCode newcode = malloc ( sizeof ( struct InterCode_ ) );
				newcode -> first_code = false;
				newcode -> kind = IC_CALL;
				if (place!=NULL)
					newcode -> u.assign.left = *place;
				else
					newcode -> u.assign.left = new_Temp();
				Operand func = (Operand)malloc(sizeof(struct Operand_));
				func -> kind = OP_FUNCTION;
				func -> u.name = funcp->var_name;
				newcode -> u.assign.right = func;
				InsertCode(newcode);
				// PrintfCode();
			}
			
			break;
		}
		case 7:{
			// ID LP RP
			struct item* funcp = find_item(root->childp->data.strd, FUNCTION);
			InterCode newcode = malloc ( sizeof ( struct InterCode_ ) );
			newcode -> first_code = false;
			if (strcmp(funcp->var_name,"read")==0){
				newcode -> kind = IC_READ;
				newcode -> u.sinOp.op = *place;
			}
			else{
				newcode -> kind = IC_CALL;
				newcode -> u.assign.left = *place;
				Operand func = (Operand)malloc(sizeof(struct Operand_));
				func -> kind = OP_FUNCTION;
				func -> u.name = funcp->var_name;
				newcode -> u.assign.right = func;
			}
			InsertCode(newcode);
			// PrintfCode();
			break;
		}
		case 8:{
			// Exp LB Exp RB
			// array
			translate_Array(root,  place);
			break;
		}
		case 9:{
			// Exp DOT ID
			// no struct var exist
			// printf("line %d: ",root->childp->lineno);
			printf("Cannot translate: Code contains variables or parameters of structure type.\n");
			exit(-1);
			break;
		}
		case 10:{
			// ID
#ifdef DEBUG
			assert(place!=NULL);
#endif
			Operand p = look_Up(root->childp->data.strd);
			(*place)->kind=p->kind;
			(*place)->u = p->u;
			// PrintfOperand((*place));
			// printf("\n");
			break;
		}
		case 11:{
			// INT
#ifdef DEBUG
			assert(place!=NULL);
			// printf("%d\n",root->childp->data.intd);
#endif
			(*place)->kind=OP_CONSTANT;
			(*place)->u.value=root->childp->data.intd;
			break;
		}
		case 12:{
			// FLOAT
			assert(0);// P63 Assume 1
			break;
		}
		default:
			assert(0);

	}
	return;
}

void translate_Args(treeNode* root, Operand arg_list[], int *size){
/*
Args -> Exp COMMA Args | Exp
*/
#ifdef DEBUG
	//printf("translate_Args:%d\n",*size);
#endif
	Operand t1 = new_Temp();
	translate_Exp(root->childp, &t1);
	if (isArray(findExpID(root->childp))!=-1&&t1->kind==OP_VARIABLE)
		t1->kind=OP_GET_ADDR;
	if (isArray(findExpID(root->childp))!=-1&&t1->kind==OP_VAR_ADDR){
		while(t1->kind==OP_VAR_ADDR)
			t1 = t1->u.addr;
	}
	arg_list[*size] = t1;
	(*size) ++;
	if ( root -> childnum == 3 )
	{
		translate_Args(root->childp->right->right, arg_list, size);
	}
	return;
}

void translate_Cond(treeNode* root, Operand label_true, Operand label_false){
	int case_k = 0;
	if ( root->childnum == 3 && strcmp(secc(),"AND")==0 )
		case_k = 3;
	if ( root->childnum == 3 && strcmp(secc(),"OR")==0 )
		case_k = 4;
	if ( root->childnum == 3 && strcmp(secc(),"RELOP")==0 )
		case_k = 1;
	if ( root->childnum == 2 && strcmp(firc(),"NOT")==0 )
		case_k = 2;
#ifdef DEBUG
	// printf("translate_Cond:%d\n",case_k);
#endif
	switch(case_k){
		case 1:{
			// Exp1 RELOP Exp2
			Operand t1 = new_Temp();
			Operand t2 = new_Temp();
			translate_Exp(root->childp, &t1);
			// PrintfOperand(t1);
			// printf("\n");
			translate_Exp(root->childp->right->right, &t2);
			char* op;
			op = root->childp->right->data.strd;
			InterCode newcode = malloc ( sizeof ( struct InterCode_ ) );
			newcode -> first_code = false;
			newcode -> kind = IC_IFGOTO;
			newcode -> u.triOp.op1 = t1;
			newcode -> u.triOp.op2 = t2;
			newcode -> u.triOp.label = label_true;
			newcode -> u.triOp.relop = op;
			InsertCode(newcode);
			// PrintfCode();
			InterCode newcode_ = malloc ( sizeof ( struct InterCode_ ) );
			newcode -> first_code = false;
			newcode_ -> kind = IC_GOTO;
			newcode_ -> u.sinOp.op = label_false;
			InsertCode(newcode_);
			// PrintfCode();
			break;
		}
		case 2:{
			// NOT Exp1
			translate_Cond(root->childp->right, label_false, label_true);
			break;	
		}
		case 3:{
			// Exp1 AND Exp2
			Operand label1 = new_Label();
			translate_Cond(root->childp, label1, label_false);
			InsertCode_label(label1);
			// PrintfCode();
			translate_Cond(root->childp->right->right, label_true, label_false) ;
			break;
		}
		case 4:{
			// Exp1 OR Exp2
			Operand label1 = new_Label();
			translate_Cond(root->childp, label_true, label1);
			InsertCode_label(label1);
			// PrintfCode();
			translate_Cond(root->childp->right->right, label_true, label_false);
			break;
		}
		default:{
			Operand t1 = new_Temp();
			translate_Exp(root, &t1);
			Operand t2=(Operand)malloc(sizeof(struct Operand_));
			memset(t2,0,sizeof(struct Operand_));
			t2->kind=OP_CONSTANT;
			t2->u.value = 0;
			InterCode newcode = malloc ( sizeof ( struct InterCode_ ) );
			newcode -> first_code = false;
			newcode -> kind = IC_IFGOTO;
			newcode -> u.triOp.op1 = t1;
			newcode -> u.triOp.op2 = t2;
			newcode -> u.triOp.label = label_true;
			newcode -> u.triOp.relop = malloc ( sizeof ( char )*32 );
			newcode -> u.triOp.relop = "!=";
			InsertCode(newcode);
			// PrintfCode();
			InterCode newcode_ = malloc ( sizeof ( struct InterCode_ ) );
			newcode -> first_code = false;
			newcode_ -> kind = IC_GOTO;
			newcode_ -> u.sinOp.op = label_false;
			InsertCode(newcode_);
			// PrintfCode();
		}
			// other cases
	}
	return;
}

void arraysize(char* name,int* size, int*len){
	unsigned int index = hash_pjw(name);
	struct item *tableItem = table[index];
	while(tableItem!=NULL){
		if(strcmp(tableItem->var_name,name)==0){
			break;
		}
		tableItem=tableItem->next;
	}
#ifdef DEBUG
	assert(tableItem!=NULL);
#endif
	Type p = tableItem->var_type;
	while(p->kind==ARRAY)
	{
		size[*len]=p->u.array.size;
		(*len)++;
		p=p->u.array.elem;
	}
}

void translate_Array(treeNode* root,  Operand* place){
#ifdef DEBUG
	// printf("translate_Array:%d\n",root->childnum);
#endif
	if ( root->childnum == 4 ){
		// Exp LB Exp RB
		if ( place == NULL )
		{
			return;
		}
		else{
			int typesize = 4;
			int len=0;
			int size[MAX_LEN];
			arraysize(findExpID(root), size, &len);
			treeNode *p = root;
			Operand bias=new_Temp();
			Operand t0=(Operand)malloc(sizeof(struct Operand_));
			memset(t0,0,sizeof(struct Operand_));
			t0->kind=OP_CONSTANT;
			t0->u.value = 0;
			InterCode newcod = malloc ( sizeof ( struct InterCode_ ) );
			newcod -> kind = IC_ASSIGN;
			newcod -> u.assign.right = t0;
			newcod -> u.assign.left = bias;
			InsertCode(newcod);
			int cnt=-1;
			int cur_size=1;
			while(p->branch!=10){
				Operand t1=new_Temp();
				translate_Exp(p->childp->right->right,&t1);
				Operand t2=(Operand)malloc(sizeof(struct Operand_));
				memset(t2,0,sizeof(struct Operand_));
				t2->kind=OP_CONSTANT;
				if(cnt==-1)
					cur_size=1;
				else
					cur_size=cur_size*size[cnt];
				t2->u.value = typesize*cur_size;
				Operand t3=new_Temp();
				InterCode newcode = malloc ( sizeof ( struct InterCode_ ) );
				newcode -> first_code = false;
				newcode -> u.binOp.result = t3;
				newcode -> u.binOp.op1 = t1;
				newcode -> u.binOp.op2 = t2;
				newcode -> kind = IC_MUL;
				InsertCode(newcode);

				InterCode newcode_ = malloc ( sizeof ( struct InterCode_ ) );
				newcode -> first_code = false;
				newcode_ -> u.binOp.result = bias;
				newcode_ -> u.binOp.op1 = bias;
				newcode_ -> u.binOp.op2 = t3;
				newcode_ -> kind = IC_ADD;
				InsertCode(newcode_);
				p = p->childp;
				cnt++;		
				// PrintfCode();
			}

			Operand t4=(Operand)malloc(sizeof(struct Operand_));
			translate_Exp(p,&t4);
			if (t4->kind==OP_VARIABLE)
				t4->kind=OP_GET_ADDR;
			while(t4->kind==OP_VAR_ADDR)
				t4 = t4->u.addr;

			Operand t5=new_Temp();
			InterCode newcode_ = malloc ( sizeof ( struct InterCode_ ) );
			newcode_ -> first_code = false;
			newcode_ -> u.binOp.result = t5;
			newcode_ -> u.binOp.op1 = bias;
			newcode_ -> u.binOp.op2 = t4;
			newcode_ -> kind = IC_ADD;
			InsertCode(newcode_);	
			// PrintfCode();
			if( place != NULL ){
				Operand t6=(Operand)malloc(sizeof(struct Operand_));
				memset(t6,0,sizeof(struct Operand_));
				t6->kind = OP_TEMP_VAR_ADDR;
				t6->u.addr = (Operand)malloc(sizeof(struct Operand_));
				t6->u.addr->kind = OP_TEMP_VAR;
				t6->u.addr->u.var_no = t5->u.var_no;
				(*place) = t6;
				// PrintfCode();
			}
		}
	}
	else{
		assert(0);
	}
}



