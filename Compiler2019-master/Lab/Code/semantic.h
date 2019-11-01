#include <stdlib.h>
#include "syntaxTree.h"
#include <assert.h>
#include<stdbool.h>

#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_

#define TABLE_SIZE 0x3fff
#endif

#define INT 0
#define FLOAT 1

// just define some little functions
#define cnEq(num)\
	(root->childnum==num)
#define printErr(str)\
	printf("Wrong in %s\n",str);\
	assert(0);
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
#define sixc()\
	root->childp->right->right->right->right->right->name
#define sevc()\
	root->childp->right->right->right->right->right->right->name
#define MACRO_RETURN(INT_FLOAT_TYPE)\
	Type type = (Type)malloc(sizeof(struct Type_));\
	type->kind = BASIC;\
	type->u.basic = INT_FLOAT_TYPE;\
	type->value = R_VALUE;\
	return type;

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef struct Function_* Function;

struct Type_
{
	enum { BASIC, ARRAY, STRUCTURE, FUNCTION} kind;
	union{
		//Basic type
		int basic;
		//array info contains elem type and array size
		struct { Type elem; int size;} array;
		//for a struct info		
		FieldList structure;
		
		Function function;
	}u;
	enum { L_VALUE, R_VALUE, LR_VALUE} value;// used for exp only
};

struct FieldList_
{
	char *name;
	Type type;
	FieldList tail;
};

struct Function_{
	char *name;
	Type fun_type;// return
	int isDef;//to allign and to be simple
	FieldList para;
	int para_num;
};

struct item{
	struct item* next; // deal with collision
	Type var_type;
	char* var_name;
	// some data
};
/* 
for a function item
var_type->kind = FUNCTION
var_type->u.function
var_name
*/
/* hash table */
extern struct item* table[TABLE_SIZE];

/********************************************
 *hash table api, implemented in hashTable.c
 ********************************************/
unsigned int hash_pjw(char* name);
struct item * find_item(char *name, int t);
void add_item(struct item* p);
struct item* create_new();
void print_table();
struct item* create_new();

/********************************************
 *equal judge api, implemented in equalJudge.c
 ********************************************/
bool typeEqual(Type ltype, Type rtype);
bool structEqual(FieldList lstruct, FieldList rstruct);

/*****************************************************
 *semantic non-terminal api, implemented in semantic.c
 *****************************************************/
// High Level Definitions
void Program(treeNode* root);
void ExtDefList(treeNode* root);
void ExtDef(treeNode* root);
void ExtDecList(treeNode* root, Type type);

// Specifiers
Type Specifier(treeNode* root);
Type StructSpecifier(treeNode *root);

//Declarators
FieldList VarDec(treeNode* root, Type var_type);
Function FunDec(treeNode* root, Type fun_type,int isDef);
FieldList VarList(treeNode* root);

// Statements
void CompSt(treeNode* root, Type func_type);
void StmtList(treeNode* root, Type func_type);
void Stmt(treeNode* root, Type func_type);

// Local Definitions
FieldList DefList(treeNode* root);

// Experssions
Type Exp(treeNode* root);
bool Args(treeNode* root, FieldList para);


//assistant function
Type MultiArray(treeNode *root, int i, Type b);
Type inFieldList(FieldList f, char* ID);




