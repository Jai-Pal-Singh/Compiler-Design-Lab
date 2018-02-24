//Write a program to develop Lexical Analyzer which can tokenise and identify the category of token.

#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<stack>
#include<algorithm>

using namespace std;

int lexemePointer=0;
int cnt=0;
string text;

string mapping[39][2]={
	{">=","Greater Than Equal To"},
	{"<=","Less Than Equal To"},
	{"==","Equal To Equal To"},
	{"!=","Not Equal To"},
	{">>","Right Shift"},
	{"<<","Left Shift"},
	{"&&","AND"},
	{"||","OR"},
	{"+=","Plus Assignment"},
	{"-=","Minus Assignment"},
	{"/=","Divide Assignment"},
	{"*=","Multiply Assignment"},
	{"%=","Modulus Assignment"},
	{"++","Increment"},
	{"--","Decrement"},
	{"+","Addition"},
	{"-","Subtraction"},
	{"/","Divide"},
	{"*","Multiply"},
	{"%","Modulo"},
	{">","Greater Than"},
	{"<","Less Than"},
	{"&","Bitwise AND"},
	{"|","Bitwise OR"},
	{"^","Exponent"},
	{"~","Bitwise Negation"},
	{"!","NOT"},
	{"=","Assignment"},
	{"?","Question Mark"},
	{":","Colon"},
	{";","Semi-Colon"},
	{".","Dot"},
	{"{","Opening Curly Bracket"},
	{"}","Closing Curly Bracket"},
	{"(","Opening Parenthesis"},
	{")","Closing Parenthesis"},
	{"[","Opening Square Bracket"},
	{"]","Closing Square Bracket"},
    {"->","Reference Arrow"}
};

int isNumber(char c){
    if(c >= '0' && c <='9') return 1;
    return 0;
}

int isTokenAlphabet(char c){
    if(c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || isNumber(c)) return 1;
    return 0;
}

string readInput(string filename)
{
    ifstream in;
    in.open(filename.c_str());
    string temp,input;
    while(in>>temp)input += temp + " ";
    in.close();
    return input;
}

void outputTokenAndType(string temp)
{
	for(int i=0;i<39;i++)
	{
		if(temp == mapping[i][0])
		{
			cout<<temp<<" is "<<mapping[i][1]<<"."<<endl;
			return;
		}
	}
	if(temp[0] == '"')
	{
		cout<<temp<<" is a String Literal."<<endl;
		return;
	}
	int length = temp.length(),floatflag = 0;
	for(int i=0;i<length;i++)
	{
		if(!isNumber(temp[i]) || temp[i] == '_')
		{
		    if(temp[i] == '.')
            {
                floatflag = 1;
                break;
            }
			cout<<temp<<" is a Identifier Name."<<endl;
			return;
		}
	}
	if(floatflag == 1) cout<<temp<<" is a Float Literal."<<endl;
    else cout<<temp<<" is a Integer Literal."<<endl;
}

int isDoubleOperator()
{
    string temp = text.substr(lexemePointer,2);
    if(temp == ">=" || temp == "<=" || temp == "==" || temp == "!=" || temp == ">>" ||
       temp == "<<" || temp == "&&" || temp == "||" || temp == "+=" || temp == "-=" ||
       temp == "/=" || temp == "*=" || temp == "%=" || temp == "++" || temp == "--" ||
	   temp == "->")
    {
        outputTokenAndType(temp);
        lexemePointer+=2;
        cnt++;
        return 1;
    }
    return 0;
}

int isSingleOperator()
{
    string temp = text.substr(lexemePointer,1);
    if(temp == "+" || temp == "-" || temp == "*" || temp == "/" || temp == "%" ||
       temp == ">" || temp == "<" || temp == "&" || temp == "|" || temp == "^" ||
       temp == "~" || temp == "!" || temp == "=" || temp == "{" || temp == "}" ||
       temp == "[" || temp == "]" || temp == "(" || temp == ")" || temp == "?" ||
       temp == ":" || temp == ";" || temp == ".")
    {
        outputTokenAndType(temp);
        lexemePointer++;
        cnt++;
        return 1;
    }
    return 0;
}

int checkStringLiteral(int length)
{
    string temp = "\"";
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
		temp += "\"";
        outputTokenAndType(temp);
        cnt++;
        return 1;
    }
    else return 0;
}

int checkNumber(int length)
{
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
        outputTokenAndType(temp);
        cnt++;
        return 1;
    }
    else return 0;
}

int checkName(int length)
{
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
        outputTokenAndType(temp);
        cnt++;
        return 1;
    }
    else return 0;
}

void parseText(){
	int length = text.length();
    while(lexemePointer<length)	{
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

int main(void){
    text = readInput("test.cpp");
    parseText();
    cout<<"Total number of tokens in the program \"test.cpp\" are : "<<cnt<<endl;
    return 0;
}
