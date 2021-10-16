#include <bits/stdc++.h>

using namespace std;


void printMap(vector< pair<string,vector<string>> > positions){
    for (int i=0; i<positions.size(); i++) {
        string key = positions[i].first;
        vector<string> value = positions[i].second;
        cout << key << ": ";
        for(int i=0; i<value.size(); i++){
            cout << value[0] << ' ';
        }
        cout << endl;
    }
}


// rank and file (row, col)
char board[7][7];

void printBoard(){
    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            cout << board[i][j];
            cout << ' ';
        }
        cout << endl;
    }
}

bool isBlack(char c){
    if(c==toupper(c)){
        return false;
    }
    return true;
}

vector<string> splitString(string str, char del){
    vector<string> res;
    string temp = "";

    for(int i=0; i<str.size(); i++){
        if(str[i]!=del){
            temp += str[i];
        }
        else{
            res.push_back(temp);
            temp = "";
        }
    }
    res.push_back(temp);
    return res;
}

void printContentsOfVector(vector<string> vec){
    for(int i=0; i<vec.size(); i++){
        cout << vec[i] << endl;
    }
}

bool isNumber(char c){
    vector<char> v = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    if(count(v.begin(), v.end(), c)){
        return true;
    }
    return false;
}

void putIntoBoard(string input){
    vector<string> splitBySlash = splitString(input, '/');
    for(int i=0; i<splitBySlash.size(); i++){
        string rank = splitBySlash[i];
        for(int j=0; j<rank.size(); j++){
            if(isNumber(rank[j])){
                int number = rank[j]-'0';
                for(int k=0; k<number; k++){
                    board[i][k] = '#';
                }
            }
            else{
                board[i][j] = rank[j];
            }
        }
    }
    printBoard();
}

void updateDict(vector< pair<string,vector<string>> > &result, int index, string coord){
    vector<string> v = result[index].second;
    v.push_back(coord);
    sort(v.begin(), v.end());
    result[index].second = v;
}

void handleBlack(vector< pair<string,vector<string>> > &result, char c, string coord){
    if(c=='p'){
        updateDict(result, 1, coord);
    }
    else if(c=='g'){

    }
    else if(c=='m'){

    }
    else if(c=='e'){
        
    }
    else if(c=='l'){
        
    }
    else if(c=='c'){
        
    }
    else if(c=='z'){
        
    }
}

char to_alphabet(int n)
{
    assert(n >= 1 && n <= 26)
    return "abcdefghijklmnopqrstuvwxyz"[n-1];
}

vector< pair<string,vector<string>> > putIntoDict(){
    vector<string> v;
    vector< pair<string,vector<string>> > result = {
        {"white pawn", v}, {"black pawn", v}, {"white superpawn", v}, {"black superpawn", v},
        {"white giraffe", v}, {"black giraffe", v}, {"white monkey", v}, {"black monkey", v},
        {"white elephant", v}, {"black elephant", v}, {"white lion", v}, {"black lion", v},
        {"white crocodile", v}, {"black crocodile", v}, {"white zebra", v}, {"black zebra", v}
    };

    for(int row=0; row<7; row++){
        for(int col=0; col<7; col++){
            char c = board[row][col];
            string coord = to_alphabet(col) + to_string(row);
            if(isBlack(c)){
                handleBlack(result, c, coord);
            }
            else{
                handleWhite(result, c, coord);
            }
        }
    }

    return result;
}

void getStateInput(){
    // int numberOfFENStrings;
    // vector<string> FENStrings;
    // string temp;

    // getline(cin, temp);
    // numberOfFENStrings = stoi(temp);

    // for(int i=0; i<numberOfFENStrings; i++){
    //     string s;
    //     getline(cin, s);
    //     vector<string> temp = splitString(s, ' ');
    //     FENStrings.push_back(temp[0]);
    // }
    
    // for(int i=0; i<FENStrings.size(); i++){
    //     string FENString = FENStrings[i];
    //     putIntoBoard(FENString);
    // }
    vector< pair<string,vector<string>> > positions = putIntoDict();
    printMap(positions);
}