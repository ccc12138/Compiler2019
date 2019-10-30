#include "semantic.h"

// High Level Definitions
void Program(treeNode* root){
	// ExtDefList
	if(cnEq(1)&&strcmp(firc(),"ExtDefList")==0){
		printf("Program branch1\n");
		ExtDefList(root->childp);
	}
	else{
		printErr("Program");
	}
	return;
}

void ExtDefList(treeNode* root){
	// ExtDef ExtDefList
	if(cnEq(2)&&strcmp(firc(),"ExtDef")==0
		&&(strcmp(secc(),"ExtDefList")==0||strcmp(secc(),"EPSILON")==0)){
		printf("ExtDefList branch1\n");
		ExtDef(root->childp);
		ExtDefList(root->childp->right);
	}
	// epsilon
	else if(cnEq(0)){
		printf("ExtDefList branch2\n");
		return;
	}
	else{
		printErr("ExtDefList");
	}
	return;
}

void ExtDef(treeNode* root){
	// Specifier ExtDecList SEMI
	if(cnEq(3)&&strcmp(firc(),"Specifier")==0&&strcmp(secc(),"ExtDecList")==0
	&&strcmp(thic(),"SEMI")==0){
		printf("ExtDef branch1\n");
		Type spec_type=Specifier(root->childp);
		ExtDecList(root->childp->right,spec_type);
	}
	// Specifier SEMI
	else if(cnEq(2)&&strcmp(firc(),"Specifier")==0&&strcmp(secc(),"SEMI")==0){
		printf("ExtDef branch2\n");
		Specifier(root->childp);
	}
	// Specifier FunDec CompSt
	else if(cnEq(3)&&strcmp(firc(),"Specifier")==0&&strcmp(secc(),"FunDec")==0
	&&strcmp(thic(),"CompSt")==0){
		printf("ExtDef branch3\n");
		Type fun_type=Specifier(root->childp);
		printf("flag1\n");
		FunDec(root->childp->right,fun_type);
		printf("flag2\n");
		CompSt(root->childp->right->right);
		// Begin: need SYMTAB here and check FUNCTION errors


		// End
	}
	// Specifier FunDec SEMI
	else if(cnEq(3)&&strcmp(firc(),"Specifier")==0&&strcmp(secc(),"FunDec")==0
	&&strcmp(thic(),"SEMI")==0){// elective
		printf("ExtDef branch4\n");
		Type fun_type=Specifier(root->childp);
		FunDec(root->childp->right,fun_type);
		// Begin: need SYMTAB here and check FUNCTION errors

		
		// End
	}
	else{
		printErr("ExtDef");
	}
	return;
}

void ExtDecList(treeNode* root, Type var_type){
	// VarDec
	if(cnEq(1)&&strcmp(firc(),"VarDec")==0){
		printf("ExtDecList branch1\n");
		VarDec(root->childp,var_type);
	}
	// VarDec COMMA ExtDecList
	else if(cnEq(3)&&strcmp(firc(),"VarDec")==0&&strcmp(secc(),"COMMA")==0
	&&strcmp(thic(),"ExtDecList")==0){
		printf("ExtDecList branch2\n");
		VarDec(root->childp,var_type);
		ExtDecList(root->childp->right->right,var_type);
	}
	else{
		printErr("ExtDecList");
	}
	return;
}

// A.1.3 Specifiers
Type Specifier(treeNode *root){
	treeNode *p=root;
	/* Specifier -> TYPE | StructSpecifier */
	Type add_type = (Type)malloc(sizeof(struct Type_));
	if(cnEq(1)&&strcmp(p->childp->name,"TYPE")==0){
        add_type->kind = BASIC;
		if(strcmp(p->childp->data.strd,"int")==0)
			add_type->u.basic = INT;
		else if(strcmp(p->childp->data.strd,"float")==0)
			add_type->u.basic = FLOAT;
		else
			printf("error");
		return add_type;
    }
	else if(cnEq(1)&&strcmp(p->childp->name,"StructSpecifier")==0){
		add_type = StructSpecifier(p->childp);
	}
	else{
		printErr("Specifier");
	}
}
// StructSpecifier
Type StructSpecifier(treeNode *root){
	treeNode *p=root;
	Type add_type = (Type)malloc(sizeof(struct Type_));// return
	/* StructSpecifier -> STRUCT OptTag LC DefList RC | STRUCT Tag */
	if(strcmp(p->childp->name,"STRUCT")==0){
		if(p->childnum==5){
			FieldList add_struct = (FieldList)malloc(sizeof(struct FieldList_));
			// add_type->u.structure = add_struct   point to the head (for example struct a{})
			add_type->kind = STRUCTURE;
			/* OptTag -> ID |  */
			treeNode *OptTag = p->childp->right;//deal with the name of struct
			if( OptTag == NULL )

				/**********************
				*****NULL OR ""?*******
				***********************/

				add_struct -> name = "";
			else
				strcpy(add_struct -> name,OptTag->childp->data.strd);
			add_struct ->type-> kind = STRUCTURE;
			//next deal with add_struct->tail point to all var of the struct
			/* DefList -> Def DefList | */
			treeNode* DefList = p->childp->right->right->right;
			if( DefList->childp == NULL ){
				add_struct->tail=NULL;
			}
			else{
				while( DefList->childp != NULL ){
					treeNode* Def = DefList-> childp;	
					treeNode * DecList = Def->childp->right;
					treeNode * specifierp = Def->childp;
					/* DecList -> Dec | Dec COMMA DecList */
					while( DecList != NULL ){
						FieldList add_struct_new = (FieldList)malloc(sizeof(struct FieldList_));
						if( DecList -> childnum == 1 ){
							treeNode * Dec = DecList->childp;
							/* deal with Dec -> VarDec | VarDec ASSIGNOP Exp */
							// the later one is error type 15
							add_struct_new = VarDec(Dec->childp,Specifier(specifierp));
							DecList = NULL;
						}
						else if( DecList -> childnum == 3 ){
							treeNode * Dec = DecList->childp;
							/* deal with Dec -> VarDec | VarDec ASSIGNOP Exp*/
							add_struct_new = VarDec(Dec->childp,Specifier(specifierp));
							// the later one is error type 15
							DecList = DecList->childp->right->right;
						}
						else{
							printf("error!");
						}
						add_struct->tail = add_struct_new;
						add_struct = add_struct_new;
					}
					DefList = Def->right;
					
				}
			}
			add_type->u.structure = add_struct;
			return add_type;
		}
		else if(p->childnum==2){/* declaration */
			/*
			struct item* q = find_item(p->childp->right->childp->data.strd);
			if(q==NULL){
			*/
				/* error ouput */	
			/*}
			else{
				add_type = q->var_type;
				return add_type;
			}*/
		}
		else{
			printf("error!");		
		}
	}
	else{
		printf("error!");	
	}
}

// A.1.4 Declarators
// VarDec -> ID | VarDec LB INT RB
FieldList VarDec(treeNode* root,Type var_type){// Inherited Attribute
	treeNode *p=root;
	int i=0;
	/* VarDec -> ID | VarDEc LB INT RB */
	while(strcmp(p->childp->name,"ID")!=0){
        p=p->childp;
        i++;
    }

	FieldList add_var = (FieldList)malloc(sizeof(struct FieldList_));
	// printf("p->childp->data.strd=%s\n,p->childp->data.strd");
	if(add_var->name == NULL){
		add_var->name = (char*)malloc(sizeof(char)*32);
	}
	strcpy(add_var->name,p->childp->data.strd);
	// printf("add_var->name=%s\n,add_var->name");
	add_var->type = (Type)malloc(sizeof(struct Type_));
	/* root->childp->name == ID      ->     VarDec -> ID*/
	if(i==0){
        add_var->type->kind=BASIC;
        return add_var;
    }
	else if(i>=1){
	/* i-dimension array */
		add_var->type = MultiArray(root,i,var_type);
		return add_var;
	}
	else{
		printErr("VarDec");
	}
}

Type MultiArray(treeNode *root,int i,Type b){
	treeNode *tp = root;
	Type p = NULL;
	Type Array = (Type)malloc(sizeof(struct Type_));
	p = Array;
	int j=0;
	for(;j<i;j++){
		p->kind=ARRAY;
		p->u.array.size = tp->childp->right->right->data.intd;
		p->u.array.elem = (Type)malloc(sizeof(struct Type_));
		p = p->u.array.elem;
		tp = tp->childp;
	}
	p = b;
	return Array;
}


// malloc a new item
struct item* create_new(){
	struct item* add_new = (struct item*)malloc(sizeof(struct item));
	add_new -> var_type = (Type)malloc(sizeof(struct Type_));
	add_new -> var_name = (char*)malloc(sizeof(char)*32);
	return add_new;
}

// FunDec -> ID LP VarList RP | ID LP RP
Function FunDec(treeNode* root, Type fun_type){
	Function func= (Function)malloc(sizeof(struct Function_));
	//PrintDFS(root->childp,0);
	if(func->name == NULL){
		func->name = (char*)malloc(sizeof(char)*32);
	}
	strcpy(func->name,root->childp->data.strd);
	// printf("%s\n",func->name);
	func->isDef=0;
	func->para=NULL;
	func->fun_type=fun_type;
	// ID RP VarList RP
	if(cnEq(4)&&strcmp(firc(),"ID")==0&&strcmp(secc(),"LP")==0
	&&strcmp(thic(),"VarList")==0&&strcmp(fouc(),"RP")==0){
		func->para=VarList(root->childp->right->right);
		struct item* add_new = create_new();
		add_new -> next = NULL;
		add_new -> var_type -> kind = FUNCTION;
		add_new -> var_type -> u.function = func;
		strcpy(add_new -> var_name,func->name);
		add_item(add_new);
		// to add func into symbol table
	}
	else if(cnEq(3)&&strcmp(firc(),"ID")==0&&strcmp(secc(),"LP")==0
	&&strcmp(thic(),"RP")==0){
		func->para=NULL;
		struct item* add_new = create_new();
		add_new -> next = NULL;
		add_new -> var_type -> kind = FUNCTION;
		add_new -> var_type -> u.function = func;
		
		strcpy(add_new -> var_name,func->name);
		add_item(add_new);
		// func->isDef=1;
		// to add func into symbol table
	}
	else{
		printErr("FunDec");
	}
	return func;
}

// VarList -> ParamDec COMMA VarList | ParamDec 		+ ParamDec
FieldList VarList(treeNode* root){
	FieldList fieldl=(FieldList)malloc(sizeof(struct FieldList_));
	FieldList p = fieldl;
	//to implement
	treeNode* VarList = root;
	while( VarList->childnum == 3 ){
		/* each step deal with one ParamDec */
		treeNode* Param = VarList-> childp;
		treeNode * specifierp = Param->childp;
		treeNode * VarDecp = Param->childp->right;
		/* ParamDec -> Specifier VarDec */
		p->tail = VarDec(VarDecp,Specifier(specifierp));
		VarList = VarList->right->right->right;
	}
	if(VarList->childnum == 1)
	{
		/* each step deal with one ParamDec */
		treeNode* Param = VarList-> childp;
		treeNode * specifierp = Param->childp;
		treeNode * VarDecp = Param->childp->right;
		/* ParamDec -> Specifier VarDec */
		p->tail = VarDec(VarDecp,Specifier(specifierp));
		VarList = VarList->right->right->right;
	}
	return fieldl;
}

// Statements
void CompSt(treeNode* root){
	//LC DefList StmtList RC
	if(cnEq(4)&&strcmp(firc(),"LC")==0&&strcmp(secc(),"DefList")==0
		&&(strcmp(thic(),"StmtList")==0||strcmp(thic(),"EPSILON")==0)
		&&strcmp(fouc(),"RC")==0){
		printf("CompSt branch1\n");
		DefList(root->childp->right);
		printf("flag3\n");
		StmtList(root->childp->right->right);
	}
	else{
		printErr("CompSt");
	}
	return;
}

void StmtList(treeNode* root){
	// Stmt StmtList
	if(cnEq(2)&&strcmp(firc(),"Stmt")==0
		&&(strcmp(secc(),"StmtList")==0||strcmp(secc(),"EPSILON")==0)){
		printf("StmtList branch1\n");
		Stmt(root->childp);
		StmtList(root->childp->right);
	}
	// epsilon
	else if(cnEq(0)){
		return;
	}
	else{
		printErr("StmtList");
	}
	return;
}

void Stmt(treeNode* root){
	// Exp SEMI
	if(cnEq(2)&&strcmp(firc(),"Exp")==0&&strcmp(secc(),"SEMI")==0){
		printf("Stmt branch1\n");
		Exp(root->childp);
	}
	// CompSt
	else if(cnEq(1)&&strcmp(firc(),"CompSt")==0){
		printf("Stmt branch2\n");
		CompSt(root->childp);
	}
	// RETURN Exp SEMI
	else if(cnEq(3)&&strcmp(firc(),"RETURN")==0&&strcmp(secc(),"Exp")==0
		&&strcmp(thic(),"SEMI")==0){
		printf("Stmt branch3\n");
		Type ret_type=Exp(root->childp->right);
		// Begin: need SYMTAB here and check RETURN errors


		// End	
	}
	// IF LP Exp RP Stmt
	else if(cnEq(5)&&strcmp(firc(),"IF")==0&&strcmp(secc(),"LP")==0
		&&strcmp(thic(),"Exp")==0&&strcmp(fouc(),"RP")==0
		&&strcmp(fifc(),"Stmt")==0){
		printf("Stmt branch4\n");
		Exp(root->childp->right->right);
		Stmt(root->childp->right->right->right->right);
	}
	// IF LP Exp RP Stmt ELSE Stmt
	else if(cnEq(7)&&strcmp(firc(),"IF")==0&&strcmp(secc(),"LP")==0
		&&strcmp(thic(),"Exp")==0&&strcmp(fouc(),"RP")==0
		&&strcmp(fifc(),"Stmt")==0&&strcmp(sixc(),"ELSE")==0
		&&strcmp(sevc(),"Stmt")==0){
		printf("Stmt branch5\n");
		Exp(root->childp->right->right);
		Stmt(root->childp->right->right->right->right);
		Stmt(root->childp->right->right->right->right->right->right);
	}
	// WHILE LP Exp RP Stmt
	else if(cnEq(5)&&strcmp(firc(),"WHILE")==0&&strcmp(secc(),"LP")==0
		&&strcmp(thic(),"Exp")==0&&strcmp(fouc(),"RP")==0
		&&strcmp(fifc(),"Stmt")==0){
		printf("Stmt branch6\n");
		Exp(root->childp->right->right);
		Stmt(root->childp->right->right->right->right);
	}
	else{
		printErr("Stmt");
	}
	return;
}

// Local Definitions
/* add to the symbol table when defining */
void DefList(treeNode* root){
	/* like below */
	treeNode* DefList = root;
	while( DefList->childp != NULL ){
		/* each step deal with one type,semi and add it */
		treeNode* Def = DefList-> childp;
		// printf("Def-> childp=%s\n",Def->childp->name);			
		treeNode * DecList = Def->childp->right;
		treeNode * specifierp = Def->childp;
		Type p = Specifier(specifierp);
		/* DecList -> Dec | Dec COMMA DecList */
		while( DecList != NULL ){
			struct item* add_new = create_new();
			add_new -> next = NULL;			
			FieldList f = (FieldList)malloc(sizeof(struct FieldList_));
			treeNode * Dec = DecList->childp;
			/* deal with Dec -> VarDec | VarDec ASSIGNOP Exp */
			// the later one is error type 15
			f = VarDec(Dec->childp,p);
			printf("BACK\n");
			add_new->var_type = f->type;
			printf("flag4\n");
			strcpy(add_new->var_name,f->name);
			add_item(add_new);
			if( DecList -> childnum == 1 ){
				DecList = NULL;
			}
			else if( DecList -> childnum == 3 ){
				DecList = DecList->childp->right->right;
			}
			else{
					printf("error!");
			}
		}
		DefList = Def->right;
	}
}

// Experssions
Type Exp(treeNode* root){
	Type type;
	// Exp <sth.> Exp
	if(cnEq(3)&&strcmp(firc(),"Exp")==0&&strcmp(thic(),"Exp")==0){
		// Exp ASSIGNOP Exp
		if(strcmp(secc(),"ASSIGNOP")==0){
			Type ltype=Exp(root->childp);
			Type rtype=Exp(root->childp->right->right);
			if(ltype==NULL||rtype==NULL){
				return NULL;
			}
			else if(ltype->value==R_VALUE){
				printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n"
					, root->childp->lineno);
				return NULL;
			}
			else if(!typeEqual(ltype,rtype)){
				printf("Error type 5 at Line %d: Type mismatched for assignment.\n"
					, root->childp->lineno);
				return NULL;	
			}
			else{
				return ltype;
			}
		}

		/*
		 * Question: Does FLOAT/ARRAY/STRUCTURE sup AND/OR calculation?
		 */

		// Exp AND/OR/RELOP/PLUS/MINUS/STAR/DIV Exp
		else if(strcmp(secc(),"AND")==0||strcmp(secc(),"OR")==0
			||strcmp(secc(),"RELOP")==0||strcmp(secc(),"PLUS")==0
			||strcmp(secc(),"MINUS")==0||strcmp(secc(),"STAR")==0
			||strcmp(secc(),"DIV")==0){
			Type ltype=Exp(root->childp);
			Type rtype=Exp(root->childp->right->right);
			if(ltype==NULL||rtype==NULL){
				return NULL;
			}
			if(!typeEqual(ltype,rtype)||ltype->kind!=BASIC){
				return NULL;
			}
			return ltype;
			//else if(!typeEqual(ltype,rtype)||ltype->)
		}
		else{
			printErr("Exp OP Exp");
		}
	}
	// LP Exp RP
	else if(cnEq(3)&&strcmp(firc(),"LP")==0&&strcmp(secc(),"Exp")==0
		&&strcmp(thic(),"RP")){
		return Exp(root->childp->right);
	}
	// <sth.> Exp
	else if(cnEq(2)&&strcmp(secc(),"Exp")==0){
		// MINUS/NOT Exp
		if(strcmp(firc(),"MINUS")==0||strcmp(firc(),"NOT")==0){
			Type exp_type=Exp(root->childp->right);
			if(exp_type==NULL){
				return NULL;
			}
			else if(exp_type->kind!=BASIC){
				printf("Error type 7 at Line %d: Operands type mismatched\n", root->childp->lineno);
				return NULL;
			}
			exp_type->value=R_VALUE;
			return exp_type;
		}
		else{
			printErr("OP Exp");
		}
	}
	// ID LP Args RP
	else if(cnEq(4)&&strcmp(firc(),"ID")==0&&strcmp(secc(),"LP")==0
		&&strcmp(thic(),"Args")==0&&strcmp(fouc(),"RP")==0){
		// TO IMPLEMENT: ID CHECK ERROR TYPE 1, FUNCTION CHECK ERROR
		// THIS Exp IS R_VALUE
		// Begin:

		// End
	}
	// ID LP RP
	else if(cnEq(3)&&strcmp(firc(),"ID")==0&&strcmp(secc(),"LP")==0
		&&strcmp(thic(),"RP")==0){
		// TO IMPLEMENT: ID CHECK ERROR TYPE 1, FUNCTION CHECK ERROR
		// THIS Exp IS R_VALUE
		// Begin:

		// End
	}
	// Exp LB Exp RB
	else if(cnEq(4)&&strcmp(firc(),"Exp")==0&&strcmp(secc(),"LB")==0
		&&strcmp(thic(),"Exp")==0&&strcmp(fouc(),"RB")==0){

	}
	// Exp DOT ID
	else if(cnEq(3)&&strcmp(firc(),"Exp")==0&&strcmp(secc(),"DOT")==0
		&&strcmp(thic(),"ID")==0){
		// TO IMPLEMENT: Exp CHICK ERROR, ID CHECK ERROR TYPE 1, FUNCTION CHECK ERROR
		// THIS Exp IS ______?
		// Begin:

		// End
	}
	// <sth.>
	else if(cnEq(1)){
		// ID
		if(strcmp(firc(),"ID")==0){
			// TO IMPLEMENT: ID CHECK ERROR TYPE 1
			// THIS IS LR_VALUE
			// Begin:

			// End
		}
		// INT
		else if(strcmp(firc(),"INT")==0){
			MACRO_RETURN(INT);
		}
		// FLOAT
		else if(strcmp(firc(),"FLOAT")==0){
			MACRO_RETURN(FLOAT);
		}
		else{
			printErr("Exp->OP");
		}
	}
	else{
		printErr("Exp");
	}
	type=NULL;
	return type;
}

/*
 * Args Func can compare whether cur_para_type=symtable.func.para_type
 * Return true means equal, otherwise unequal
 */
bool Args(treeNode* root, FieldList para){
	if(root==NULL)
		return false;
	if(para==NULL)
		return false;

	Type exp_type = Exp(root->childp);
	if(!typeEqual(exp_type, para->type)){
		printf("Error type 9 at Line %d: Function parameters not match\n",root->childp->lineno);
		return false;
	}
	else if(cnEq(1)&&strcmp(firc(),"Exp")==0){
		return true;
	}
	else if(cnEq(3)&&strcmp(firc(),"Exp")==0&&strcmp(secc(),"COMMA")==0
		&&strcmp(thic(),"Args")==0){
		return Args(root->childp->right->right, para->tail);
	}
	else{
		printErr("Args");
	}
	return true;
}
