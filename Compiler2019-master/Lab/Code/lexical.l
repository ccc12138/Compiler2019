%{

#include "syntax.tab.h"

/* BUG: ‘yylloc’ undeclared (first use in this function); did you mean ‘yyalloc’? */
/* Ref: P31 */
int yycolumn = 1;
#define YY_USER_ACTION \
	yylloc.first_line = yylloc.last_line = yylineno; \
	yylloc.first_column = yycolumn; \
	yylloc.last_column = yycolumn + yyleng - 1; \
	yycolumn += yyleng;
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
{FLOAT}		{	printf("FLOAT\n");
				return FLOAT;			}
{ERR_FLOAT}	{	printf("Error type A at Line %d: Illegal floating point number \"%s\"\n",yylineno,yytext);
				//we need some error hint here
				return FLOAT;			}
{INT}		{	printf("INT\n");
				return INT;				}
{SEMI}		{	printf("SEMI\n");
				return SEMI;			}
{COMMA}		{	printf("COMMA\n");
				return COMMA;			}
{ASSIGNOP}	{	printf("ASSIGNOP\n");
				return ASSIGNOP;		}
{RELOP}		{	printf("RELOP\n");
				return RELOP;			}
{PLUS}		{	printf("OR\n");
				return PLUS;			}
{MINUS}		{	printf("MINUS\n");
				return MINUS;			}
{AND}		{	printf("AND\n");
				return AND;				}
{OR}		{	printf("OR\n");
				return OR;				}
{STAR}		{	printf("STAR\n");
				return STAR;			}
{DIV}		{	printf("DIV\n");
				return DIV;				}
{DOT}		{	printf("DOT\n");
				return DOT;				}
{NOT}		{	printf("NOT\n");
				return NOT;				}
{TYPE}		{	printf("TYPE\n");
				return TYPE;			}
{LP}		{	printf("LP\n");
				return LP;				}
{RP}		{	printf("RP\n");
				return RP;				}
{LB}		{	printf("LB\n");
				return LB;				}
{RB}		{	printf("RB\n");
				return RB;				}
{LC}		{	printf("LC\n");
				return LC;				}
{RC}		{	printf("RC\n");
				return RC;				}
"struct"	{	printf("struct\n");
				return STRUCT;			}
"return"	{	printf("return\n");
				return RETURN;			}
"if"		{	printf("if\n");
				return IF;				}
"else"		{	printf("else\n");
				return ELSE;			}
"while"		{	printf("while\n");
				return WHILE;			}
{newline}	{	yycolumn = 1;			
										}//Ref: P31
{whitespace} {}
{ID}		{	printf("ID\n");
				return ID;				}
.			{	printf("Error type A at line %d: Mysterious characters \'%s\'\n",yylineno,yytext);}

%%