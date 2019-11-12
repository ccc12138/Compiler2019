#include "translate.h"

/* High level Definitions */
void translate_Program(treeNode* root){
	switch(root->branch){
		case 1:
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
			//translate_ExtDef(root->childp);
			//translate_ExtDefList(root->childp->right);
			break;
		case 2:
			break;
		default:
			assert(0);
	}
	return;
}

void translate_ExtDef(treeNode* root){
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
void translate_Exp(treeNode* root){
	return;
}

void translate_Args(treeNode* root){
	return;
}