%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "y.tab.h"
%}

digit [0-9]
number {digit}+([.]{digit}+)?

%%

{number} 	{ 
				yylval.floatType = atof(yytext);
				return NUMBER; 
			}

[ \t]+ 		{ }
\n 			{ return 0; }
.			{ return yytext[0]; }

%%

int yywrap()
{
	return 1;
}