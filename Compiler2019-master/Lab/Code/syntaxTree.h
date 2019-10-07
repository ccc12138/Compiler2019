#include <stdio.h>
#include <stdlib.h>//malloc
#include <stdarg.h>
#include <string.h>

typedef enum NODE_TYPE{
	TOKENS_INT,
	TOKENS_FLOAT,
	TOKENS_ID,
	TOKENS_SEMI,
	TOKENS_COMMA,
	TOKENS_ASSIGNOP,
	TOKENS_RELOP,
	TOKENS_PLUS,
	TOKENS_MINUS,
	TOKENS_AND,
	TOKENS_OR,
	TOKENS_STAR,
	TOKENS_DIV,
	TOKENS_DOT,
	TOKENS_NOT,
	TOKENS_TYPE,
	TOKENS_LP,
	TOKENS_RP,
	TOKENS_LB,
	TOKENS_RB,
	TOKENS_LC,
	TOKENS_RC,
	TOKENS_STRUCT,
	TOKENS_RETURN,
	TOKENS_IF,
	TOKENS_ELSE,
	TOKENS_WHILE,
	TOKENS_NEWLINE,
	TOKENS_WHITESPACE
}NODE_TYPE;

typedef struct treeNode{
	char* name;
	int childnum;					//amount of children
	int lineno;
	enum NODE_TYPE type;
	union {
		int intd;
		float floatd;
		char strd[32];
	}data;							//数据
	struct treeNode* right;
	struct treeNode* childp;		//第一个子节点
}treeNode;
//multitreeNode $1,$2... need va_list

treeNode* InitNode(char*, NODE_TYPE, int);
void InsertTree(treeNode **, const char *, int, ...);
void PrintDFS(treeNode *, int);
