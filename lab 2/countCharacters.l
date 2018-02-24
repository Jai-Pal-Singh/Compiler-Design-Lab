/*write a lex program to count the number of characters in a string*/

%{
	int count=0;
%}
%%
[a-zA-Z] count++;
[\n] {return count;}
%%

int main(void){
	printf("Enter a string\n");
	yylex();
	printf("Count=%d \n",count);
	return 0;
}
