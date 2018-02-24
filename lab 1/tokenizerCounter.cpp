#include<iostream>
#include<fstream>
#include<stack>
#include<algorithm>
#include<stdlib.h>
#include<string>

using namespace std;

int lexemePointer=0,cnt=0;
string text;

void parseText(){
	int length = text.length();
    while(lexemePointer<length)
	{
		int flag = 0;
		if(lexemePointer+1 < length)flag = isDoubleOperator();
		if(flag) continue;
		flag = isSingleOperator();
		if(flag) continue;
		flag = checkStringLiteral(length);
		if(flag) continue;
		flag = checkNumber(length);
		if(flag) continue;
		flag = checkName(length);
		if(!flag) lexemePointer++;
	}
}

string input(string file){
    ifstream in;
    in.open(file.c_str());
    string temp,input;
    while(in>>temp)input += temp + " ";
    in.close();
    return input;
}

int isDoubleOperator(){
    string temp = text.substr(lexemePointer,2);
    if(temp == ">=" || temp == "<=" || temp == "==" || temp == "!=" || temp == ">>" ||
       temp == "<<" || temp == "&&" || temp == "||" || temp == "+=" || temp == "-=" ||
       temp == "/=" || temp == "*=" || temp == "%=" || temp == "++" || temp == "--")
    {
        cout<<temp<<endl;
        lexemePointer+=2;
        cnt++;
        return 1;
    }
    return 0;
}

int isSingleOperator(){
    string temp = text.substr(lexemePointer,1);
    if(temp == "+" || temp == "-" || temp == "*" || temp == "/" || temp == "%" ||
       temp == ">" || temp == "<" || temp == "&" || temp == "|" || temp == "^" ||
       temp == "~" || temp == "!" || temp == "=" || temp == "{" || temp == "}" ||
       temp == "[" || temp == "]" || temp == "(" || temp == ")" || temp == "?" ||
       temp == ":" || temp == ";" || temp == ".")
    {
        cout<<temp<<endl;
        lexemePointer++;
        cnt++;
        return 1;
    }
    return 0;
}

int checkStringLiteral(int length){
    string temp = "";
    if(text[lexemePointer] == '"')
    {
        lexemePointer++;
        while(lexemePointer < length)
        {
            if(text[lexemePointer] != '"')
            {

                if(text[lexemePointer] == '\\')
                {
                    temp += '"';
                    lexemePointer+=2;
                }
                else
                {
                    temp+=text[lexemePointer];
                    lexemePointer++;
                }
            }
            else
            {
                lexemePointer++;
                break;
            }
        }
        cout<<temp<<endl;
        cnt++;
        return 1;
    }
    else return 0;
}

int isNumber(char c){
    if(c >= '0' && c <='9') return 1;
    return 0;
}

int isTokenAlphabet(char c){
    if(c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || isNumber(c)) return 1;
    return 0;
}

int checkNumber(int length){
    string temp = "";
    int dotAppeared = 0;
    if(isNumber(text[lexemePointer]))
    {
        temp += text[lexemePointer];
        lexemePointer++;
        while(lexemePointer < length)
        {
            if(text[lexemePointer] != '.')
            {
                if(isNumber(text[lexemePointer]))
                {
                    temp += text[lexemePointer];
                    lexemePointer++;
                }
                else break;
            }
            else if(!dotAppeared)
            {
                temp += text[lexemePointer];
                dotAppeared = 1;
                lexemePointer++;
            }
            else break;
        }
        cout<<temp<<endl;
        cnt++;
        return 1;
    }
    else return 0;
}

int checkName(int length){
    string temp = "";
    if(isTokenAlphabet(text[lexemePointer]))
    {
        temp += text[lexemePointer];
        lexemePointer++;
        while(lexemePointer < length)
        {
            if(isTokenAlphabet(text[lexemePointer]))
            {
                temp += text[lexemePointer];
                lexemePointer++;
            }
            else break;
        }
        cout<<temp<<endl;
        cnt++;
        return 1;
    }
    else return 0;
}

int main(){
    text = input("test.cpp");
    parseText();
    cout<<"Total number of tokens in the program \"test.cpp\" are : "<<cnt<<endl;
    return 0;
}
