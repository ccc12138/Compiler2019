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
	Treenode* right;
	Treenode* childp;		//第一个子节点
	int childnum=0;			//amount of children
};
//multitreenode $1,$2... need va_list