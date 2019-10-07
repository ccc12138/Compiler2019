#include "syntaxTree.h"

treeNode* InitNode(char* nodeName, int lineno){
    treeNode* node=(treeNode *)malloc(sizeof(treeNode));
    node->name=nodeName;
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


    /////////////////////////////////////////////////
    ////WRONG HERE!!!!!!Cause Segmentation Fault!////
    /////////////////////////////////////////////////
    va_list ap;
    va_start(ap, num);
    root->childnum = num;
    root->childp = va_arg(ap,treeNode*);
    treeNode* pre = (treeNode *)malloc(sizeof(treeNode));
    pre = root->childp;
    for( int i=1 ; i < num ; i++ ){
        treeNode* next = (treeNode *)malloc(sizeof(treeNode));
        next = va_arg(ap,treeNode*);
        pre->right = next;
        pre = next;
    }
    pre->right = NULL;
    va_end(ap);
    ////////////////////////////////////////////////
}

void PrintDFS(treeNode *root, int t_no){
    if(root==NULL)
        return;
    for(int i=0;i<t_no;i++)
        printf("  ");//Ref P3, Print 2 blanks
    printf("%s",root->name);
    //different types of printf
    PrintDFS(root->childp,t_no+1);
    PrintDFS(root->right,t_no);
}
