#include "translate.h"

// DEBUG macro is defined in syntaxTree.h

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
void translate_Exp(treeNode* root){
	switch(root->branch){
		case 1:

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
			break;
		case 11:
			break;
		case 12:
			break;
		default:
			assert(0);

	}
	return;
}

void translate_Args(treeNode* root){
	return;
}