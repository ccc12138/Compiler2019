#include "syntaxTree.h"

void Build(struct Treenode **root, const char * cname , int num, ...){
    *root =  (struct Treenode*)malloc(sizeof(struct Treenode));
    (*root)->name = (char*)malloc(sizeof(char)*50);
    strcpy((*root)->name,cname);
    (*root)->childnum = num;
    //link all children using va_list
    va_list ap;
    va_start(ap, num);
    (*root)->childp = va_arg(ap,struct Treenode*);
    struct Treenode* pre = (*root)->childp;
    for( int i=1 ; i < num ; i++ ){
        struct Treenode* next = va_arg(ap,struct Treenode*);
        pre->right = next;
        pre = next;
    }
    pre->right = NULL;
    va_end(ap);
}

void PrintDFS(struct Treenode *root, int t_no){
    if(root==NULL)    return;
    for(int i=0;i<t_no;i++)    printf("\t");// num of \t
    printf("%s",root->name);
    //different types of printf
    PrintDFS(root->childp,t_no+1);
    PrintDFS(root->right,t_no);
}
