#include "semantic.h"

/* hash table */
struct item* table[TABLE_SIZE]={NULL};

unsigned int hash_pjw(char* name){
	unsigned int val = 0, i;
	for(; *name; ++name)
	{
		val = (val<<2) + *name;
		if (i=val&~TABLE_SIZE) val = (val^(i>>12))&TABLE_SIZE;
	}
	return val;
}

// malloc a new item
struct item* create_new(){
	struct item* add_new = (struct item*)malloc(sizeof(struct item));
	add_new -> var_type = (Type)malloc(sizeof(struct Type_));
	add_new -> var_name = (char*)malloc(sizeof(char)*32);
	return add_new;
}

struct item * find_item(char *name, int t){
	unsigned int index = hash_pjw(name);
	if(table[index] == NULL)
		return NULL;
	else
	{
		struct item* p = table[index];
		while(p != NULL)
		{
			if(t == FUNCTION){
				if(p->var_type->kind == FUNCTION && strcmp(p->var_name,name)==0)
					break;
			}
			if(t != FUNCTION){
				if(p->var_type->kind != FUNCTION && strcmp(p->var_name,name)==0)
					break;
			}
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

//debug
void print_table(){
	for(int i=0;i<TABLE_SIZE;i++)
		if(table[i]!=NULL){
			struct item* p = table[i];
			while(p!=NULL){
				printf("name:%s\n",p->var_name);
			}
		}
}
