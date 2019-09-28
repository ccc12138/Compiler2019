#include <stdio.h>
#include <stdlib.h>//malloc
#include <stdarg.h>
#include <string.h>

struct Treenode{
	char* name;//print
	union {
		int intd;
		float floatd;
		char * strd;
	}data;				//数据
	struct Treenode* right;
	struct Treenode* childp;		//第一个子节点
	int childnum;			//amount of children
};
//multitreenode $1,$2... need va_list