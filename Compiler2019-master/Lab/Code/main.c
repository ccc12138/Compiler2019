/* Ref P25 */
#include <stdio.h>
#include "semantic.h"
extern FILE* yyin;
int lexErrNum;
int synErrNum;
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
    yyrestart(f);
    yyparse();
    if(lexErrNum==0&&synErrNum==0){
        // PrintDFS(root,0);

        //Here we have complete tree and we can do semantic analysis
        Program(root);
    }
    // else{
    //     printf("lexErrNum=%d, synErrNum=%d\n", lexErrNum, synErrNum);
    // }
    return 0;
}
