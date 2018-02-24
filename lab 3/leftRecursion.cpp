#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main (void){
	FILE *input = freopen("leftRecursionInput.txt","r",stdin);
	FILE *output = freopen("leftRecursionOutput.txt","w",stdout);
	string str;
	int count=0,i=0;
	char *ss,productions[15][30];
	while(cin>>productions[i]){
		int j=0,hasRecursion = 0;
		char *prod[5];
		for(int k=0; k<5; k++)
			prod[k] = NULL;
		ss = strtok(productions[i], "->");
		char* temp = strtok(NULL, "->");
		prod[j] = strtok(temp, "|");
		
		while (prod[j] != NULL){
			if(prod[j][0] == '^'){
				prod[j] = NULL;
			}
			if(prod[j][0] == ss[0]){
				 hasRecursion = 1;
				 prod[j] += 1;
				 cout<<ss<<"->"<<prod[j]<<ss<<'\''<<endl;
				 cout<<ss<<'\''<<"->"<<"NULL"<<endl;	
				 prod[j] = NULL;
			}	
			prod[++j] = strtok(NULL, "|");
		}
		
		if(hasRecursion){
			for(int k=0; k<5; k++){
				if(prod[k]){		
					cout<<ss<<'\''<<"->"<<prod[k]<<ss<<'\''<<"\n";
				}
			}
		}
		else if(!hasRecursion){
			for(int k=0; k<5; k++)
				if(prod[k])
					cout<<ss<<"->"<<prod[k]<<"\n";
		}
		cout<<endl;
		i++;
		}
	fclose(input);
	fclose(output);
	return 0;
}
