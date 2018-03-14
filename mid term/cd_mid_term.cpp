//w.a.p. to construct  a miley machine which can produce 2's complement of a given binary string

#include <bits/stdc++.h>
using namespace std;

int main(void){
	FILE *input = freopen("input.txt","r",stdin);
	FILE *output = freopen("output.txt","w",stdout);
	string binaryStr="", outputStr="";
	cin >> binaryStr;
	int len = binaryStr.length();
	int i = len-1;
	//state 0 ==> 0/0
	for(; i >= 0; --i){
		if(binaryStr[i]=='0'){
			outputStr = '0' + outputStr;
			}
		else if(binaryStr[i]=='1'){
			//transition state ==> 1/1
			outputStr = '1' + outputStr;
			i--;
			break;
			}
		}
	
	//state 1 ==> 0/1 or 1/0
	for( ;i >= 0; --i){
		if(binaryStr[i]=='0'){
			outputStr = '1' + outputStr;
			}
		else
			outputStr = '0' + outputStr;
		}
	cout << "2's complement of "<< binaryStr << " : "<<outputStr<<endl;
	return 0;
	}
