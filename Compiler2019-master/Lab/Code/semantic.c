#include "semantic.h"

unsigned int hash_pjw(char* name){
	unsigned int val = 0, i;
	for(; *name; ++name)
	{
		val = (val<<2) + *name;
		if (i=val&~TABLE_SIZE) val = (val^(i>>12))&TABLE_SIZE;
	}
	return val;
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

void print_table(){
	for(int i=0;i<TABLE_SIZE;i++)
		if(table[i]!=NULL){
			struct item* p = table[i];
			while(p!=NULL){
				printf("name:%s\n",p->var_name);
			}
		}

}

Type MultiArray(treeNode *root,int i,Type b){
	treeNode *tp = root;
	Type p = NULL;
	Type Array = (Type)malloc(sizeof(struct Type_));
	p = Array;
	int j=0;
	for(;j<i;j++){
		p->kind=ARRAY;
		p->u.array.size = tp->childp->right->right->data.intd;
		p->u.array.elem = (Type)malloc(sizeof(struct Type_));
		p = p->u.array.elem;
		tp = tp->childp;
	}
	p = b;
	return Array;
}

FieldList VarDec(treeNode* root,Type var_type){// Inherited Attribute
	treeNode *p=root;
	int i=0;
	/* VarDec -> ID | VarDEc LB INT RB */
	while(strcmp(p->childp->name,"ID")!=0){
        p=p->childp;
        i++;
    }

	FieldList add_var = (FieldList)malloc(sizeof(struct FieldList_));
	strcpy(add_var->name, p->childp->data.strd); 
	
	/* root->childp->name == ID      ->     VarDec -> ID*/
	if(i==0){
        add_var->type->kind=BASIC;
        return add_var;
    }
	else if(i>=1){
	/* i-dimension array */
		add_var->type = MultiArray(root,i,var_type);
		return add_var;
	}
}


Type StructSpecifier(treeNode *root){
	treeNode *p=root;
	Type add_type = (Type)malloc(sizeof(struct Type_));// return
	/* StructSpecifier -> STRUCT OptTag LC DefList RC | STRUCT Tag */
	if(strcmp(p->childp->name,"STRUCT")==0){
		if(p->childnum==5){
			FieldList add_struct = (FieldList)malloc(sizeof(struct FieldList_));
			// add_type->u.structure = add_struct   point to the head (for example struct a{})
			add_type->kind = STRUCTURE;
			/* OptTag -> ID |  */
			treeNode *OptTag = p->childp->right;//deal with the name of struct
			if( OptTag == NULL )
				add_struct -> name = NULL;
			else
				strcpy(add_struct -> name,OptTag->childp->data.strd);
			add_struct ->type-> kind = STRUCTURE;
			//next deal with add_struct->tail point to all var of the struct
			/* DefList -> Def DefList | */
			treeNode* DefList = p->childp->right->right->right;
			if( DefList->childp == NULL ){
				add_struct->tail=NULL;
			}
			else{
				while( DefList->childp != NULL ){
					treeNode* Def = DefList-> childp;	
					treeNode * DecList = Def->childp->right;
					treeNode * specifierp = Def->childp;
					/* DecList -> Dec | Dec COMMA DecList */
					while( DecList != NULL ){
						FieldList add_struct_new = (FieldList)malloc(sizeof(struct FieldList_));
						if( DecList -> childnum == 1 ){
							treeNode * Dec = DecList->childp;
							/* deal with Dec -> VarDec | VarDec ASSIGNOP Exp */
							// the later one is error type 15
							add_struct_new = VarDec(Dec->childp,Specifier(specifierp));
							DecList = NULL;
						}
						else if( DecList -> childnum == 3 ){
							treeNode * Dec = DecList->childp;
							/* deal with Dec -> VarDec | VarDec ASSIGNOP Exp*/
							add_struct_new = VarDec(Dec->childp,Specifier(specifierp));
							// the later one is error type 15
							DecList = DecList->childp->right->right;
						}
						else{
							printf("error!");
						}
						add_struct->tail = add_struct_new;
						add_struct = add_struct_new;
					}
					DefList = Def->right;
					
				}
			}
			add_type->u.structure = add_struct;
			return add_type;
		}
		else if(p->childnum==2){/* declaration */
			struct item* q = find_item(p->childp->right->childp->data.strd);
			if(q==NULL){
			/* error ouput */	
			}
			else{
				add_type = q->var_type;
				return add_type;
			}
		}
		else{
			printf("error!");		
		}
	}
	else{
		printf("error!");	
	}
}


Type Specifier(treeNode *root){
	treeNode *p=root;
	/* Specifier -> TYPE | StructSpecifier */
	Type add_type = (Type)malloc(sizeof(struct Type_));
	if(strcmp(p->childp->name,"TYPE")==0){
        add_type->kind = BASIC;
		if(strcmp(p->childp->data.strd,"int")==0)
			add_type->u.basic = INT;
		else if(strcmp(p->childp->data.strd,"float")==0)
			add_type->u.basic = FLOAT;
		else
			printf("error");
		return add_type;
    }
	else if(strcmp(p->childp->name,"StructSpecifier")==0){
		add_type = StructSpecifier(p->childp);
	}
	else{
		printf("error!");	
	}
}

/* add to the symbol table when defining */
void DefList(treeNode* root){
	/* like below */
	treeNode* DefList = root;
	while( DefList->childp != NULL ){
		/* each step deal with one type,semi and add it */
		treeNode* Def = DefList-> childp;
						
		treeNode * DecList = Def->childp->right;
		treeNode * specifierp = Def->childp;
		/* DecList -> Dec | Dec COMMA DecList */
		while( DecList != NULL ){
			struct item* add_new = (struct item*)malloc(sizeof(struct item));
			FieldList f = (FieldList)malloc(sizeof(struct FieldList_));
			treeNode * Dec = DecList->childp;
			/* deal with Dec -> VarDec | VarDec ASSIGNOP Exp */
			// the later one is error type 15
			f = VarDec(Dec->childp,Specifier(specifierp));
			add_new->var_type = f->type;
			strcpy(add_new->var_name,f->name);
			add_item(add_new);
			if( DecList -> childnum == 1 ){
				DecList = NULL;
			}
			else if( DecList -> childnum == 3 ){
				DecList = DecList->childp->right->right;
			}
			else{
					printf("error!");
			}
		}
		DefList = Def->right;
	}
}



