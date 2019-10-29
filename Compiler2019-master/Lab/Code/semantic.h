#include <stdlib.h>
#include "syntaxTree.h"
#include <assert.h>

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
};

struct FieldList_
{
	char* name;
	Type type;
	FieldList tail;
};


// Is it correct?
struct Function_{
	char *name;
	Type fun_type;
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

/* hash table */
extern struct item* table[TABLE_SIZE];

/********************************************
 *hash table api, implemented in hashTable.c
 ********************************************/
unsigned int hash_pjw(char* name);
struct item * find_item(char *name, Type item_type);
void add_item(struct item* p);
void print_table();

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
Function FunDec(treeNode* root, Type fun_type);
FieldList VarList(treeNode* root);

// Declarators


// Statements


// Local Definitions
void DefList(treeNode* root);

// Experssions


Type MultiArray(treeNode *root, int i, Type b);





