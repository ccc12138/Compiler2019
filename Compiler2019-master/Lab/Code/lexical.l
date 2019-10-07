%{

#include "syntax.tab.h"
#include "syntaxTree.h"
#include <assert.h>

/* Ref: P31 */
int yycolumn = 1;
#define YY_USER_ACTION \
	yylloc.first_line = yylloc.last_line = yylineno; \
	yylloc.first_column = yycolumn; \
	yylloc.last_column = yycolumn + yyleng - 1; \
	yycolumn += yyleng;
void PrintInfol(char *s,int lineno);
void PrintInfom(char *s,int lineno,int type,treeNode* node);

%}


%option yylineno

digit		[0-9]
INT			0|([1-9][0-9]*)
RE_FLOAT	({digit}+\.{digit}+)
SC_FLOAT	(((\.{digit}+)|({digit}+\.)|({digit}+\.{digit}+))[eE][+-]?{digit}+)
FLOAT		{RE_FLOAT}|{SC_FLOAT}
ERR_FLOAT	(((\.{digit}+)|({digit}+\.)|({digit}+\.{digit}+))[eE][+-]?)|({digit}+[eE]{digit}*)
SEMI		;
COMMA		,
ASSIGNOP	=	
RELOP		>|<|(>=)|(<=)|(==)|(!=)
PLUS		\+
MINUS		-
STAR		\*
DIV			\/
AND			&&
OR			\|\|
DOT			\.
NOT			!
TYPE		int|float
LP			\(
RP			\)
LB			\[
RB			\]
LC			\{
RC			\}
newline 	[\n\r]
whitespace 	[ \t]+
ID			[a-zA-Z_][a-zA-Z0-9_]*
%%
{FLOAT}		{	treeNode* yylval=InitNode("FLOAT",TOKENS_FLOAT,yylloc.first_line);
				sscanf(yytext,"%f",&yylval->data.floatd);//Ref: p3
				PrintInfom("FLOAT",yylloc.first_line,2,yylval);
				return FLOAT;			}
{ERR_FLOAT}	{	printf("Error type A at Line %d: Illegal floating point number \"%s\"\n",yylineno,yytext);
				////////////////////////////////
				//we need some error hint here//
				////////////////////////////////
				return FLOAT;			}
{INT}		{	treeNode* yylval=InitNode("INT",TOKENS_INT,yylloc.first_line);
				sscanf(yytext,"%d",&yylval->data.intd);//Ref: p3
				PrintInfom("INT",yylloc.first_line,1,yylval);
				return INT;				}
{SEMI}		{	treeNode* yylval=InitNode("SEMI",TOKENS_SEMI,yylloc.first_line);
				PrintInfol("SEMI",yylloc.first_line);
				return SEMI;			}
{COMMA}		{	treeNode* yylval=InitNode("COMMA",TOKENS_COMMA,yylloc.first_line);
				PrintInfol("COMMA",yylloc.first_line);
				return COMMA;			}
{ASSIGNOP}	{	treeNode* yylval=InitNode("ASSIGNOP",TOKENS_ASSIGNOP,yylloc.first_line);
				PrintInfol("ASSIGNOP",yylloc.first_line);
				return ASSIGNOP;		}
{RELOP}		{	treeNode* yylval=InitNode("RELOP",TOKENS_RELOP,yylloc.first_line);
				PrintInfol("RELOP",yylloc.first_line);
				return RELOP;			}
{PLUS}		{	treeNode* yylval=InitNode("PLUS",TOKENS_PLUS,yylloc.first_line);
				PrintInfol("OR",yylloc.first_line);
				return PLUS;			}
{MINUS}		{	treeNode* yylval=InitNode("MINUS",TOKENS_MINUS,yylloc.first_line);
				PrintInfol("MINUS",yylloc.first_line);
				return MINUS;			}
{AND}		{	treeNode* yylval=InitNode("AND",TOKENS_AND,yylloc.first_line);
				PrintInfol("AND",yylloc.first_line);
				return AND;				}
{OR}		{	treeNode* yylval=InitNode("OR",TOKENS_OR,yylloc.first_line);
				PrintInfol("OR",yylloc.first_line);
				return OR;				}
{STAR}		{	treeNode* yylval=InitNode("STAR",TOKENS_STAR,yylloc.first_line);
				PrintInfol("STAR",yylloc.first_line);
				return STAR;			}
{DIV}		{	treeNode* yylval=InitNode("DIV",TOKENS_DIV,yylloc.first_line);
				PrintInfol("DIV",yylloc.first_line);
				return DIV;				}
{DOT}		{	treeNode* yylval=InitNode("DOT",TOKENS_DOT,yylloc.first_line);
				PrintInfol("DOT",yylloc.first_line);
				return DOT;				}
{NOT}		{	treeNode* yylval=InitNode("NOT",TOKENS_NOT,yylloc.first_line);
				PrintInfol("NOT",yylloc.first_line);
				return NOT;				}
{TYPE}		{	treeNode* yylval=InitNode("TYPE",TOKENS_TYPE,yylloc.first_line);
				sscanf(yytext,"%s",&yylval->data.strd);
				PrintInfom("TYPE",yylloc.first_line,3,yylval);
				return TYPE;			}
{LP}		{	treeNode* yylval=InitNode("LP",TOKENS_LP,yylloc.first_line);
				PrintInfol("LP",yylloc.first_line);
				return LP;				}
{RP}		{	treeNode* yylval=InitNode("RP",TOKENS_RP,yylloc.first_line);
				PrintInfol("RP",yylloc.first_line);
				return RP;				}
{LB}		{	treeNode* yylval=InitNode("LB",TOKENS_LB,yylloc.first_line);
				PrintInfol("LB",yylloc.first_line);
				return LB;				}
{RB}		{	treeNode* yylval=InitNode("RB",TOKENS_RB,yylloc.first_line);
				PrintInfol("RB",yylloc.first_line);
				return RB;				}
{LC}		{	treeNode* yylval=InitNode("LC",TOKENS_LC,yylloc.first_line);
				PrintInfol("LC",yylloc.first_line);
				return LC;				}
{RC}		{	treeNode* yylval=InitNode("RC",TOKENS_RC,yylloc.first_line);
				PrintInfol("RC",yylloc.first_line);
				return RC;				}
"struct"	{	treeNode* yylval=InitNode("STRUCT",TOKENS_STRUCT,yylloc.first_line);
				PrintInfol("STRUCT",yylloc.first_line);
				return STRUCT;			}
"return"	{	treeNode* yylval=InitNode("RETURN",TOKENS_RETURN,yylloc.first_line);
				PrintInfol("RETURN",yylloc.first_line);
				return RETURN;			}
"if"		{	treeNode* yylval=InitNode("IF",TOKENS_IF,yylloc.first_line);
				PrintInfol("IF",yylloc.first_line);
				return IF;				}
"else"		{	treeNode* yylval=InitNode("ELSE",TOKENS_ELSE,yylloc.first_line);
				PrintInfol("ELSE",yylloc.first_line);
				return ELSE;			}
"while"		{	treeNode* yylval=InitNode("WHILE",TOKENS_WHILE,yylloc.first_line);
				PrintInfol("WHILE",yylloc.first_line);
				return WHILE;			}
{newline}	{	yycolumn = 1;			
										}//Ref: P31
{whitespace} {}
{ID}		{	treeNode* yylval=InitNode("ID",TOKENS_ID,yylloc.first_line);
				sscanf(yytext,"%s",&yylval->data.strd);
				PrintInfom("ID",yylloc.first_line,3,yylval);
				return ID;				}
.			{	printf("Error type A at line %d: Mysterious characters \'%s\'\n",yylineno,yytext);}

%%

/* Just for debug */
void PrintInfol(char *s,int lineno){//Print less info
	printf("%s(line %d)\n",s,lineno);
	return;
}
void PrintInfom(char *s,int lineno,int type,treeNode* node){//Print more info
	switch(type){
		case 1: printf("%s(line %d): %d\n",s,lineno,node->data.intd); break;
		case 2: printf("%s(line %d): %f\n",s,lineno,node->data.floatd); break;
		case 3: printf("%s(line %d): %s\n",s,lineno,node->data.strd); break;
		default: assert(0);
	}
	return;
}