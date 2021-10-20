#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

vector<char> whitePieces = {'l', 'p', 'z', 'e'};
vector<char> blackPieces = {'L', 'P', 'Z', 'E'};

vector<vector<char>> board = {
    {'#','#','e','l','e','#','z'},
    {'p','p','p','p','p','p','p'},
    {'#','#','#','#','#','#','#'},
    {'#','#','#','#','#','#','#'},
    {'#','#','#','#','#','#','#'},
    {'P','P','P','#','P','P','P'},
    {'#','#','E','L','E','#','Z'}
};

bool isBlack(char c){
    if(c==toupper(c)){
        return false;
    }
    return true;
}

bool isTeamMate(){
    char myPiece = board[6][3];
    char space = board[6][4];
    cout << myPiece << endl;
    cout << space << endl;
    if(space=='#'){
        return false;
    }
    if(isBlack(myPiece)){
        if(!(find(blackPieces.begin(), blackPieces.end(), space) != blackPieces.end())){
            return true;
        }
    }
    else{
        if(!(find(whitePieces.begin(), whitePieces.end(), space) != whitePieces.end())){
            return true;
        }
    }

    return false;
}

int main()
{
    cout<< isTeamMate();

    return 0;
}
