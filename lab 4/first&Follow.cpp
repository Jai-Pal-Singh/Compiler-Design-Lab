#include <bits/stdc++.h>
using namespace std;

map<string, set<string> > grammar, first, follow, visFollow;
map<string, set<string> >::iterator gr, fi, fo;
map<string, int> visFirst;
string startSymbol;

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
    cout <<non_terminal<<" arrived for computing follow\n";
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
                cout << *st << " already visited\n";
                continue;
            }
            else{                                               //visiting non-terminal first time
                cout <<"visiting "<< *st<<" first time\n";
                visFollow[it->first].insert(*st);
                string s = *st;
                for(int i=0; i<s.length();i++){
                    if(!non_terminal.compare(string(1,s[i]))){
                        cout << "for non-terminal "<<it->first<<endl;
                        set<string> temp;
                        if(i+1==s.length()){                  //
                            cout << s[i]<<" is last element. So calculating follow of "<<it->first<<endl;
                            temp = computeFollow(it->first);
                            follow[non_terminal].insert(temp.begin(),temp.end());
                        }
                        for(int j=i+1;j<s.length();++j){
                            if(s[j]>='a' && s[j]<='z'&& s[j]!='e'){         //checking for terminal
                                cout << s[j] <<" Terminal condition\n";
                                follow[non_terminal].insert(string(1,s[j]));
                                break;
                            }
                            else if(s[j]>='A' && s[j]<='Z'){                //checking for non-terminal
                                cout << s[j] <<" Non-terminal condition\n";
                                set<string> te = computeFirst(string(1,s[j]));
                                set<string>::iterator its;
                                its = te.find("e");
                                if(*its != "e"){
                                    follow[non_terminal].insert(te.begin(),te.end());
                                    continue;
                                }
                                else{
                                    te.erase("e");
                                    for (its=te.begin() ; its!=te.end(); ++its)
                                        cout<<*its<<" , ";
                                    cout<<endl;
                                    follow[non_terminal].insert(te.begin(),te.end());
                                    if(j+1==s.length()){
                                        cout << s[j]<<" is last element. So calculating follow of "<<it->first<<endl;
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
        cout << "\nComputing "<<gr->first<<endl;
        computeFollow(gr->first);
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

int main(void){
	FILE *input = freopen("first&FollowInput.txt","r",stdin);
//	FILE *output = freopen("first&FollowOutput.txt","w",stdout);
	string str;
    cin >> startSymbol;
	while(cin >> str){
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
    cout << "Start Symbol : " << startSymbol << endl;
    displayProduction();
    findFirst();
    displayFirst();
    findFollow();
    displayFollow();
	return 0;
}
