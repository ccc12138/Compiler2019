#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_

#define tablesize 0x3fff

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;

struct Type_
{
	enum { BASIC, ARRAY, STRUCTTURE} kind;
	union{
		//Basic type
		int basic;
		//array info contains elem type and array size
		stuct { Type elem; int size;} array;
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
	Type_ var_type;
	char* var_name;
};


// all functions
unsigned int hash_pjw(char* name);
struct item * find_item(char *name);
void add_item(struct item* p);





