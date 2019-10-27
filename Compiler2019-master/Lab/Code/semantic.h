#include <stdlib.h>
#include "syntaxTree.h"

#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_

#define TABLE_SIZE 0x3fff
#endif

#define INT 0
#define FLOAT 1

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;

struct Type_
{
	enum { BASIC, ARRAY, STRUCTURE} kind;
	union{
		//Basic type
		int basic;
		//array info contains elem type and array size
		struct { Type elem; int size;} array;
		//for a struct info		
		FieldList structure;		
	} u;
};

struct FieldList_
{
	char* name;
	Type type;
	FieldList tail;
};


struct item{
	struct item* next; // deal with collision
	Type var_type;
	char* var_name;
	// some data
};

struct item* table[TABLE_SIZE]={NULL};

// all functions
unsigned int hash_pjw(char* name);
struct item * find_item(char *name);
void add_item(struct item* p);
void print_table();

Type Specifier(treeNode* root);
Type MultiArray(treeNode *root, int i, Type b);
FieldList VarDec(treeNode* root, Type var_type);
Type StructSpecifier(treeNode *root);
void DefList(treeNode* root);





