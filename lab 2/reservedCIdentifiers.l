/*write a lex program to identify the reserved identifiers in c*/

%%
auto |
break |
case |
char |
const |
continue |
default |
do |
double |
else |
enum |
extern |
float |
for |
goto | 
if |
int |
long |
register |
return |
short |
signed |
sizeof |
static |
struct |
switch |
typedef |
union |
unsigned |
void |
volatile |
while {printf("%s : is a valid reserved word in c",yytext);}
[_a-zA-Z][_a-zA-Z0-9_]*+ {printf("%s : is a valid identifier in c",yytext);}
.* {printf("%s : is an invalid identifier in c",yytext);}
%%
int main(void){
	yylex();
	return 0;
	}
