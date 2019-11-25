#ifndef _TRANSLATE_H
#define _TRANSLATE_H

#include "syntaxTree.h"
#include "interCode.h"
#include "semantic.h"

#define TABLE_SIZE 0x3fff
#define MAX_LEN 32
#define cnEq(num)\
	(root->childnum==num)
#define firc()\
	root->childp->name
#define secc()\
	root->childp->right->name
#define thic()\
	root->childp->right->right->name
#define fouc()\
	root->childp->right->right->right->name
#define fifc()\
	root->childp->right->right->right->right->name


extern unsigned varNum;
extern unsigned tempVarNum;
extern unsigned labelNum;
extern struct item* table[TABLE_SIZE];





// some useful functions
Operand look_Up(char *name);
Operand new_Temp();
Operand new_Label();

/* High level Definitions */
void translate_Program(treeNode* root);
void translate_ExtDefList(treeNode* root);
void translate_ExtDef(treeNode* root);
// void translate_ExtDecList(treeNode* root);

/* Specifiers */
void translate_Specifier(treeNode* root);
// void translate_StructSpecifier(treeNode* root);

/* Declarators */
void translate_VarDec(treeNode* root, char* var_name);
void translate_FunDec(treeNode* root);
void translate_VarList(treeNode* root);
void translate_ParamDec(treeNode* root);

/* Statements*/
void translate_CompSt(treeNode* root);
void translate_StmtList(treeNode* root);
void translate_Stmt(treeNode* root);

/* Local Definitions */
void translate_DefList(treeNode* root);
void translate_Def(treeNode* root);
void translate_DecList(treeNode* root);
void translate_Dec(treeNode* root);

/* Expressions */
void translate_Exp(treeNode* root, Operand* place);
void translate_Args(treeNode* root, Operand arg_list[], int *size);

void translate_Cond(treeNode* root, Operand label_true, Operand label_false);
int isArray(char * name);
char* findExpID(treeNode* root);
Operand changeiop(char *name);
void translate_Array(treeNode* root,  Operand* place);


#endif
