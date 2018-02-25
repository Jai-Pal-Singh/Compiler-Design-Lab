#include <bits/stdc++.h>
using namespace std;

map<string, set<string> > grammar;
map<string, set<string> >::iterator gr;
set<string> productions;
set<string>::iterator prodIterator;
vector< vector< pair<string,string> > > items;
vector< vector< pair<string,string> > >::iterator it;
vector< pair<string,string> > closure, vec, quetop;
vector< pair<string,string> >::iterator cl;
string startSymbol;
queue <vector< pair<string,string> > > nextItem;

void displayProduction();
void displayitems();
void computeitems();
vector< pair<string,string> > createItemSet(vector< pair<string,string> > inp);
void findGotoSet(vector< pair<string,string> > inp);

int main(void){
    FILE *input = freopen("lr(0)Input.txt","r",stdin);
	FILE *output = freopen("lr(0)Output.txt","w",stdout);
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
    closure.push_back(make_pair(startSymbol+"'",startSymbol));
    nextItem.push(closure);
    while(!nextItem.empty()){
        int itemAlreadyExist = 0;
		quetop = nextItem.front();
        closure = createItemSet(nextItem.front());
        for(it = items.begin(); it != items.end(); it++){
            if(closure == *it){
                itemAlreadyExist = 1;
            }
        }
        if(itemAlreadyExist==0){
            items.push_back(closure);
			findGotoSet(closure);
        }
        nextItem.pop();
    }
}

vector< pair<string,string> > createItemSet(vector< pair<string,string> > inp){
	string visited = "";
    for(int k = 0 ; k < inp.size(); k++){
        string str = inp[k].second;
        int i = str.find(".");
        if(i==str.npos){                        //. not found. Starting condition
            inp[k].second = "."+str;
            str = inp[k].second;
            i=1;
        }
        else if(i+1==str.length()){          //. at the end of production
            continue;
        }
        else{                              //. in middle of string, Advancing .
            str[i] = str[i+1];
            str[i+1] = '.';
            inp[k].second = str;
			i += 2;
        }
        if(str[i]=='e'){                    //epsilon condition
            str.erase(i);
            inp[k].second = str;
            continue;
        }
        else if(str[i]>='a'&&str[i]<='z'&&str[i]!='e'){             //terminal condition
			continue;
        }
        else if(str[i]>='A'&&str[i]<='Z'&&str[i]!='e'){             //non-terminal condition
            gr = grammar.find(string(1,str[i]));
            if(gr == grammar.end()){
                cout << "Error : " << str[i] <<" is not presented in grammar.\n";
                break;
            }
			int l = visited.find(str[i]);
            if(visited[l]== str[i]){
                continue;
            }
            visited.push_back(str[i]);
            productions = gr->second;
            for(prodIterator = productions.begin(); prodIterator != productions.end(); ++prodIterator){
                pair<string, string> p = make_pair(gr->first,*prodIterator);
                inp.push_back(p);
            }
        }
    }
    return inp;
}

void findGotoSet(vector< pair<string,string> > inp){
    string visited = "";
    for(int i=0; i<inp.size(); i++){
        vec.clear();
        string s1 = inp[i].second;
        int pos1 = s1.find(".");
        int l = visited.find(s1[pos1+1]);
		if(pos1+1==s1.length()){
			continue;
		}
        if(visited[l]== s1[pos1+1]){
            continue;
        }
        visited.push_back(s1[pos1+1]);
        vec.push_back(make_pair(inp[i].first,inp[i].second));
        for(int j=i+1; j<inp.size(); j++){
            string s2 = inp[j].second;
            int pos2 = s2.find(".");
            if(s1[pos1+1]==s2[pos2+1]){
                vec.push_back(make_pair(inp[j].first,inp[j].second));
            }
        }
        nextItem.push(vec);
    }
}
