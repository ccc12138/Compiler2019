#include "interCode.h"

bool InsertCode(InterCode node){
	assert(node!=NULL);
	if(codeHead==NULL&&codeTail==NULL){
		codeHead=node;
		codeTail=node;
		node->next=NULL;
		node->prev=NULL;
	}
	else{
		node->prev=codeTail;
		node->next=codeHead;
		codeTail->next=node;
		codeHead->prev=node;
		codeTail=node;
	}
	return true;
}

bool DeleteCode(InterCode node){
	assert(node!=NULL&&codeHead!=NULL&&codeTail!=NULL);
	if(node==codeHead){
		codeHead=node->next;
		codeHead->prev=codeTail;
		codeTail->next=codeHead;
		free(node);
	}
	else if(node==codeTail){
		codeTail=node->prev;
		codeTail->next=codeHead;
		codeHead->prev=codeTail;
		free(node);
	}
	else{
		node->prev->next=node->next;
		node->next->prev=node->prev;
		free(node);
	}
	return true;
}