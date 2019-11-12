#ifndef _TRANSLATE_H
#define _TRANSLATE_H

#include "syntaxTree.h"
#include "interCode.h"

/* High level Definitions */
void translate_Program(treeNode* root);
void translate_ExtDefList(treeNode* root);
void translate_ExtDef(treeNode* root);
void translate_ExtDecList(treeNode* root);

/* Specifiers */
void translate_Specifier(treeNode* root);
void translate_StructSpecifier(treeNode* root);

/* Declarators */
void translate_VarDec(treeNode* root);
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
void translate_Exp(treeNode* root);
void translate_Args(treeNode* root);

#endif