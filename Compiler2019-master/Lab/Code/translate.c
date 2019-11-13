#include "translate.h"

// DEBUG macro is defined in syntaxTree.h

/* some useful functions */
Operand look_Up(char *name, int t){
	// TO IMPLEMENT
	Operand tableOp=(Operand)malloc(sizeof(struct Operand_));
	memset(tableOp,0,sizeof(struct Operand_));
	struct item *tableItem;
	tableItem=find_item(name,t);
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
			break;
		case STRUCTURE:
			break;
		case FUNCTION:
			break;
		default:
			assert(0);
	}
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
			printf("case 1");
#endif // DEBUG
			translate_ExtDefList(root->childp);
			break;
		default:
			assert(0);
	}
	return;
}

void translate_ExtDefList(treeNode* root){
	switch(root->branch){
		case 1:
#ifdef DEBUG
			printf("case 1");
#endif // DEBUG
			translate_ExtDef(root->childp);
			translate_ExtDefList(root->childp->right);
			break;
		case 2:
#ifdef DEBUG
			printf("case 2");
#endif // DEBUG
			break;
		default:
			assert(0);
	}
	return;
}

void translate_ExtDef(treeNode* root){
	// TO IMPLEMENT
	switch(root->branch){
		case 1:
			translate_Specifier(root->childp);
			translate_ExtDecList(root->childp->right);
			break;
		case 2:
			translate_Specifier(root->childp);
			break;
		case 3:
			translate_Specifier(root->childp);
			translate_FunDec(root->childp->right);
			translate_CompSt(root->childp->right->right);
			break;
		case 4:
			translate_Specifier(root->childp);
			translate_FunDec(root->childp->right);
			break;
		default:
			assert(0);
	}
	return;
}

void translate_ExtDecList(treeNode* root){
	return;
}

/* Specifiers */
void translate_Specifier(treeNode* root){
	return;
}

void translate_StructSpecifier(treeNode* root){
	return;
}

/* Declarators */
void translate_VarDec(treeNode* root){
	return;
}

void translate_FunDec(treeNode* root){
	return;
}

void translate_VarList(treeNode* root){
	return;
}

void translate_ParamDec(treeNode* root){
	return;
}

/* Statements*/
void translate_CompSt(treeNode* root){
	return;
}

void translate_StmtList(treeNode* root){
	return;
}

void translate_Stmt(treeNode* root){
	return;
}

/* Local Definitions */
void translate_DefList(treeNode* root){
	return;
}

void translate_Def(treeNode* root){
	return;
}

void translate_DecList(treeNode* root){
	return;
}

void translate_Dec(treeNode* root){
	return;
}

/* Expressions */
void translate_Exp(treeNode* root, Operand place){
	// TO IMPLEMENT
	switch(root->branch){
		case 1://ASSIGNOP
#ifdef DEBUG
			assert(place!=NULL);
#endif
			// left Operand
			Operand leftOp;
			// right Operand
			Operand rightOp=(Operand)malloc(sizeof(struct Operand_));
			memset(rightOp,0,sizeof(struct Operand_));
			rightOp->u.var_no=tempVarNum;
			rightOp->kind=OP_TEMP_VAR;
			++tempVarNum;
			

			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		case 10:
#ifdef DEBUG
			assert(place!=NULL);
#endif
			place->kind=OP_VARIABLE;
			place->u.name=root->childp->data.strd;
			break;
		case 11:
#ifdef DEBUG
			assert(place!=NULL);
#endif
			place->kind=OP_CONSTANT;
			place->u.value=root->childp->data.intd;
			break;
		case 12:
			assert(0);// P63 Assume 1
			break;
		default:
			assert(0);

	}
	return;
}

void translate_Args(treeNode* root){
	return;
}