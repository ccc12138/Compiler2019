#include "syntaxTree.h"

treeNode* InitNode(char* nodeName, int lineno){
    treeNode* node=(treeNode *)malloc(sizeof(treeNode));
    node->name=nodeName;
    //printf("initate:%s\n",nodeName);
    node->childnum=0;
    node->lineno=lineno;
    node->right=NULL;
    node->childp=NULL;
    return node;
}

void InsertNode(treeNode *root, int num, ...){
    // *root =  (treeNode*)malloc(sizeof(treeNode));
    // (*root)->name = (char*)malloc(sizeof(char)*50);
    // strcpy((*root)->name,cname);
    //link all children using va_list

    va_list ap;
    va_start(ap, num);
    root->childnum = num;
    root->childp = va_arg(ap,treeNode*);
    treeNode* pre = root->childp;
    int i=1;
    for( ; i < num ; i++ ){
        treeNode* next = va_arg(ap,treeNode*);	
        pre->right = next;
        pre = next;
    }
    pre->right = NULL;
    va_end(ap);
}

void PrintDFS(treeNode *node, int t_no){
    if(node==NULL||node->name=="NULL")
        return;
    int i=0;
    if(strcmp(node->name,"EPSILON")!=0){//NOT EPSILON
        for(;i<t_no;i++)
            printf("  ");//Ref P3, Print 2 blanks
        if(node->childp==NULL){//token
            if(strcmp(node->name,"ID")==0){
                printf("%s: %s\n",node->name,node->data.strd);
            }
            else if(strcmp(node->name,"TYPE")==0){
                printf("%s: %s\n",node->name,node->data.strd);
            }
            else if(strcmp(node->name,"INT")==0){
                printf("%s: %d\n",node->name,node->data.intd);
            }
            else if(strcmp(node->name,"FLOAT")==0){
                printf("%s: %f\n",node->name,node->data.floatd);
            }
            else{
                printf("%s\n",node->name);
            }
        }
        else{//syntax unit
            printf("%s (%d)\n",node->name,node->lineno);
        }
    }
    //different types of printf
    PrintDFS(node->childp,t_no+1);
    PrintDFS(node->right,t_no);
}