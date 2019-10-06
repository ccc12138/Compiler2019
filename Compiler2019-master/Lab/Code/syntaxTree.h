#include <stdio.h>
#include <stdlib.h>//malloc
#include <stdarg.h>
#include <string.h>

enum NODE_TYPE{
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
	TOKENS_WHITESPACE,
	//TOKENS_. ? Confused
};

struct Treenode{
	char* name;
	int childnum;					//amount of children
	int lineno;
	enum NODE_TYPE type;
	union {
		int intd;
		float floatd;
		char* strd;
	}data;							//数据
	struct Treenode* right;
	struct Treenode* childp;		//第一个子节点
};
//multitreenode $1,$2... need va_list

void InitNode(char*, int, enum NODE_TYPE);
void Build(struct Treenode **, const char *, int, ...);
void PrintDFS(struct Treenode *, int);
