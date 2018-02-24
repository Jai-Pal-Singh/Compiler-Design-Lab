/*write a lex program to count the number of vowels and consonents in a string*/
%option noyywrap
%{
	int vowel=0;
	int consonent=0;
%}
%%
[aeiouAEIOU] vowel++;
[a-zA-Z] consonent++;
[\n] {return 0;}
%%

int main(void){
	printf("Enter a string\n");
	yylex();
	printf("Vowel=%d \n",vowel);
	printf("Consonent=%d \n",consonent);
	return 0;
}
