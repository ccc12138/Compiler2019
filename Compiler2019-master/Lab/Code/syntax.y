%locations

%{
	
#include <stdio.h>
#include "lex.yy.c"

int yyerror(char *msg);
treeNode* root;
extern int synErrNum;
int PrintSynErr(int,char*,int);
int prevRow=0;

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
												//PrintDFS(root,0);
};
ExtDefList: 	ExtDef ExtDefList 			{
												$$=InitNode("ExtDefList",@$.first_line);
												//$1=InitNode("ExtDef",@$.first_line);
												//$2=InitNode("ExtDefList",@$.first_line);
												InsertNode($$,2,$1,$2);
}
			|								{
												$$=InitNode("EPSILON",@$.first_line);
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
}
			|	Specifier FunDec SEMI		{
												$$=InitNode("ExtDef",@$.first_line);
												InsertNode($$,2,$1,$2);
}			
			|	error SEMI					{
												++synErrNum;
												prevRow=PrintSynErr(@$.first_line,";",prevRow);
}
;
ExtDecList:		VarDec						{
												$$=InitNode("ExtDecList",@$.first_line);
												InsertNode($$,1,$1);
}
			|	VarDec COMMA ExtDecList		{
												$$=InitNode("ExtDecList",@$.first_line);
												InsertNode($$,3,$1,$2,$3);
};

/* Specifiers */
Specifier:		TYPE 						{$$=InitNode("Specifier",@$.first_line);InsertNode($$,1,$1);}
			|	StructSpecifier				{$$=InitNode("Specifier",@$.first_line);InsertNode($$,1,$1);}
			;
StructSpecifier:STRUCT OptTag LC DefList RC	{
												$$=InitNode("StructSpecifier",@$.first_line);
												InsertNode($$,5,$1,$2,$3,$4,$5);
}
			|	STRUCT Tag 					{
												$$=InitNode("StructSpecifier",@$.first_line);
												InsertNode($$,2,$1,$2);
}
			|	STRUCT OptTag LC error RC	{
												++synErrNum;
												prevRow=PrintSynErr(@$.first_line,"}",prevRow);
}
			|	STRUCT error LC DefList RC	{
												++synErrNum;
												prevRow=PrintSynErr(@$.first_line,"}",prevRow);
}
;
OptTag: 		ID 							{$$=InitNode("OptTag",@$.first_line);InsertNode($$,1,$1);}
			|								{$$=InitNode("EPSILON",@$.first_line);}
			;
Tag:			ID 							{$$=InitNode("Tag",@$.first_line);InsertNode($$,1,$1);}
			;

/* Declarators */
VarDec: 		ID 							{
												$$=InitNode("VarDec",@$.first_line);InsertNode($$,1,$1);
}
			|	VarDec LB INT RB			{
												$$=InitNode("VarDec",@$.first_line);InsertNode($$,4,$1,$2,$3,$4);
}
			|	VarDec LB error RB			{
												++synErrNum;
												prevRow=PrintSynErr(@$.first_line,"]",prevRow);
};
FunDec:			ID LP VarList RP			{
												$$=InitNode("FunDec",@$.first_line);InsertNode($$,4,$1,$2,$3,$4);
}
			|	ID LP RP 					{
												$$=InitNode("FunDec",@$.first_line);InsertNode($$,3,$1,$2,$3);
}
			|	error RP 					{
												++synErrNum;
												prevRow=PrintSynErr(@$.first_line,")",prevRow);
};

VarList: 		ParamDec COMMA VarList 		{
												$$=InitNode("VarList",@$.first_line);InsertNode($$,3,$1,$2,$3);
}
			| 	ParamDec					{
												$$=InitNode("VarList",@$.first_line);InsertNode($$,1,$1);
};

ParamDec: 		Specifier VarDec 			{
												$$=InitNode("ParamDec",@$.first_line);InsertNode($$,2,$1,$2);
};

/* Statements */
CompSt: 		LC DefList StmtList RC						{
																$$=InitNode("CompSt",@$.first_line);
																InsertNode($$,4,$1,$2,$3,$4);
}
			|	error RC									{
																++synErrNum;
																prevRow=PrintSynErr(@$.first_line,"}",prevRow);
}
;
StmtList:		Stmt StmtList								{
																$$=InitNode("StmtList",@$.first_line);
																InsertNode($$,2,$1,$2);
}
			|												{
																$$=InitNode("EPSILON",@$.first_line);
};
Stmt:			Exp SEMI									{
																$$=InitNode("Stmt",@$.first_line);
																InsertNode($$,2,$1,$2);
}
			|	error SEMI									{
																++synErrNum;
																prevRow=PrintSynErr(@$.first_line,";",prevRow);
}
			| 	Exp error 									{
																++synErrNum;
																prevRow=PrintSynErr(@$.first_line,";",prevRow);
}
			|	CompSt										{	
																$$=InitNode("Stmt",@$.first_line);
																InsertNode($$,1,$1);
}
			|	RETURN Exp SEMI								{	$$=InitNode("Stmt",@$.first_line);
																InsertNode($$,3,$1,$2,$3);
}
			| 	RETURN Exp error 							{
																++synErrNum;
																prevRow=PrintSynErr(@$.first_line,";",prevRow);
}
			|	IF LP Exp RP Stmt %prec LOWER_THAN_ELSE		{ 	$$=InitNode("Stmt",@$.first_line);
                                                                InsertNode($$,5,$1,$2,$3,$4,$5);}// Ref: P33
			|	IF LP Exp RP Stmt ELSE Stmt 				{
																$$=InitNode("Stmt",@$.first_line);
																InsertNode($$,7,$1,$2,$3,$4,$5,$6,$7);
}
			|	IF LP Exp RP error ELSE Stmt 				{
																++synErrNum;
																prevRow=PrintSynErr(@$.first_line,";",prevRow);
}
			| 	WHILE LP Exp RP Stmt 						{	
																$$=InitNode("Stmt",@$.first_line);
																InsertNode($$,5,$1,$2,$3,$4,$5);
}
;

/* Local Definitions */
DefList: 		Def DefList 				{$$=InitNode("DefList",@$.first_line);InsertNode($$,2,$1,$2);}
			| 								{$$=InitNode("EPSILON",@$.first_line);}
			;
Def: 			Specifier DecList SEMI		{$$=InitNode("Def",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			|	Specifier error SEMI		{
												++synErrNum;
												prevRow=PrintSynErr(@$.first_line,";",prevRow);
}
			|	Specifier DecList error 	{
												++synErrNum;
												prevRow=PrintSynErr(@$.first_line,";",prevRow);
}
;
DecList: 		Dec 						{$$=InitNode("DecList",@$.first_line);InsertNode($$,1,$1);}
			|	Dec COMMA DecList 			{$$=InitNode("DecList",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			;
Dec:			VarDec 						{$$=InitNode("Dec",@$.first_line);InsertNode($$,1,$1);}
			| 	VarDec ASSIGNOP Exp			{$$=InitNode("Dec",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			;

/* Expressions */
Exp: 			Exp ASSIGNOP Exp 			{$$=InitNode("Exp",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	Exp AND Exp 				{$$=InitNode("Exp",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	Exp OR Exp 					{$$=InitNode("Exp",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	Exp RELOP Exp 				{$$=InitNode("Exp",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	Exp PLUS Exp 				{$$=InitNode("Exp",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	Exp MINUS Exp 				{$$=InitNode("Exp",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	Exp STAR Exp 				{$$=InitNode("Exp",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	Exp DIV Exp 				{$$=InitNode("Exp",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	LP Exp RP 					{$$=InitNode("Exp",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	MINUS Exp 		 			{$$=InitNode("Exp",@$.first_line);InsertNode($$,2,$1,$2);}
			| 	NOT Exp 					{$$=InitNode("Exp",@$.first_line);InsertNode($$,2,$1,$2);}
			| 	ID LP Args RP 	 			{$$=InitNode("Exp",@$.first_line);InsertNode($$,4,$1,$2,$3,$4);}
			| 	ID LP RP 					{$$=InitNode("Exp",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	Exp LB Exp RB				{$$=InitNode("Exp",@$.first_line);InsertNode($$,4,$1,$2,$3,$4);}
			| 	Exp DOT ID 					{$$=InitNode("Exp",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			|	ID 							{$$=InitNode("Exp",@$.first_line);InsertNode($$,1,$1);}
			| 	INT 						{$$=InitNode("Exp",@$.first_line);InsertNode($$,1,$1);}
			| 	FLOAT 						{$$=InitNode("Exp",@$.first_line);InsertNode($$,1,$1);}
			| 	LP error RP 				{
												++synErrNum;
												prevRow=PrintSynErr(@$.first_line,")",prevRow);
}
			| 	ID LP error RP 				{
												++synErrNum;
												prevRow=PrintSynErr(@$.first_line,")",prevRow);
}
			| 	Exp LB error RB 			{
												++synErrNum;
												prevRow=PrintSynErr(@$.first_line,"]",prevRow);
}
			| 	error LB Exp RB 			{
												++synErrNum;
												prevRow=PrintSynErr(@$.first_line,"]",prevRow);
}
;
Args: 			Exp COMMA Args 				{$$=InitNode("Args",@$.first_line);InsertNode($$,3,$1,$2,$3);}
			| 	Exp 						{$$=InitNode("Args",@$.first_line);InsertNode($$,1,$1);}
;
%%
int yyerror(char *msg){
	//printf("syntax error\n");
    return 0;
}

int PrintSynErr(int lineno, char *miss, int prevLine){
	if(lineno!=prevLine){//prevLine is for robust in case of outputing mul err msg
		printf("Error type B at Line %d: Missing \"%s\".\n",lineno,miss);
	}
	return lineno;
}
