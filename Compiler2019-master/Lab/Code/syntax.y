%{
	
#include <stdio.h>
#include "lex.yy.c"
#include "syntaxTree.h"

int yyerror(char *msg);

%}

/* Declared tokens */
%token 		ID FLOAT INT SEMI COMMA ASSIGNOP RELOP PLUS MINUS
%token 		AND OR STAR DIV DOT NOT TYPE LP RP LB RB LC RC
%token 		STRUCT RETURN IF ELSE WHILE 

/* Ref: P121 */
%right 		ASSIGNOP
%left 		OR
%left 		AND
%left 		RELOP
%left 		PLUS MINUS
%left 		STAR DIV
%right 		NOT NEG //but we don't have NEG?
%left 		LP RP LB RB DOT

/* Ref: P33 */
%nonassoc 	LOWER_THAN_ELSE
%nonassoc 	ELSE

%%

/*High-level Definitions */
Program: 		ExtDefList					{}
	;
ExtDefList: 	ExtDef ExtDefList 			{}
			|								{}
			;
ExtDef:			Specifier ExtDecList SEMI	{}
			| 	Specifier SEMI				{}
			|	Specifier FunDec CompSt		{}
			;
ExtDecList:		VarDec						{}
			|	VarDec COMMA ExtDecList		{}
			;

/* Specifiers */
Specifier:		TYPE 						{}
			|	StructSpecifier				{}
			;
StructSpecifier:STRUCT OptTag LC DefList RC	{}
			|	STRUCT Tag 					{}
			;
OptTag: 		ID 							{}
			|								{}
			;
Tag:			ID 							{}
			;

/* Declarators */
VarDec: 		ID 							{}
			|	VarDec LB INT RB			{}
			;
FunDec:			ID LP VarList RB			{}
			|	ID LP RP 					{}
			;
VarList: 		ParamDec COMMA VarList 		{}
			| 	ParamDec					{}
			;
ParamDec: 		Specifier VarDec 			{}
			;

/* Statements */
CompSt: 		LC DefList StmtList RC						{}
			;
StmtList:		Stmt StmtList								{}
			|												{}
			;
Stmt:			Exp SEMI									{}
			|	CompSt										{}
			|	RETURN Exp SEMI								{}
			|	IF LP Exp RP Stmt %prec LOWER_THAN_ELSE		{}/* Ref: P33 */
			|	IF LP Exp RP Stmt ELSE Stmt 				{}
			| 	WHILE LP Exp RP Stmt 						{}
			;

/* Local Definitions */
DefList: 		Def DefList 				{}
			| 								{}
			;
Def: 			Specifier DecList SEMI		{}
			;
DecList: 		Dec 						{}
			|	Dec COMMA DecList 			{}
			;
Dec:			VarDec 						{}
			| 	VarDec ASSIGNOP Exp			{}
			;

/* Expressions */
Exp: 			Exp ASSIGNOP Exp 			{}
			| 	Exp AND Exp 				{}
			| 	Exp OR Exp 					{}
			| 	Exp RELOP Exp 				{}
			| 	Exp PLUS Exp 				{}
			| 	Exp MINUS Exp 				{}
			| 	Exp STAR Exp 				{}
			| 	Exp DIV Exp 				{}
			| 	LP Exp RP 					{}
			| 	MINUS Exp 		 			{}
			| 	NOT Exp 					{}
			| 	ID LP Args RP 	 			{}
			| 	ID LP RP 					{}
			| 	Exp LB Exp RB				{}
			| 	Exp DOT ID 					{}
			|	ID 							{}
			| 	INT 						{}
			| 	FLOAT 						{}
			;
Args: 			Exp COMMA Args 				{}
			| 	Exp 						{}
			;

