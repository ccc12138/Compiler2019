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
												InsertNode($$,1,$1);
												root=$$;
};
ExtDefList: 	ExtDef ExtDefList 			{
												$$=InitNode("ExtDefList",@$.first_line);
												InsertNode($$,2,$1,$2);
}
			|								{
												$$=InitNode("ExtDefList",@$.first_line);
};
ExtDef:			Specifier ExtDecList SEMI	{
												$$=InitNode("ExtDef",@$.first_line);
												InsertNode($$,3,$1,$2,$3);
}
			| 	Specifier SEMI				{
												$$=InitNode("ExtDef",@$.first_line);
												InsertNode($$,2,$1,$2);
}
			|	Specifier FunDec CompSt		{
												$$=InitNode("ExtDef",@$.first_line);
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
			|	IF LP Exp RP Stmt %prec LOWER_THAN_ELSE		{}// Ref: P33
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

