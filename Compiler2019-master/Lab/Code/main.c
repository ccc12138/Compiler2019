/* Ref P25 */
#include <stdio.h>
extern FILE* yyin;
int yylex();
int yyrestart(FILE *);
void yyset_lineno(int);
int yyparse();
int main(int argc, char** argv){
	if(argc<=1)
		return 1;
	FILE* f=fopen(argv[1],"r");
    if(!f){
    	perror(argv[1]);
    	return 1;
    }
    yyrestart(f);
    yyset_lineno(1);//Ref P19: Reset yylineno = 1 when read in another input file
    yyparse();
    return 0;
}
