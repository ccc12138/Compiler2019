/* Ref P25 */
#include <stdio.h>
#include "mips.h"
extern FILE* yyin;
int lexErrNum;
int synErrNum;
int semErrNum;
InterCode codeHead;
InterCode codeTail;
BasicBlock blockHead;
BasicBlock blockTail;
unsigned varNum;
unsigned tempVarNum;
unsigned labelNum;
int yylex();
int yyrestart(FILE *);
void yyset_lineno(int);
int yyparse();
extern treeNode* root;
int main(int argc, char** argv){
	if(argc<=1)
		return 1;
	FILE* f=fopen(argv[1],"r");
    if(!f){
    	perror(argv[1]);
    	return 1;
    }
    yyset_lineno(1);//Ref P19: Reset yylineno = 1 when read in another input file
    lexErrNum=0;
    synErrNum=0;
    semErrNum=0;
    codeHead=NULL;
    codeTail=NULL;
    blockHead=NULL;
    blockTail=NULL;
    varNum=1;
    tempVarNum=1;
    labelNum=1;
    yyrestart(f);
    yyparse();
    if(lexErrNum==0&&synErrNum==0){
        // PrintDFS(root,0);
        //Here we have complete tree and we can do semantic analysis
        Program(root);
        // Here we need to optimize code
        // Begin:

        // End
        // Here we need to printCode()
        if(semErrNum==0&&argc==3){
            FILE *fp=fopen(argv[2],"w");
            // printf("%s\n",argv[2]);
            if(!fp){
                perror(argv[2]);
                return 1;
            }
#ifdef DEBUG
            printf("Start Translate Program...\n");
#endif
            translate_Program(root);
#ifdef DEBUG
            printf("Translate succ!\n");
            printf("Start Optimize Code...\n");
#endif
            OptimizeCode();
#ifdef DEBUG
            printf("Optimize succ!\n");
#endif
            // PrintCode(fp);
            PrintMips(fp);
            fclose(fp);
        }
        // else{
        //     printf("semErrNum=%d\n",semErrNum);
        // }
    }
    fclose(f);
    return 0;
}
