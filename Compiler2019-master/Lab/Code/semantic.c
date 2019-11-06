#include "semantic.h"

extern int semErrNum;
struct ListNode *listHead=NULL;
bool error = false;
// Linked List Func
void add_to_linked_list(char *name, int lineno){
	struct ListNode *p=(struct ListNode*)malloc(sizeof(struct ListNode));
	p->name=name;
	p->lineno=lineno;
	p->next=listHead;
	listHead=p;
}

void del_from_linked_list(char *name){
	// printf("name=%s\n",name);
	struct ListNode *p=listHead;
	if(p==NULL){// if use this func, this case is impossible.
		assert(0);
	}
	bool isDel=false;
	// printf("p->name=%s\n",p->name);
	if(strcmp(p->name,name)==0){
		p=p->next;
		free(listHead);
		listHead=p;
		return;
	}
	p=p->next;
	struct ListNode *q=listHead;
	while(p!=NULL){
		// printf("p->name=%s\n",p->name);
		if(strcmp(p->name,name)==0){
			struct ListNode *toDel=p;
			p=p->next;
			q->next=p;
			free(toDel);
			isDel=true;
			break;
		}
		p=p->next;
	}
	assert(isDel);
	return;
}

void judge_linked_list(){
	struct ListNode *p=listHead;
	while(p!=NULL){
		printf("Error type 18 at Line %d: Undefined function \"%s\"\n",p->lineno,p->name);
		p=p->next;
	}
}

// High Level Definitions
void Program(treeNode* root){
	// printf("Program\n");
	// ExtDefList
	if(cnEq(1)&&strcmp(firc(),"ExtDefList")==0){
		// printf("Program branch1\n");
		ExtDefList(root->childp);
	}
	else{
		printErr("Program");
	}
	if(error==false)
		judge_linked_list();
	return;
}

void ExtDefList(treeNode* root){
	// printf("ExtDefList\n");
	// printf("root->num=%d\n",root->childnum);
	// ExtDef ExtDefList
	if(cnEq(2)&&strcmp(firc(),"ExtDef")==0
		&&(strcmp(secc(),"ExtDefList")==0||strcmp(secc(),"EPSILON")==0)){
		// printf("ExtDefList branch1\n");
		ExtDef(root->childp);
		// printf("succ return!\n");
		ExtDefList(root->childp->right);
	}
	// epsilon
	else if(cnEq(0)){
		// printf("ExtDefList branch2\n");
		return;
	}
	else{
		printErr("ExtDefList");
	}
	return;
}

void ExtDef(treeNode* root){
	// printf("ExtDef\n");
	// Specifier ExtDecList SEMI
	if(cnEq(3)&&strcmp(firc(),"Specifier")==0&&strcmp(secc(),"ExtDecList")==0
	&&strcmp(thic(),"SEMI")==0){
		// printf("ExtDef branch1\n");
		Type spec_type=Specifier(root->childp);
		ExtDecList(root->childp->right,spec_type);
	}
	// Specifier SEMI
	else if(cnEq(2)&&strcmp(firc(),"Specifier")==0&&strcmp(secc(),"SEMI")==0)
	{
		// printf("ExtDef branch2\n");
		Specifier(root->childp);
	}
	// Specifier FunDec CompSt
	// func define: Error type 4, 19
	else if(cnEq(3)&&strcmp(firc(),"Specifier")==0&&strcmp(secc(),"FunDec")==0
	&&strcmp(thic(),"CompSt")==0){
		int tempSemErrNum=0;
		// printf("ExtDef branch3\n");
		Type fun_type=Specifier(root->childp);
		// printf("flag1----------------\n");
		Function func=FunDec(root->childp->right,fun_type,1);
		// printf("flag2-------------------------\n");
		struct item* add_new = create_new();
		add_new -> next = NULL;
		add_new -> var_type -> kind = FUNCTION;
		add_new -> var_type -> u.function = func;
		strcpy(add_new -> var_name,func->name);
		// test before add item
		struct item* po =find_item(add_new -> var_name, add_new -> var_type -> kind );
		if(po==NULL){
			// printf("add_item:ID:%s----type:%d\n",add_new->var_name,add_new->var_type->kind);
			add_item(add_new);
		}//never declare or define
		else if(po->var_type->kind==FUNCTION&&po->var_type->u.function->isDef==0){
			// printf("\n\nenter updateIsDef!\n");
			po->var_type->u.function->isDef=1;
			del_from_linked_list(add_new->var_name);
		}
		else{
			if(po->var_type->u.function->isDef==1){
				//Error type 4, multi define
				error = true;
				printf("Error type 4 at Line %d: Redefined function \"%s\".\n"
				,root->childp->right->lineno,root->childp->right->data.strd);
				++tempSemErrNum;
			}
			if(typeEqual(func->fun_type,po->var_type->u.function->fun_type)==false
			||structEqual(func->para,po->var_type->u.function->para)==false){
				//Error type 19, conflict declare and define
				printf("Error type 19 at Line %d: Inconsistent declaration of function \"%s\".\n"
				,root->childp->right->lineno,func->name);
				++tempSemErrNum;
			}
		}
		semErrNum+=tempSemErrNum;
		CompSt(root->childp->right->right,fun_type);
	}
	// Specifier FunDec SEMI
	else if(cnEq(3)&&strcmp(firc(),"Specifier")==0&&strcmp(secc(),"FunDec")==0
	&&strcmp(thic(),"SEMI")==0){// elective
		// printf("ExtDef branch4\n");
		Type fun_type=Specifier(root->childp);
		Function func=FunDec(root->childp->right,fun_type,0);
		// Begin: need SYMTAB here and check FUNCTION errors
		// done in FunDec function
		struct item* add_new = create_new();
		add_new -> next = NULL;
		add_new -> var_type -> kind = FUNCTION;
		add_new -> var_type -> u.function = func;
		strcpy(add_new -> var_name,func->name);
		// test before add item
		struct item* po =find_item(add_new -> var_name, add_new -> var_type -> kind );
		if(po==NULL){
			// printf("add_item:ID:%s----type:%d\n",add_new->var_name,add_new->var_type->kind);
			add_item(add_new);
			add_to_linked_list(add_new->var_name,root->childp->right->lineno);
			// printf("succ added\n");
		}
		else if(typeEqual(func->fun_type,po->var_type->u.function->fun_type)==false
			||structEqual(func->para,po->var_type->u.function->para)==false){
			//Error type 19: conflicting declares + declare and define
			printf("Error type 19 at Line %d: Inconsistent declaration of function \"%s\".\n"
				,root->childp->right->lineno,func->name);
			++semErrNum;
		}
		// printf("if succ judged.\n");
		// End
	}
	else{
		//printf("root->childnum=%d\n",root->childnum);
		printErr("ExtDef");
	}
	// printf("return?\n");
	return;
}

void ExtDecList(treeNode* root, Type var_type){
	// printf("ExtDecList\n");
	// VarDec
	if(cnEq(1)&&strcmp(firc(),"VarDec")==0){
		// printf("ExtDecList branch1\n");
		FieldList p = VarDec(root->childp,var_type,0);
		while ( p!=NULL ){
			struct item * a =(struct item*)malloc(sizeof(struct item));
			a->var_type = p->type;
			a->var_name = p->name;
			p = p->tail;
			add_item(a);
		}
	}
	// VarDec COMMA ExtDecList
	else if(cnEq(3)&&strcmp(firc(),"VarDec")==0&&strcmp(secc(),"COMMA")==0
	&&strcmp(thic(),"ExtDecList")==0){
		// printf("ExtDecList branch2\n");
		FieldList p = VarDec(root->childp,var_type,0);
		while ( p!=NULL ){
			struct item * a =(struct item*)malloc(sizeof(struct item));
			a->var_type = p->type;
			a->var_name = p->name;
			p = p->tail;
			add_item(a);
		}
		ExtDecList(root->childp->right->right,var_type);
	}
	else{
		printErr("ExtDecList");
	}
	return;
}

// A.1.3 Specifiers
Type Specifier(treeNode *root){
	// printf("Specifier\n");
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
		//printf("Specifier branch2\n");
		add_type = StructSpecifier(p->childp);
	}
	else{
		printErr("Specifier");
	}
}
// StructSpecifier
Type StructSpecifier(treeNode *root){
	// printf("StructSpecifier\n");
	treeNode *p=root;
	Type add_type = (Type)malloc(sizeof(struct Type_));// return
	
	/* StructSpecifier -> STRUCT OptTag LC DefList RC | STRUCT Tag */
	if(strcmp(p->childp->name,"STRUCT")==0){
		if(p->childnum==5){//define a struct
			FieldList add_struct = (FieldList)malloc(sizeof(struct FieldList_));
			add_struct->name = (char*)malloc(sizeof(char)*32);
			add_struct->type = (Type)malloc(sizeof(struct Type_));
			FieldList head = add_struct;
			// add_type->u.structure = add_struct   point to the head (for example struct a{})
			add_type->kind = STRUCTURE;
			/* OptTag -> ID |  */
			treeNode *OptTag = p->childp->right;//deal with the name of struct
			if( OptTag == NULL )
				add_struct -> name = "";
			else
				strcpy(add_struct -> name,OptTag->childp->data.strd);
			//printf("ID:%s--------------------\n",add_struct -> name);
			//printf("get here?\n");
			if(find_item(add_struct -> name,0)!=NULL)
			{
				// Error type 16: already exist
				printf("Error type 16 at Line %d: Duplicated name \"%s\".\n"
					,root->childp->right->lineno,root->childp->right->childp->data.strd);
				++semErrNum;
			}
			add_struct ->type-> kind = STRUCTURE;
			//next deal with add_struct->tail point to all var of the struct
			/* DefList -> Def DefList | */
			treeNode* DefListp = p->childp->right->right->right;
			FieldList p = DefList(DefListp,1);
			FieldList h = p;
			// printf("A struct\n");
			//printf("fieldName:------------------------%s\n",h->name);
			// while(h!=NULL){
			// 	// printf("fieldName:--------------------%s\n",h->name);
			// 	h = h->tail;
			// }
			add_struct->type-> u.structure = p;
			add_type->u.structure = add_struct;
			struct item* a = create_new();
			a->next = NULL;
			a->var_type = add_type;
			//printf("kind:%d-----------------------\n",add_type->kind);
			a->var_name = add_struct -> name;
			// printf("add_item:ID:%s----type:%d\n",a->var_name,a->var_type->kind);
			add_item(a);
			return add_type;
		}
		else if(p->childnum==2){/* declaration */
			struct item* q = find_item(p->childp->right->childp->data.strd,STRUCTURE);
			if(q==NULL){
				return NULL;
			}
			else{
				add_type = q->var_type;
				return add_type;
			}
		}
		else{
			printErr("StructSpecifier");		
		}
	}
	else{
		printf("StructSpecifier");	
	}
}


// A.1.4 Declarators
// VarDec -> ID | VarDec LB INT RB
FieldList VarDec(treeNode* root,Type var_type,int funRelated){// Inherited Attribute
	// printf("VarDec\n");
	if(var_type==NULL) return NULL;
	treeNode *p=root;
	int i=0;
	/* VarDec -> ID | VarDec LB INT RB */
	while(strcmp(p->childp->name,"ID")!=0){
        p=p->childp;
        i++;
    }

	FieldList add_var = (FieldList)malloc(sizeof(struct FieldList_));
	//printf("p->childp->data.strd=%s\n",p->childp->data.strd);
	add_var->name = p->childp->data.strd;
	// printf("add_var->name=%s\n",add_var->name);
	struct item* p_ = find_item(add_var->name, 0);//0 signify var or structure
	if(p_!=NULL&&funRelated==0){
		// there is this var or structure in table
		printf("Error type 3 at Line %d: Redefined variable \"%s\".\n"
			,root->childp->lineno,add_var->name);
		++semErrNum;
	}
	add_var->type = (Type)malloc(sizeof(struct Type_));
	/* root->childp->name == ID      ->     VarDec -> ID*/
	if(i==0){
        add_var->type = var_type;
        return add_var;
    }
	else if(i>=1){
	/* i-dimension array */
		add_var->type = MultiArray(root,i,var_type);
		// printf("KIND------------------------------%d,%d\n",add_var->type->kind,add_var->type->u.array.elem->kind);
		return add_var;
	}
	else{
		printErr("VarDec");
	}
}

Type MultiArray(treeNode *root,int i,Type b){
	// printf("MultiArray\n");
	treeNode *tp = root;
	Type p = NULL;
	Type q = NULL;
	Type Array = (Type)malloc(sizeof(struct Type_));
	p = Array;
	int j=0;
	for(;j<i;j++){
		p->kind=ARRAY;
		p->u.array.size = tp->childp->right->right->data.intd;
		p->u.array.elem = (Type)malloc(sizeof(struct Type_));
		q = p;
		p = p->u.array.elem;
		tp = tp->childp;
	}
	q->u.array.elem = b;
	return Array;
}

void add_funpara(FieldList head){
	FieldList p = head;
	while(p!=NULL){
		struct item* a = (struct item *)malloc(sizeof(struct item));
		a->var_type = p->type;
		a->var_name = p->name;
		//printf("%s-----------------------------\n",p->name);
		// printf("func para add_item:ID:%s----type:%d\n",a->var_name,a->var_type->kind);
		add_item(a);
		p = p->tail;
	}
	//printf("add_funpara-----------------\n");
}

// FunDec -> ID LP VarList RP | ID LP RP
Function FunDec(treeNode* root, Type fun_type, int isDef){
	// printf("FunDec\n");
	Function func= (Function)malloc(sizeof(struct Function_));
	//PrintDFS(root->childp,0);
	if(func->name == NULL){
		func->name = (char*)malloc(sizeof(char)*32);
	}
	strcpy(func->name,root->childp->data.strd);
	// printf("%s\n",func->name);
	func->isDef=isDef;
	func->para=NULL;
	func->fun_type=fun_type;
	// ID RP VarList RP
	if(cnEq(4)&&strcmp(firc(),"ID")==0&&strcmp(secc(),"LP")==0
	&&strcmp(thic(),"VarList")==0&&strcmp(fouc(),"RP")==0){
		func->para=VarList(root->childp->right->right,isDef);
		//printf("func->para\n");
		add_funpara(func->para);
		return func;
	}
	else if(cnEq(3)&&strcmp(firc(),"ID")==0&&strcmp(secc(),"LP")==0
	&&strcmp(thic(),"RP")==0){
		return func;
		// func->para=NULL;
		// struct item* add_new = create_new();
		// add_new -> next = NULL;
		// add_new -> var_type -> kind = FUNCTION;
		// add_new -> var_type -> u.function = func;
		
		// strcpy(add_new -> var_name,func->name);
		// add_item(add_new);
		// // to add func into symbol table
	}
	else{
		printErr("FunDec");
	}
	return func;
}

// VarList -> ParamDec COMMA VarList | ParamDec 		+ ParamDec
FieldList VarList(treeNode* root, int isDef){
	// printf("VarList\n");
	FieldList fieldl=NULL;
	FieldList ppp = NULL;
	//to implement
	treeNode* VarList = root;
	while( VarList->childnum == 3 ){
		/* each step deal with one ParamDec */
		treeNode* Param = VarList-> childp;
		treeNode * specifierp = Param->childp;
		treeNode * VarDecp = Param->childp->right;
		/* ParamDec -> Specifier VarDec */
		FieldList p = VarDec(VarDecp,Specifier(specifierp),isDef);
		if(fieldl==NULL){
			fieldl = p;
			ppp = p;
		}
		else{
			ppp->tail = p;
			ppp = ppp->tail;
		}
		VarList = VarList->childp->right->right;
	}
	if(VarList->childnum == 1)
	{
		/* each step deal with one ParamDec */
		treeNode* Param = VarList-> childp;
		treeNode * specifierp = Param->childp;
		treeNode * VarDecp = Param->childp->right;
		/* ParamDec -> Specifier VarDec */
		FieldList p = VarDec(VarDecp,Specifier(specifierp),isDef);
		if(fieldl==NULL){
			fieldl = p;
			ppp = p;
		}
		else{
			ppp->tail = p;
			ppp = ppp->tail;
		}
	}
	ppp->tail=NULL;
	return fieldl;
}

// Statements
void CompSt(treeNode* root, Type func_type){
	// printf("CompSt\n");
	//printf("%s %s %s %s\n",firc(),secc(),thic(),fouc());
	//LC DefList StmtList RC
	if(cnEq(4)&&strcmp(firc(),"LC")==0&&(strcmp(secc(),"DefList")==0||strcmp(secc(),"EPSILON")==0)
		&&(strcmp(thic(),"StmtList")==0||strcmp(thic(),"EPSILON")==0)
		&&strcmp(fouc(),"RC")==0){
		// printf("CompSt branch1\n");
		DefList(root->childp->right,0);//0 means it isn't a struct
		// printf("flag3\n");
		StmtList(root->childp->right->right, func_type);
	}
	else{
		printErr("CompSt");
	}
	return;
}

void StmtList(treeNode* root, Type func_type){
	// printf("StmtList\n");
	// Stmt StmtList
	if(cnEq(2)&&strcmp(firc(),"Stmt")==0
		&&(strcmp(secc(),"StmtList")==0||strcmp(secc(),"EPSILON")==0)){
		// printf("StmtList branch1\n");
		Stmt(root->childp, func_type);
		StmtList(root->childp->right, func_type);
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

void Stmt(treeNode* root, Type func_type){
	// printf("Stmt\n");
	// Exp SEMI
	if(cnEq(2)&&strcmp(firc(),"Exp")==0&&strcmp(secc(),"SEMI")==0){
		// printf("Stmt branch1\n");
		Exp(root->childp);
	}
	// CompSt
	else if(cnEq(1)&&strcmp(firc(),"CompSt")==0){
		// printf("Stmt branch2\n");
		CompSt(root->childp,func_type);
	}
	// RETURN Exp SEMI
	else if(cnEq(3)&&strcmp(firc(),"RETURN")==0&&strcmp(secc(),"Exp")==0
		&&strcmp(thic(),"SEMI")==0){
		// printf("Stmt branch3\n");
		Type ret_type=Exp(root->childp->right);
		// Begin: need SYMTAB here and check RETURN errors
		if(typeEqual(ret_type,func_type)==1)
		{
			// nothing error
		}
		else{
			// NEED Error Type 8
			printf("Error type 8 at Line %d: return type is not matched.\n", root->childp->lineno);
			++semErrNum;
		}
		// End	
	}
	// IF LP Exp RP Stmt
	else if(cnEq(5)&&strcmp(firc(),"IF")==0&&strcmp(secc(),"LP")==0
		&&strcmp(thic(),"Exp")==0&&strcmp(fouc(),"RP")==0
		&&strcmp(fifc(),"Stmt")==0){
		// printf("Stmt branch4\n");
		Exp(root->childp->right->right);
		Stmt(root->childp->right->right->right->right, func_type);
	}
	// IF LP Exp RP Stmt ELSE Stmt
	else if(cnEq(7)&&strcmp(firc(),"IF")==0&&strcmp(secc(),"LP")==0
		&&strcmp(thic(),"Exp")==0&&strcmp(fouc(),"RP")==0
		&&strcmp(fifc(),"Stmt")==0&&strcmp(sixc(),"ELSE")==0
		&&strcmp(sevc(),"Stmt")==0){
		// printf("Stmt branch5\n");
		Exp(root->childp->right->right);
		Stmt(root->childp->right->right->right->right, func_type);
		Stmt(root->childp->right->right->right->right->right->right, func_type);
	}
	// WHILE LP Exp RP Stmt
	else if(cnEq(5)&&strcmp(firc(),"WHILE")==0&&strcmp(secc(),"LP")==0
		&&strcmp(thic(),"Exp")==0&&strcmp(fouc(),"RP")==0
		&&strcmp(fifc(),"Stmt")==0){
		// printf("Stmt branch6\n");
		Exp(root->childp->right->right);
		Stmt(root->childp->right->right->right->right, func_type);
	}
	else{
		printErr("Stmt");
	}
	return;
}

// Local Definitions
/* add to the symbol table when defining */
FieldList DefList(treeNode* root, bool isStruct){
	// printf("DefList\n");
	FieldList fp=NULL;
	FieldList ppp=NULL;
	FieldList head=NULL;
	treeNode* DefList = root;
	int cnt = 0;
	while( DefList->childp != NULL ){
		treeNode* Def = DefList-> childp;		
		treeNode * DecList = Def->childp->right;
		treeNode * specifierp = Def->childp;
		Type p = Specifier(specifierp);
		if(p==NULL)
		{
			printf("Error type 17 at Line %d: Undefined structure.\n"
				,DecList->lineno);
			++semErrNum; 
		}
		/* DecList -> Dec | Dec COMMA DecList */
		while( DecList != NULL ){
			struct item* add_new = create_new();
			add_new -> next = NULL;			
			treeNode * Dec = DecList->childp;
			/* deal with Dec -> VarDec | VarDec ASSIGNOP Exp */
			if(Dec->childnum==3){
				if(isStruct==true){
					//Error type 15_2
					treeNode *wrong=Dec->childp->right->right;
					printf("Error type 15 at Line %d: Initialize field \"%s\" in struct.\n"
						,wrong->lineno, wrong->data.strd);
					++semErrNum;
				}
				Type r = Exp(Dec->childp->right->right);
				if(typeEqual(p,r)==false){
					// Error type 5
					printf("Error type 5 at Line %d: Type mismatched for assignment.\n"
						,Dec->childp->right->lineno);
					++semErrNum;
				}
			}
			else if(Dec->childnum==1){
				// do nothing
			}
			else{
				assert(0);
			}
			fp = VarDec(Dec->childp,p,0);
			if(fp==NULL) return NULL;
			if( isStruct && inFieldList(head,fp->name) != NULL){
				printf("Error type 15 at Line %d: Redefined fields.\n"
						,Dec->childp->lineno);
				++semErrNum;
			}
			if(head==NULL){
				head = fp;
				ppp = fp;
			}
			else{
				ppp->tail = fp;
				ppp = ppp->tail;
			}
			// printf("BACK\n");
			add_new->var_type = fp->type;
			// printf("flag4\n");
			add_new->var_name=fp->name;
			// printf("add_item:ID:%s----type:%d\n",add_new->var_name,add_new->var_type->kind);
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
			fp = fp->tail;
		}
		DefList = DefList->childp->right;
	}
	return head; 
}



// Experssions
Type Exp(treeNode* root){
	// printf("Exp\n");
	Type type;
	int tempSemErrNum=0;
	// Exp <sth.> Exp
	if(cnEq(3)&&strcmp(firc(),"Exp")==0&&strcmp(thic(),"Exp")==0){
		// Exp ASSIGNOP Exp
		if(strcmp(secc(),"ASSIGNOP")==0){
			Type ltype=Exp(root->childp);
			if(ltype!=NULL&&ltype->value==R_VALUE){
				// printf("%d\n",ltype->value);
				printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n"
					, root->childp->lineno);
				++tempSemErrNum;
			}
			Type rtype=Exp(root->childp->right->right);
			if(ltype==NULL||rtype==NULL){
				return NULL;
			}
			if(!typeEqual(ltype,rtype)){
				printf("Error type 5 at Line %d: Type mismatched for assignment.\n"
					, root->childp->lineno);
				++tempSemErrNum;	
			}
			if(!tempSemErrNum){
				// printf("Exp ASSIGNOP Exp\n");
				ltype->value=LR_VALUE;
				return ltype;
			}
			else{
				semErrNum+=tempSemErrNum;
				return NULL;
			}
		}
		else if(strcmp(secc(),"AND")==0||strcmp(secc(),"OR")==0
			||strcmp(secc(),"RELOP")==0){
			Type ltype=Exp(root->childp);
			Type rtype=Exp(root->childp->right->right);
			if(ltype==NULL||rtype==NULL){
				return NULL;
			}
			if(!typeEqual(ltype,rtype)||ltype->kind!=BASIC
				||(ltype->kind==BASIC&&ltype->u.basic!=INT)){
				printf("Error type 7 at Line %d: Type mismatched for operation.\n",root->childp->lineno);
				++semErrNum;
				return NULL;
			}
			ltype->value=R_VALUE;
			return ltype;
		}
		else if(strcmp(secc(),"PLUS")==0||strcmp(secc(),"MINUS")==0
			||strcmp(secc(),"STAR")==0||strcmp(secc(),"DIV")==0){
			Type ltype=Exp(root->childp);
			Type rtype=Exp(root->childp->right->right);
			if(ltype==NULL||rtype==NULL){
				return NULL;
			}
			if(!typeEqual(ltype,rtype)||ltype->kind!=BASIC){
				printf("Error type 7 at Line %d: Type mismatched for operation.\n",root->childp->lineno);
				++semErrNum;
				return NULL;
			}
			ltype->value=R_VALUE;
			return ltype;
		}
		else{
			printErr("Exp OP Exp");
		}
	}
	// LP Exp RP
	else if(cnEq(3)&&strcmp(firc(),"LP")==0&&strcmp(secc(),"Exp")==0
		&&strcmp(thic(),"RP")==0){
		// printf("in here\n");
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
				++semErrNum;
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

		// ID undefine
		char * ID = root->childp->data.strd;
		// printf("func:%s\n",ID);
		struct item* p = find_item(ID,FUNCTION);
		struct item* q = find_item(ID,0);
		if( p == NULL ){
			// two is possible: ID is a var, no ID
			if(q==NULL){
				printf("Error type 2 at Line %d: Undefined function \"%s\".\n"
				,root->childp->lineno,root->childp->data.strd);
				++semErrNum;
				return NULL;
			}
			else{
				printf("Error type 11 at Line %d: \"%s\" is not a function.\n"
					, root->childp->lineno,root->childp->data.strd);
				++semErrNum;
				return NULL;
			}
		}
		else{
			if(p->var_type->u.function->isDef==0){
				//Error type 18: Declared but not defined
				error = true;
				printf("Error type 18 at Line %d: Undefined function \"%s\".\n"
					,root->childp->lineno,root->childp->data.strd);
				++tempSemErrNum;
			}
			if(tempSemErrNum!=0){
				semErrNum+=tempSemErrNum;
				return NULL;
			}
			else if(Args(root->childp->right->right, p->var_type->u.function->para) == 1 ){
			// nothing error
				type = p->var_type->u.function->fun_type;
				type -> value = R_VALUE;
				return type;
			}
			else{
				//printErr("Exp");
			}
		}
		// printf("----------------------------%s\n",ID);
		// End
	}
	// ID LP RP
	else if(cnEq(3)&&strcmp(firc(),"ID")==0&&strcmp(secc(),"LP")==0
		&&strcmp(thic(),"RP")==0){
		// TO IMPLEMENT: ID CHECK ERROR TYPE 1, FUNCTION CHECK ERROR
		// THIS Exp IS R_VALUE
		// Begin:
		char * ID = root->childp->data.strd;
		struct item* p = find_item(ID,FUNCTION);
		if( p == NULL ){
			// two is possible: ID is a var, no ID
			struct item* q = find_item(ID,0);
			if (q == NULL ){
				printf("Error type 2 at Line %d: Undefined function \"%s\".\n"
				,root->childp->lineno,root->childp->data.strd);
				++semErrNum;
				return NULL;
			}
			else{
				// Error type 11
				printf("Error type 11 at Line %d: \"%s\" is not a function.\n"
					, root->childp->lineno,root->childp->data.strd);
				++semErrNum;
				return NULL;
			}
		}
		if(p->var_type->u.function->isDef==0){
			//Error type 18: Declared but not defined
			error = true;
			printf("Error type 18 at Line %d: Undefined function \"%s\".\n"
				,root->childp->lineno,root->childp->data.strd);
			++tempSemErrNum;
		}
		if(tempSemErrNum!=0){
			semErrNum+=tempSemErrNum;
			return NULL;
		}
		else if( Args(NULL, p->var_type->u.function->para) == 1 ){
			// nothing error
			type = p->var_type->u.function->fun_type;
			type -> value = R_VALUE;
			return type;
		}
		else{
			printErr("Exp");
		}
		// End
	}
	// Exp LB Exp RB
	else if(cnEq(4)&&strcmp(firc(),"Exp")==0&&strcmp(secc(),"LB")==0
		&&strcmp(thic(),"Exp")==0&&strcmp(fouc(),"RB")==0){
		Type arr_type=Exp(root->childp);
		Type arr_opr=Exp(root->childp->right->right);
		if(arr_type==NULL||arr_opr==NULL){
			return NULL;
		}
		// printf("arr_opr->kind=%d\n",arr_opr->kind);
		if(arr_type->kind!=ARRAY){
			//Error type 10: not an array
			printf("Error type 10 at Line %d: \"%s\" is not an array.\n"
				, root->childp->lineno, root->childp->childp->data.strd);
			++tempSemErrNum;
		}
		// printf("--%d\n",arr_opr->kind);
		if(arr_opr->kind!=BASIC||(arr_opr->kind==BASIC&&arr_opr->u.basic!=INT)){
			//Error type 12: not an integer
			printf("Error type 12 at Line %d: \"%s\" is not an integer.\n"
				, root->childp->right->right->lineno , root->childp->right->right->childp->data.strd);
			++tempSemErrNum;
		}
		if(tempSemErrNum!=0){
			semErrNum+=tempSemErrNum;
			return NULL;
		}
		else{
			type=arr_type->u.array.elem;
			// printf("ARRAY___________kind:%d\n",type->kind);
			type->value = LR_VALUE;
			return type;
		}
	}
	// Exp DOT ID
	else if(cnEq(3)&&strcmp(firc(),"Exp")==0&&strcmp(secc(),"DOT")==0
		&&strcmp(thic(),"ID")==0){
		// TO IMPLEMENT: Exp CHECK ERROR, ID CHECK ERROR TYPE 1, FUNCTION CHECK ERROR
		// THIS Exp IS ______? LR_VALUE
		// Begin:
		Type l = Exp(root->childp);
		if(l==NULL)
			return NULL;
		else if(l->kind!=STRUCTURE){
			// Error type 13: not a structure
			printf("Error type 13 at Line %d: Illegal use of \"%s\".\n"
				, root->childp->lineno, root->childp->data.strd);
			++semErrNum;
			return NULL;
		}
		else{
			// for a struct
			char * ID = root->childp->right->right->data.strd;
			// printf("ID:-----------------%s\n",ID);
			Type type = inFieldList(l->u.structure->type->u.structure, ID);
			if(type==NULL)
			{
				// ID not define in the structure
				// NEED Error type 14
				printf("Error type 14 at Line %d: Visit undefined field in struct.\n", root->childp->lineno);
				++semErrNum;
				return NULL;
			}
			else{
				type -> value = LR_VALUE;
				return type; 
			}
		}
		// End
	}
	// <sth.>
	else if(cnEq(1)){
		// ID
		if(strcmp(firc(),"ID")==0){
			// TO IMPLEMENT: ID CHECK ERROR TYPE 1
			// THIS IS LR_VALUE
			// Begin:
			char * ID = root->childp->data.strd;
			struct item* p = find_item(ID,0);
			// printf("ID----------->%s\n",ID);
			if( p == NULL ){
				// two is possible: ID is a func or not define
				printf("Error type 1 at Line %d: Undefined variable \"%s\".\n"
					, root->childp->lineno, root->childp->data.strd);
				++semErrNum;
				return NULL;
			}
			else{
				// nothing error
				type = p->var_type;
				type -> value = LR_VALUE;
				// printf("%s:value-------------%d\n",ID,type -> value);
				
				return type;
			}					
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
		// printf("root->childnum=%d\n",root->childnum);
		// printf("firc=%s\nsecc=%s\nthic=%s\n",firc(),secc(),thic());
		printErr("Exp");
	}
	type=NULL;
	return type;
}
Type inFieldList(FieldList f, char* ID){
	FieldList p = f;
	// printf("ID:%s\n",ID);
	//printf("fieldName:------------------------%s\n",p->name);
	while(p!=NULL){
		// printf("fieldName:--------------------%s\n",p->name);
		if(strcmp(p->name,ID)==0){
			return p->type;
		}
		p = p->tail;
	}
	return NULL;
}
/*
 * Args Func can compare whether cur_para_type=symtable.func.para_type
 * Return true means equal, otherwise unequal
 */
bool Args(treeNode* root, FieldList para){
	// printf("Args\n");
	if(para==NULL && root==NULL)
		return true;
	if(root==NULL){
		printf("Error type 9 at Line %d: Function is not applicable for arguments.\n"
			,root->childp->lineno);
		++semErrNum;
		return false;
	}
	if(para==NULL){
		printf("Error type 9 at Line %d: Function is not applicable for arguments.\n"
			,root->childp->lineno);
		++semErrNum;
		return false;
	}
	// printf("kind:%d\n",para->type->kind);
	Type exp_type = Exp(root->childp);
	if(!typeEqual(exp_type, para->type)){
		// TO IMPLEMENT ERROR TYPE 9
		printf("Error type 9 at Line %d: Function is not applicable for arguments.\n"
			,root->childp->lineno);
		++semErrNum;
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
