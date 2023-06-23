/*
	RUN:
	yacc -d exp8.y && lex exp8.l && gcc lex.yy.c y.tab.c && ./a.out

	INPUT:
	1.2+2*((4*5)/2)

	This program has no ID as we did in lab as it takes all number inputs
*/

%{
	#include<stdio.h>
	#include<stdlib.h>
	
	extern int yylex();
	void yyerror(char *s);
%}
/*
	Union is used to declare yylval types

	eg:
	%union{
		float floatType;
		char *stringType;
	}
	In lex file

	yylval.floatType = 2.114
	yylval.stringType = "hello"
*/
%union{
	float floatType;
}

%token <floatType> NUMBER
%type <floatType> S E

// Start production is E
%start S

/* 
	All tokens in same line have same precendence. As we go down precedence increases
	%left Indicates left associative
*/
%left '+' '-'
%left  '*' '/'
%left '(' ')'

%%

S	: 	E 			{ 
						printf("Result: %f\n", $$);
						return 0;
					}

E	:	E'+'E 		{ $$= $1+$3; }
	|	E'-'E 		{ $$= $1-$3; }
	|	E'*'E 		{ $$= $1*$3; }
	|	E'/'E		{ $$= $1/$3; }
	|	'-'NUMBER	{ $$= -$2; }
	|	'('E')'		{ $$= $2; }
	|	NUMBER		{ $$= $1; };
%%


void yyerror(char *s)
{
	printf("\n%s: Expression is invalid\n", s);
	exit(0);
}

void main()
{
	printf("\nEnter Expression:\n");
	yyparse();
	printf("\nExpression is valid\n");
}
