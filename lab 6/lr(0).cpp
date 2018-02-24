#include <bits/stdc++.h>
using namespace std;

map<string, set<string> > grammar;
map<string, set<string> >::iterator gr;
set<string> productions;
set<string>::iterator prodIterator;
vector< vector< pair<string,string> > > items;
vector< vector< pair<string,string> > >::iterator it;
vector< pair<string,string> > closure;
vector< pair<string,string> >::iterator cl;
string startSymbol;
void displayProduction();
void displayitems();
void computeitems();

int main(void){
    FILE *input = freopen("lr(0)Input.txt","r",stdin);
//	FILE *output = freopen("lr(0)Output.txt","w",stdout);
    int inputLength, terLen;
    string str;
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
            else{
                production.push_back(str.at(i));
            }
		}
		temp.insert(production);
		grammar.insert(make_pair(non_terminal,temp));
    }
    cout << "Start symbol : "<<startSymbol<<endl;
    displayProduction();
    computeitems();
    displayitems();
    return 0;
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

void displayitems(){
    cout << "\nItems : \n";
    int i=0;
    for(it=items.begin(); it!=items.end() ; ++i, ++it){
        cout << "\nItem "<<i<<" => \n";
        closure = *it;
        for(cl=closure.begin(); cl!=closure.end(); ++cl){
            cout << cl->first << " -> " << cl->second <<endl;
        }
    }
}

void computeitems(){
    it = items.begin();
    cl = closure.begin();
    cl = closure.insert(cl, make_pair(startSymbol+"`","."+startSymbol));
    it = items.insert(it, closure);
}
