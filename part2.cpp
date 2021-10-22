#include <bits/stdc++.h>
#include "part1.cpp"

using namespace std;

int boardIndex;

vector<char> whitePieces = {'l', 'p', 'z', 'e'};
vector<char> blackPieces = {'L', 'P', 'Z', 'E'};

vector<pair<int, int>> lionPossibleMoves = {{1,0}, {0,1}, {-1,0}, {0,-1}, {1,1}, {-1,-1}, {1,-1}, {-1,1}};
vector<pair<int, int>> zebraPossibleMoves = {{2,1}, {2,-1}, {-2,1}, {-2,-1}, {1,2}, {-1,2}, {1,-2}, {-1,-2}};
vector<pair<int, int>> elephantPossibleMoves = {{1,0}, {0,1}, {-1,0}, {0,-1}, {2,0}, {0,2}, {-2,0}, {0,-2}};
vector<pair<int, int>> blackPawnPossibleMoves = {{1,0}, {1,1}, {1,-1}};
vector<pair<int, int>> superBlackPawnPossibleMoves = {{1,0}, {1,1}, {1,-1}, {-1,0}, {-2,0}};
vector<pair<int, int>> whitePawnPossibleMoves = {{-1,0}, {-1,-1}, {-1,1}};
vector<pair<int, int>> superWhitePawnPossibleMoves = {{-1,0}, {-1,-1}, {-1,1}, {1,0}, {2,0}};

void printVector(vector<string> v){
    for(int i=0; i<v.size(); i++){
        cout<< v[i] << ' ';
    }
    cout<<endl;
}

int alphabetToInt(char c)
{
    string s = "abcdefghijklmnopqrstuvwxyz";
    int number = 0;
    for(int i=0; i<s.size(); i++){
        if(s[i]==c){
            return number+1;
        }
        number++;
    }
    return -1;
}

char to_alphabet(int n)
{
    assert(n >= 0 && n <= 25);
    return "abcdefghijklmnopqrstuvwxyz"[n];
}

pair<int, int> convertCoordinates(string coord){
    pair<int, int> res;
    res.first = abs((coord[1] - '0')-7);
    res.second = alphabetToInt(coord[0]) -1;
    return res;
}

bool isInBounds(pair<int, int> pos){
    if(pos.first>=0 && pos.first<7 && pos.second>=0 && pos.second<7){
        return true;
    }
    return false;
}

bool lionIsInBounds(pair<int, int> pos){
    int row = pos.first;
    int col = pos.second;
    if(col>1&&col<5){
        if(row!=3 && row>-1 && row<7){
            return true;
        }
    }
    return false;
}

bool isBlack(char c){
    if(c==toupper(c)){
        return false;
    }
    return true;
}

bool isTeamMate(pair<int, int> me, pair<int, int> otherPiece){
    char myPiece = boards[boardIndex][me.first][me.second];
    char space = boards[boardIndex][otherPiece.first][otherPiece.second];
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

string coordinatesToString(string coord, int col, int row){
    // cout<<"error here: "<<col<<endl;
    string temp = coord + to_alphabet(col) + to_string(abs(row-7));
    // cout<< row << ',' << col << ": " << temp << endl;
    return temp;
}

bool isEmpty(pair<int, int> pos){
    return boards[boardIndex][pos.first][pos.second] == '#';
}

bool otherLionIsOpen(){
    string whiteLion;
    string blackLion;
    vector<string> res = splitString(positions[boardIndex][4], ' ');
    whiteLion = res[2];
    res = splitString(positions[boardIndex][5], ' ');
    blackLion = res[2];
    // cout<<whiteLion<<endl;
    // cout<<blackLion<<endl;
    pair<int, int> posWhite = convertCoordinates(whiteLion);
    pair<int, int> posBlack = convertCoordinates(blackLion);
    if(posWhite.second==posBlack.second){
        for(int i=posBlack.first+1; i<posWhite.first; i++){
            if(!isEmpty({i, posBlack.second})){
                // cout<<posBlack.first<<','<<posBlack.second<<endl;
                return false;
            }
        }
    }
    else{
        return false;
    }
    return true;
}

bool isDiagonal(){
    if(boards[boardIndex][3][3]=='#' && tolower(boards[boardIndex][4][2])=='l' && tolower(boards[boardIndex][2][4])=='l'){
        return true;
    }
    else if(boards[boardIndex][3][3]=='#' && tolower(boards[boardIndex][2][2])=='l' && tolower(boards[boardIndex][4][4])=='l'){
        return true;
    }
    return false;
}

vector<string> lionMoves(){
    // TODO: take care of situation when other lion is open
    string coord;
    string otherLion;
    vector<string> res;
    if(turn[boardIndex][0]=='b'){
        coord = splitString(positions[boardIndex][5], ' ')[2];
        res = splitString(positions[boardIndex][4], ' ');
        if (res.size()>2)
        {
            otherLion = res[2];
        }
    }
    else{
        coord = splitString(positions[boardIndex][4], ' ')[2];
        res = splitString(positions[boardIndex][5], ' ');
        if (res.size()>2)
        {
            otherLion = res[2];
        }
    }
    pair<int, int> pos = convertCoordinates(coord);
    // cout<< pos.first << ',' << pos.second << endl;
    vector<string> moves;
    for(int i=0; i<lionPossibleMoves.size(); i++){
        pair<int, int> newMove = {pos.first+lionPossibleMoves[i].first, pos.second+lionPossibleMoves[i].second};
        if(lionIsInBounds(newMove)){
            if(!isTeamMate(pos, newMove)){
                moves.push_back(coordinatesToString(coord, newMove.second, newMove.first));
            }
        }
    }
    if(res.size()>2){
        if(otherLionIsOpen()){
            moves.push_back(coord+otherLion);
        }
        else if(isDiagonal()){
            moves.push_back(coord+otherLion);
        }
    }
    sort(moves.begin(), moves.end());
    return moves;
}

vector<string> zebraMoves(){
    string coord;
    vector<string> res;
    if(turn[boardIndex][0]=='b'){
        res = splitString(positions[boardIndex][7], ' ');
        if(res.size()<3){
            return {};
        }
        coord = res[2];
    }
    else{
        res = splitString(positions[boardIndex][6], ' ');
        if(res.size()<3){
            return {};
        }
        coord = res[2];
    }
    pair<int, int> pos = convertCoordinates(coord);
    // cout<< pos.first << ',' << pos.second << endl;
    vector<string> moves;
    for(int i=0; i<zebraPossibleMoves.size(); i++){
        pair<int, int> newMove = {pos.first+zebraPossibleMoves[i].first, pos.second+zebraPossibleMoves[i].second};
        if(isInBounds(newMove)){
            if(!isTeamMate(pos, newMove)){
                // cout<<newMove.first <<','<< newMove.second<<endl;
                moves.push_back(coordinatesToString(coord, newMove.second, newMove.first));
            }
        }
    }
    sort(moves.begin(), moves.end());
    return moves;
}

vector<string> elephantMoves(){
    vector<string> coords;
    if(turn[boardIndex][0]=='b'){
        vector<string> res = splitString(positions[boardIndex][3], ' ');
        for(int i=2; i<res.size(); i++){
            coords.push_back(res[i]);
        }
    }
    else{
        vector<string> res = splitString(positions[boardIndex][2], ' ');
        for(int i=2; i<res.size(); i++){
            coords.push_back(res[i]);
        }
    }

    vector<string> moves;
    for(int k=0; k<coords.size(); k++){
        string coord = coords[k];
        pair<int, int> pos = convertCoordinates(coord);
        // cout<< pos.first << ',' << pos.second << endl;
        for(int i=0; i<elephantPossibleMoves.size(); i++){
            pair<int, int> newMove = {pos.first+elephantPossibleMoves[i].first, pos.second+elephantPossibleMoves[i].second};
            if(isInBounds(newMove)){
                if(!isTeamMate(pos, newMove)){
                    moves.push_back(coordinatesToString(coord, newMove.second, newMove.first));
                }
            }
        }
    }
    
    sort(moves.begin(), moves.end());
    return moves;
}


vector<string> blackPawnMoves(){
    vector<string> coords;

    vector<string> res = splitString(positions[boardIndex][1], ' ');
    if(res.size()<3){
        return {};
    }
    for(int i=2; i<res.size(); i++){
        coords.push_back(res[i]);
    }

    vector<string> moves;
    for(int k=0; k<coords.size(); k++){
        string coord = coords[k];
        pair<int, int> pos = convertCoordinates(coord);
        // cout<< pos.first << ',' << pos.second << endl;
        if(pos.first>3){
            for(int i=0; i<superBlackPawnPossibleMoves.size(); i++){
                pair<int, int> newMove = {pos.first+superBlackPawnPossibleMoves[i].first, pos.second+superBlackPawnPossibleMoves[i].second};
                if(i==3){
                    if(isInBounds(newMove)){
                        if(isEmpty(newMove)){
                            moves.push_back(coordinatesToString(coord, newMove.second, newMove.first));
                        }
                    } 
                }
                else if(i==4){
                    if(isInBounds(newMove)){
                        if(isEmpty(newMove) && isEmpty({newMove.first+1,newMove.second})){
                            moves.push_back(coordinatesToString(coord, newMove.second, newMove.first));
                        }
                    }
                }
                else if(isInBounds(newMove)){
                    if(!isTeamMate(pos, newMove)){
                        moves.push_back(coordinatesToString(coord, newMove.second, newMove.first));
                    }
                }
            }
        }
        else{
            for(int i=0; i<blackPawnPossibleMoves.size(); i++){
                pair<int, int> newMove = {pos.first+blackPawnPossibleMoves[i].first, pos.second+blackPawnPossibleMoves[i].second};
                if(isInBounds(newMove)){
                    if(!isTeamMate(pos, newMove)){
                        moves.push_back(coordinatesToString(coord, newMove.second, newMove.first));
                    }
                }
            }
        }
    }
    
    sort(moves.begin(), moves.end());
    return moves;
}

vector<string> whitePawnMoves(){
    vector<string> coords;

    vector<string> res = splitString(positions[boardIndex][0], ' ');
    if(res.size()<3){
        return {};
    }
    for(int i=2; i<res.size(); i++){
        coords.push_back(res[i]);
    }

    vector<string> moves;
    for(int k=0; k<coords.size(); k++){
        string coord = coords[k];
        pair<int, int> pos = convertCoordinates(coord);
        // cout<< pos.first << ',' << pos.second << endl;
        if(pos.first<3){
            for(int i=0; i<superWhitePawnPossibleMoves.size(); i++){
                pair<int, int> newMove = {pos.first+superWhitePawnPossibleMoves[i].first, pos.second+superWhitePawnPossibleMoves[i].second};
                if(i==3){
                    if(isInBounds(newMove)){
                        if(isEmpty(newMove)){
                            moves.push_back(coordinatesToString(coord, newMove.second, newMove.first));
                        }
                    } 
                }
                else if(i==4){
                    if(isInBounds(newMove)){
                        if(isEmpty(newMove) && isEmpty({newMove.first-1,newMove.second})){
                            moves.push_back(coordinatesToString(coord, newMove.second, newMove.first));
                        }
                    }
                }
                else if(isInBounds(newMove)){
                    if(!isTeamMate(pos, newMove)){
                        moves.push_back(coordinatesToString(coord, newMove.second, newMove.first));
                    }
                }
            }
        }
        else{
            for(int i=0; i<whitePawnPossibleMoves.size(); i++){
                pair<int, int> newMove = {pos.first+whitePawnPossibleMoves[i].first, pos.second+whitePawnPossibleMoves[i].second};
                if(isInBounds(newMove)){
                    if(!isTeamMate(pos, newMove)){
                        moves.push_back(coordinatesToString(coord, newMove.second, newMove.first));
                    }
                }
            }
        }
    }
    
    sort(moves.begin(), moves.end());
    return moves;
}

vector<string> pawnMoves(){
    if(turn[boardIndex][0]=='b'){
        return blackPawnMoves();
    }
    else{
        return whitePawnMoves();
    }
}


int main(){
    takeInInput();
    // cout<<otherLionIsOpen();
    for(boardIndex=0; boardIndex<boards.size(); boardIndex++){
        vector<string> moves = lionMoves();
        printVector(moves);
        moves = zebraMoves();
        printVector(moves);
        moves = elephantMoves();
        printVector(moves);
        moves = pawnMoves();
        printVector(moves);
        cout<<endl;
    }
    boardIndex = 0;
    
}