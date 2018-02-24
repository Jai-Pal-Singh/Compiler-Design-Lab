#include <iostream>
#include <stdio.h>

using namespace std;

int main (void){
	FILE *input = freopen("keywordInput.txt","r",stdin);
	FILE *output = freopen("keywordOutput.txt","w",stdout);
	int i,n;
	char str[20];
	cin >> n;
	while(n--){
		cin >> str;
		if(str[0]=='i' && str[1]=='f' && str[2] == '\0')
			cout << "Valid\n";
		else if(str[0]=='f' && str[1]=='o' && str[2]=='r' && str[3]=='\0')	
			cout << "Valid\n";
		else if(str[0]=='e' && str[1]=='l' && str[2]=='s' && str[3]=='e' && str[4]=='\0')
			cout << "Valid\n";
		else if(str[0]=='w' && str[1]=='h' && str[2]=='i' && str[3]=='l' && str[4]=='e' && str[5]=='\0')
			cout << "Valid\n";
		else
			cout << "Invalid\n";
		}
	fclose(input);
	fclose(output);
	return 0;
	}
