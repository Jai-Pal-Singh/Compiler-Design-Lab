#include <bits/stdc++.h>
using namespace std;

map<string, set<string> > grammar, first, follow, visFollow;
map<string, set<string> >::iterator gr, fi, fo;
map<string, int> visFirst;
map<string, map<string, set<string> > > predectiveTable;
map<string, map<string, set<string> > >::iterator pr;
string startSymbol,checkString="";
bool error=0;

set<string> computeFirst(string non_terminal){
  if(visFirst[non_terminal]==1){                            //non-terminal already visited
    return first.find(non_terminal)->second;
  }
  else{
    visFirst[non_terminal]=1;                               //visiting non-terminal first time
    gr = grammar.find(non_terminal);
    set<string> str = gr->second;
    set<string>::iterator st = str.begin();
    for(;st!=str.end();++st){
        string s = *st;
        for(int i=0;i<s.length();++i){
            if(s[i]>='a' && s[i]<='z' && s[i]!='e'){          //checking for terminal
                first[non_terminal].insert(string(1,s[i]));
                break;
            }
            else if(s[i]=='e'){                                   //checking for epsilon
                first[non_terminal].insert(string(1,s[i]));
                break;
            }
            else if(s[i]>='A' && s[i]<='Z'){                    //checking for non-terminal
                set<string> temp = computeFirst(string(1,s[i]));

                set<string>::iterator te ;
                te = temp.find("e");
                if(te != temp.end() && i+1!=s.length()){
                    temp.erase("e");
                    first[non_terminal].insert(temp.begin(),temp.end());
                }
                else{
                    first[non_terminal].insert(temp.begin(),temp.end());
                    break;
                }
            }
        }
    }
    return first.find(non_terminal)->second;
  }
}

void findFirst(){
    visFirst.clear();
    for(gr = grammar.begin();gr!=grammar.end();gr++){           //iterating to find first for each non-terminal
        visFirst[gr->first]=0;
        computeFirst(gr->first);
    }

}

set<string> computeFollow(string non_terminal){
    if(follow.find(non_terminal)!=follow.end()){                            //non-terminal already visited
        return follow.find(non_terminal)->second;
      }
    if(non_terminal==startSymbol)
        follow[startSymbol].insert("$");
    for(map<string, set<string> >::iterator it=grammar.begin();it != grammar.end(); ++it){
        set<string> str = it->second;
        set<string>::iterator st = str.begin();
        for(;st!=str.end();++st){
            if(visFollow[it->first].find(*st)==str.end()){                              //non-terminal already visited
                continue;
            }
            else{                                               //visiting non-terminal first time
                visFollow[it->first].insert(*st);
                string s = *st;
                for(int i=0; i<s.length();i++){
                    if(!non_terminal.compare(string(1,s[i]))){
                        set<string> temp;
                        if(i+1==s.length()){
                            temp = computeFollow(it->first);
                            follow[non_terminal].insert(temp.begin(),temp.end());
                        }
                        for(int j=i+1;j<s.length();++j){
                            if(s[j]>='a' && s[j]<='z'&& s[j]!='e'){         //checking for terminal
                                follow[non_terminal].insert(string(1,s[j]));
                                break;
                            }
                            else if(s[j]>='A' && s[j]<='Z'){                //checking for non-terminal
                                set<string> te = computeFirst(string(1,s[j]));
                                set<string>::iterator its;
                                its = te.find("e");
                                if(*its != "e"){
                                    follow[non_terminal].insert(te.begin(),te.end());
                                    continue;
                                }
                                else{
                                    te.erase("e");
                                    follow[non_terminal].insert(te.begin(),te.end());
                                    if(j+1==s.length()){
                                        te = computeFollow(it->first);
                                        follow[non_terminal].insert(te.begin(),te.end());
                                    }
                                }
							}
                        }
                    }
                }
            }
        }
    }
    return follow.find(non_terminal)->second;
}

void findFollow(){
    visFollow.clear();
    computeFollow(startSymbol);
    for(gr = grammar.begin();gr!=grammar.end();gr++){           //iterating to find follow for each non-terminal
        for(map<string, set<string> >::iterator it=grammar.begin();it != grammar.end(); ++it){
            set<string> str = it->second;
            set<string>::iterator st = str.begin();
            for(;st!=str.end();++st){
                visFollow[it->first].insert("0");
            }
        }
        computeFollow(gr->first);
    }
}
void insertInTable(string row, string prod, string col){
    string temp="";
    set<string> tempStr;
    map<string, set<string> > tempMap;
    temp = row+" -> "+prod;
    predectiveTable[row][col].insert(temp);
}

void findPredectiveTable(){
    for(gr = grammar.begin(); gr != grammar.end(); ++gr){
        set<string> stringSet = gr->second;
        set<string>::iterator st;
        for(st = stringSet.begin(); st != stringSet.end(); ++st){
            string str = *st;
            set<string>::iterator te,fit,fs,ff;
            for(int i=0;i<str.length();++i){
                if(str[i]>='a' && str[i]<='z'&& str[i]!='e'){
                    insertInTable(gr->first, str, string(1,str[i]));
                    break;
                }
                else if(str[i]=='e'){
                    fo = follow.find(gr->first);
                    set<string> followSet = fo->second;
                    for(ff = followSet.begin(); ff!=followSet.end();++ff){
                        insertInTable(gr->first,"e",*ff);
                    }
                }
                else if(str[i]>='A' && str[i]<='Z'){
                    fi = first.find(string(1,str[i]));
                    set<string> firstSet = fi->second;
                    for(fs = firstSet.begin(); fs != firstSet.end(); ++fs){
                        if(*fs>="a" && *fs<="z"&& *fs!="e"){
                            insertInTable(gr->first,str,*fs);
                        }
                        else if(*fs == "e"){
                            continue;
                        }
                    }
                    fs = firstSet.find("e");
                    if(fs == firstSet.end() )
                        break;
                }
            }
        }
    }
}

void findStringAceptance(){
    if(error == 1){
        cout << "String acceptance can't be checked\n";
        return;
    }
    stack<string> myStack;
    string::iterator it,ipIt = checkString.begin();
    set<string> prod;
    set<string>::iterator pr;
    string row = startSymbol;
    myStack.push("$");
    myStack.push(startSymbol);
    while(ipIt!=checkString.end()){
        row = myStack.top();
        if(myStack.top()!= string(1,*ipIt) && myStack.top()!="e"){
            prod = predectiveTable[row][string(1,*ipIt)];
            myStack.pop();
            for(pr = prod.begin(); pr != prod.end(); ++pr){
                string s = *pr;
                for(int j = s.length()-1; j>=0; j--){
                    if(s[j]==' ')
                        break;
                    myStack.push(string(1,s[j]));
                }
            }
        }
        else if(myStack.top() == string(1,*ipIt) ){
            ipIt++;
            myStack.pop();
        }
        else if(myStack.top() == "e"){
            myStack.pop();
        }
    }
    if(myStack.empty())
        cout << "String Accepted\n";
    else
        cout << "String Rejected\n";
}

void displayProduction(){
    cout << "\nProductions :\n";
    for (gr=grammar.begin(); gr!=grammar.end(); ++gr){
        cout << gr->first << " -> ";
        set<string> temp = gr->second;
        set<string>::iterator it1 = temp.begin();
        cout << *it1 ;
        for (++it1 ; it1!=temp.end(); ++it1)
            cout <<" | "<< *it1 ;
        cout << endl;
    }
}

void displayFirst(){
    cout << "\nFIRST : \n";
    for (fi=first.begin(); fi!=first.end(); ++fi){
        cout << fi->first << " = {";
        set<string> temp = fi->second;
        set<string>::iterator it1 = temp.begin();
        cout << *it1 ;
        for (++it1 ; it1!=temp.end(); ++it1)
            cout <<" , "<< *it1 ;
        cout << "}\n";
    }
}

void displayFollow(){
    cout << "\nFOLLOW : \n";
    for (fo=follow.begin(); fo!=follow.end(); ++fo){
        cout << fo->first << " = {";
        set<string> temp = fo->second;
        set<string>::iterator it1 = temp.begin();
        cout << *it1 ;
        for (++it1 ; it1!=temp.end(); ++it1)
            cout <<" , "<< *it1 ;
        cout << "}\n";
    }
}

void displayPredectiveTable(){
    cout << "\nPredective Parsing Table : \n";
    for(pr = predectiveTable.begin(); pr != predectiveTable.end(); ++pr){
        map<string, set<string> > tempMap = pr->second;
        for(gr = tempMap.begin(); gr != tempMap.end(); gr++){
            set<string> tempString = gr->second;
            if(tempString.size()>1)
                error = 1;
            set<string>::iterator te = tempString.begin();
            cout << "M["<<pr->first<<" , "<<gr->first<<"] = "<< *te;
            for(te++ ; te != tempString.end(); te++){
               cout << " , " << *te;
            }
            cout << endl;
        }
    }
    if(error == 1)
        cout << "\nGiven grammar is not LL1\n";
    else
        cout << "\nGiven grammar is LL1\n";
}

int main(void){
	FILE *input = freopen("stringAcceptanceInput.txt","r",stdin);
	FILE *output = freopen("stringAcceptanceOutput.txt","w",stdout);
	string str;
	int inputLength;
    cin >> startSymbol;
    cin >> inputLength;
	while(inputLength--){
        cin >> str;
		int pos=str.find("->");
		string non_terminal = str.substr(0,pos);
		string production = "";
		set<string> temp;
		for(int i=pos+2;i<str.length();i++){
            if(str.at(i)=='|'){
                temp.insert(production);
                production="";
            }
            else
                production.push_back(str.at(i));
		}
		temp.insert(production);
		grammar.insert(make_pair(non_terminal,temp));
    }
    cin >> checkString;
    cout << "Start Symbol : " << startSymbol << endl;
    cout << "String to check for acceptability : "<< checkString<<endl;
    displayProduction();
    findFirst();
    displayFirst();
    findFollow();
    displayFollow();
    findPredectiveTable();
    displayPredectiveTable();
    findStringAceptance();
	return 0;
}
