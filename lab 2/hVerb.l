/*write a lex program to find if the letter is helping verb or not*/
%option noyywrap
%%
[\t]+
is |
are |
am |
was |
were {printf("%s : is a valid helping verb",yytext);}
[a-z A-Z]+ {printf("%s : is an invalid helping verb",yytext);}
	
%%
int main(void){
	yylex();
	return 0;
	}
