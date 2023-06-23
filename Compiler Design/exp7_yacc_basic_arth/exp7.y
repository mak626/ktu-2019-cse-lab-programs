/*
	https://www.ibm.com/docs/en/aix/7.2?topic=information-yacc-grammar-file-declarations
	https://www.ibm.com/docs/en/zos/2.3.0?topic=yacc-types
*/

/*
	RUN:
	yacc -d exp7.y && lex exp7.l && gcc lex.yy.c y.tab.c && ./a.out

	INPUT:
	12+2*((4*5)/2)
*/

%{
	#include<stdio.h>
	#include<stdlib.h>
	
	void yyerror(char *s);
	extern int yylex();
%}

%token NUMBER ID

// Start production is S
%start S

/* 
	All tokens in same line have same precendence. As we go down precedence increases
	%left Indicates left associative
*/
%left '+' '-'
%left  '*' '/'
%left '(' ')'

%%
S	: 	E
E	:	E'+'E 
	|	E'-'E
	|	E'*'E
	|	E'/'E
	|	'('E')'
	|	'-'NUMBER
	|	'-'ID
	|	NUMBER
	|	ID;
%%


void yyerror(char *s)
{
	printf("\n%s: Expression is invalid\n", s);
	exit(0);
}

void main()
{
	printf("Enter Expression:\n");
	yyparse();
	printf("\nExpression is valid\n");
}
