%locations

%{
	
#include <stdio.h>
#include "lex.yy.c"

int yyerror(char *msg);
treeNode* root;

%}

/* Declared types */
%union {
	struct treeNode* type_node;
}

/* Declared tokens */
%token <type_node> ID FLOAT INT SEMI COMMA ASSIGNOP RELOP PLUS MINUS
%token <type_node> AND OR STAR DIV DOT NOT TYPE LP RP LB RB LC RC
%token <type_node> STRUCT RETURN IF ELSE WHILE 

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

/* Declared non-terminals */
%type <type_node>	Program ExtDefList ExtDef ExtDecList
					Specifier StructSpecifier OptTag Tag
					VarDec FunDec VarList ParamDec 
					CompSt StmtList Stmt 
					DefList Def DecList Dec
					Exp Args


%%

/*High-level Definitions */
Program: 		ExtDefList					{
												$$=InitNode("Program",@$.first_line);
												//$1=InitNode("ExtDefList",@$.first_line);
												InsertNode($$,1,$1);
												root=$$;
												PrintDFS(root,0);
};
ExtDefList: 	ExtDef ExtDefList 			{
												$$=InitNode("ExtDefList",@$.first_line);
												//$1=InitNode("ExtDef",@$.first_line);
												//$2=InitNode("ExtDefList",@$.first_line);
												InsertNode($$,2,$1,$2);
}
			|								{
												$$=InitNode("ExtDefList",@$.first_line);
};
ExtDef:			Specifier ExtDecList SEMI	{
												$$=InitNode("ExtDef",@$.first_line);
												//$1=InitNode("Specifier",@$.first_line);
												//$2=InitNode("ExtDefList",@$.first_line);
												//$3=InitNode("SEMI",@$.first_line);
												InsertNode($$,3,$1,$2,$3);
}
			| 	Specifier SEMI				{
												$$=InitNode("ExtDef",@$.first_line);
												//$1=InitNode("Specifier",@$.first_line);
												//$2=InitNode("SEMI",@$.first_line);
												InsertNode($$,2,$1,$2);
}
			|	Specifier FunDec CompSt		{
												
												$$=InitNode("ExtDef",@$.first_line);
												//$1=InitNode("Specifier",@$.first_line);
												//$2=InitNode("FunDec",@$.first_line);
												//$3=InitNode("CompSt",@$.first_line);
												InsertNode($$,3,$1,$2,$3);
};
ExtDecList:		VarDec						{
												$$=InitNode("ExtDecList",@$.first_line);
												InsertNode($$,1,$1);
}
			|	VarDec COMMA ExtDecList		{
												$$=InitNode("ExtDecList",@$.first_line);
						
						InsertNode($$,3,$1,$2,$3);
};

/* Specifiers */
Specifier:		TYPE 						{$$=InitNode("Specifier",@$.first_line);$1=InitNode("TYPE",@$.first_line);InsertNode($$,1,$1);}
			|	StructSpecifier				{$$=InitNode("Specifier",@$.first_line);InsertNode($$,1,$1);}
			;
StructSpecifier:STRUCT OptTag LC DefList RC	{$$=InitNode("StructSpecifier",@$.first_line);$1=InitNode("STRUCT",@$.first_line);$3=InitNode("LC",@$.first_line);$5=InitNode("RC",@$.first_line);InsertNode($$,5,$1,$2,$3,$4,$5);}
			|	STRUCT Tag 					{$$=InitNode("StructSpecifier",@$.first_line);$1=InitNode("STRUCT",@$.first_line);InsertNode($$,2,$1,$2);}
			;
OptTag: 		ID 							{$$=InitNode("OptTage",@$.first_line);$1=InitNode("ID",@$.first_line);InsertNode($$,1,$1);}
			|								{$$=InitNode("OptTage",@$.first_line);}
			;
Tag:			ID 							{$$=InitNode("Tag",@$.first_line);$1=InitNode("ID",@$.first_line);InsertNode($$,1,$1);}
			;

/* Declarators */
VarDec: 		ID 							{$$=InitNode("VarDec",@$.first_line);$1=InitNode("ID",@$.first_line);InsertNode($$,1,$1);}
			|	VarDec LB INT RB			{$$=InitNode("VarDec",@$.first_line);$2=InitNode("LB",@$.first_line);$3=InitNode("INT",@$.first_line);$4=InitNode("RB",@$.first_line);InsertNode($$,4,$1,$2,$3,$4);}
			;
FunDec:			ID LP VarList RB			{$$=InitNode("FunDec",@$.first_line);$1=InitNode("ID",@$.first_line);$2=InitNode("LP",@$.first_line);$4=InitNode("RB",@$.first_line);InsertNode($$,4,$1,$2,$3,$4);}
			|	ID LP RP 					{$$=InitNode("FunDec",@$.first_line);$1=InitNode("ID",@$.first_line);$2=InitNode("LP",@$.first_line);$3=InitNode("RP",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			;
VarList: 		ParamDec COMMA VarList 		{$$=InitNode("VarList",@$.first_line);$2=InitNode("COMMA",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	ParamDec					{$$=InitNode("VarList",@$.first_line);InsertNode($$,1,$1);}
			;
ParamDec: 		Specifier VarDec 			{$$=InitNode("ParamDec",@$.first_line);InsertNode($$,2,$1,$2);}
			;

/* Statements */
CompSt: 		LC DefList StmtList RC						{$$=InitNode("CompSt",@$.first_line);$1=InitNode("LC",@$.first_line);$4=InitNode("RC",@$.first_line);InsertNode($$,4,$1,$2,$3,$4);}
			;
StmtList:		Stmt StmtList								{$$=InitNode("StmtList",@$.first_line);InsertNode($$,2,$1,$2);}
			|												{$$=InitNode("StmtList",@$.first_line);}
			;
Stmt:			Exp SEMI									{$$=InitNode("Stmt",@$.first_line);$2=InitNode("SEMI",@$.first_line);InsertNode($$,2,$1,$2);}
			|	CompSt										{$$=InitNode("Stmt",@$.first_line);InsertNode($$,1,$1);}
			|	RETURN Exp SEMI								{$$=InitNode("Stmt",@$.first_line);$1=InitNode("RETURN",@$.first_line);$3=InitNode("SEMI",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			|	IF LP Exp RP Stmt %prec LOWER_THAN_ELSE		{}// Ref: P33
			|	IF LP Exp RP Stmt ELSE Stmt 				{$$=InitNode("Stmt",@$.first_line);$1=InitNode("IF",@$.first_line);$2=InitNode("LP",@$.first_line);$4=InitNode("RP",@$.first_line);$6=InitNode("ELSE",@$.first_line);InsertNode($$,7,$1,$2,$3,$4,$5,$6,$7);}
			| 	WHILE LP Exp RP Stmt 						{$$=InitNode("Stmt",@$.first_line);$1=InitNode("WHILE",@$.first_line);$2=InitNode("LP",@$.first_line);$4=InitNode("RP",@$.first_line);InsertNode($$,4,$1,$2,$3,$4,$5);}
			;

/* Local Definitions */
DefList: 		Def DefList 				{$$=InitNode("DefList",@$.first_line);InsertNode($$,2,$1,$2);}
			| 								{$$=InitNode("DefList",@$.first_line);}
			;
Def: 			Specifier DecList SEMI		{$$=InitNode("Def",@$.first_line);$3=InitNode("SEMI",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			;
DecList: 		Dec 						{$$=InitNode("DecList",@$.first_line);InsertNode($$,1,$1);}
			|	Dec COMMA DecList 			{$$=InitNode("DecList",@$.first_line);$2=InitNode("COMMA",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			;
Dec:			VarDec 						{$$=InitNode("Dec",@$.first_line);InsertNode($$,1,$1);}
			| 	VarDec ASSIGNOP Exp			{$$=InitNode("Dec",@$.first_line);$2=InitNode("ASSIGNOP",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			;

/* Expressions */
Exp: 			Exp ASSIGNOP Exp 			{$$=InitNode("Exp",@$.first_line);$2=InitNode("ASSIGNOP",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	Exp AND Exp 				{$$=InitNode("Exp",@$.first_line);$2=InitNode("AND",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	Exp OR Exp 					{$$=InitNode("Exp",@$.first_line);$2=InitNode("OR",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	Exp RELOP Exp 				{$$=InitNode("Exp",@$.first_line);$2=InitNode("RELOP",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	Exp PLUS Exp 				{$$=InitNode("Exp",@$.first_line);$2=InitNode("PLUS",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	Exp MINUS Exp 				{$$=InitNode("Exp",@$.first_line);$2=InitNode("MINUS",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	Exp STAR Exp 				{$$=InitNode("Exp",@$.first_line);$2=InitNode("STAR",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	Exp DIV Exp 				{$$=InitNode("Exp",@$.first_line);$2=InitNode("DIV",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	LP Exp RP 					{$$=InitNode("Exp",@$.first_line);$1=InitNode("LP",@$.first_line);$3=InitNode("RP",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	MINUS Exp 		 			{$$=InitNode("Exp",@$.first_line);$1=InitNode("MINUS",@$.first_line);InsertNode($$,2,$1,$2);}
			| 	NOT Exp 					{$$=InitNode("Exp",@$.first_line);$2=InitNode("NOT",@$.first_line);InsertNode($$,2,$1,$2);}
			| 	ID LP Args RP 	 			{$$=InitNode("Exp",@$.first_line);$1=InitNode("ID",@$.first_line);$2=InitNode("LP",@$.first_line);$4=InitNode("RP",@$.first_line);InsertNode($$,4,$1,$2,$3,$4);}
			| 	ID LP RP 					{$$=InitNode("Exp",@$.first_line);$1=InitNode("ID",@$.first_line);$2=InitNode("LP",@$.first_line);$3=InitNode("RP",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	Exp LB Exp RB				{$$=InitNode("Exp",@$.first_line);$2=InitNode("LB",@$.first_line);$4=InitNode("RB",@$.first_line);InsertNode($$,4,$1,$2,$3,$4);}
			| 	Exp DOT ID 					{$$=InitNode("Exp",@$.first_line);$2=InitNode("DOT",@$.first_line);$3=InitNode("ID",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			|	ID 							{$$=InitNode("Exp",@$.first_line);$1=InitNode("ID",@$.first_line);InsertNode($$,1,$1);}
			| 	INT 						{$$=InitNode("Exp",@$.first_line);$1=InitNode("INT",@$.first_line);InsertNode($$,1,$1);}
			| 	FLOAT 						{$$=InitNode("Exp",@$.first_line);$1=InitNode("FLOAT",@$.first_line);InsertNode($$,1,$1);}
			;
Args: 			Exp COMMA Args 				{$$=InitNode("Args",@$.first_line);$2=InitNode("COMMA",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	Exp 						{$$=InitNode("Args",@$.first_line);InsertNode($$,1,$1);}
			;
%%
int yyerror(char *msg){
	printf("syntax error\n");
    return 0;
}

