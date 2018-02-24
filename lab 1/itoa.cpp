#include <iostream>
#include <string.h>

using namespace std;

void reversestr(char str[], int len)
{
    int begin = 0, end = len -1;
 
    while (begin < end){
        swap(*(str+begin), *(str+end));
        begin++;
        end--;
		}
}

void itoa(int num){
	char str[100];
	int i=0,neg=0;
	
	if(num < 0){
		neg = 1;
		num = -num;
		}
		
	if(num==0){
		str[i++] = '0';
		str[i] = '\0';
		}
		
	while (num != 0){
        int rem = num % 10;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/10	;
		}
		
	if(neg)
		str[i++] = '-';
		
	str[i] = '\0';
	
	reversestr(str,i);
	cout << str << endl;
	cout << strlen(str) << endl;
	}
	
int main(void){
	itoa(-100);
	return 0;
	}
