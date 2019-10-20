#include "semantic.h"

struct item* table[tablesize];

unsigned int hash_pjw(char* name){
	unsigned int val = 0, i;
	for(; *name; ++name)
	{
		val = (val<<2) + *name;
		if (i=val&~tablesize) val = (val^(i>>12))&tablesize;
	}
}

struct item * find_item(char *name)
{
	unsigned int index = hash_pjw(name);
	if(table[index] == NULL)
		return NULL;
	else
	{
		struct item* p = table[index];
		while(p != NULL)
		{
			if(strcmp(p->var_name,name)==0)
				break;				
			p = p->next;
		}
		return p;
	}
}

void add_item(struct item* p){
	int index = hash_pjw(p->var_name);
	if(table[index] == NULL)
		table[index]=p;
	else
	{
		//insert to the head
		struct item *head = table[index];
		p->next = head;
		table[index]= p;
	}
}




