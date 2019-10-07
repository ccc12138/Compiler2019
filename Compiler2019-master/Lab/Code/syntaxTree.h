#include <stdio.h>
#include <stdlib.h>//malloc
#include <stdarg.h>
#include <string.h>

typedef struct treeNode{
	char* name;
	int childnum;					//amount of children
	int lineno;
	union {
		int intd;
		float floatd;
		char strd[32];
	}data;							//数据
	struct treeNode* right;
	struct treeNode* childp;		//第一个子节点
}treeNode;
//multitreeNode $1,$2... need va_list

treeNode* InitNode(char*, int);
void InsertNode(treeNode *, int, ...);
void PrintDFS(treeNode *, int);
