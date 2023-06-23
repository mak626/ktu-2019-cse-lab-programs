/* https://stackoverflow.com/questions/28247979/lex-flex-regular-expression-for-string-literals-in-c-c */
/* lex exp6.l && gcc lex.yy.c && ./a.out input.c > output.txt */

%{
    #include<stdio.h>

    void print_output(char *yytext, char* str)
    {
        printf("%25s | %-s\n",str, yytext);
    }
%}

preprocessor #.*
identifier [_a-zA-Z][_a-zA-Z0-9]*
keyword (int|float|char|double|while|for|do|if|break|continue|void|switch|case|long|struct|const|typedef|return|else|goto)
multi_comment \/\*.*\*\/
single_comment \/\/.*
comment {multi_comment}|{single_comment}
function {identifier}[ ]+\(
string \"(\\.|[^\\"])*\"
digit [0-9]
char \'.{1,2}\'
op \+|-|\*|\/|=|%
number [-+]?{digit}+[.]?{digit}+([eE][-+]?{digit}+)?
relation_op \<=|\>=|\<|==|\>|!=
brack_open \{
brack_close \}
anything_else \n|.

%%

{preprocessor} { print_output(yytext,"PREPROCESSOR DIRECTIVE"); }
{comment} { print_output(yytext,"COMMENT"); }
{keyword} { print_output(yytext,"KEYWORD"); }
{identifier} { print_output(yytext,"IDENTIFIER"); }

{number} { print_output(yytext,"NUMBER"); }
{char} { print_output(yytext,"CHARACTER"); }
{string} { print_output(yytext,"STRING"); }

{function} { print_output(yytext,"FUNCTION"); }

{brack_open} { print_output(yytext, "BLOCK BEGINS"); }
{brack_close} { print_output(yytext,"BLOCK ENDS"); }

{op} {print_output(yytext,"OPERATOR");}
{relation_op} { print_output(yytext,"RELATIONAL OPERATOR");}

{anything_else} {}

%%

int yywrap()
{
    return 1;
}

int main(int argc,char **argv)
{   
    if(argc !=2)
    {
        printf("No file name given");
        printf("\nSyntax ./a.out <filename>\n");
    }
    else
    {
        FILE *file;
        file = fopen(argv[1],"r");

        if(!file)
        {
            printf("Could not open %s \n",argv[1]);
            return 0;
        }

        yyin = file;
        yylex();
    }
    
    return 0;
}