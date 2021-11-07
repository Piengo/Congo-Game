#include <bits/stdc++.h>
#include "part1.cpp"

using namespace std;

int boardIndex;

vector<int> answers;
vector<vector<char>> tempBoard;
vector<string> tempPositions;
char tempTurn;
int tempMoveNumber;

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
    char myPiece = tempBoard[me.first][me.second];
    char space = tempBoard[otherPiece.first][otherPiece.second];
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
    return tempBoard[pos.first][pos.second] == '#';
}

bool otherLionIsOpen(){
    string whiteLion;
    string blackLion;
    vector<string> res = splitString(tempPositions[4], ' ');
    whiteLion = res[2];
    res = splitString(tempPositions[5], ' ');
    blackLion = res[2];
    pair<int, int> posWhite = convertCoordinates(whiteLion);
    pair<int, int> posBlack = convertCoordinates(blackLion);
    if(posWhite.second==posBlack.second){
        for(int i=posBlack.first+1; i<posWhite.first; i++){
            if(!isEmpty({i, posBlack.second})){
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
    if(tempBoard[3][3]=='#' && tolower(tempBoard[4][2])=='l' && tolower(tempBoard[2][4])=='l'){
        return true;
    }
    else if(tempBoard[3][3]=='#' && tolower(tempBoard[2][2])=='l' && tolower(tempBoard[4][4])=='l'){
        return true;
    }
    return false;
}

vector<string> lionMoves(vector<string> &moves){
    string coord;
    string otherLion;
    vector<string> res;
    if(tempTurn=='b'){
        coord = splitString(tempPositions[5], ' ')[2];
        res = splitString(tempPositions[4], ' ');
        if (res.size()>2)
        {
            otherLion = res[2];
        }
    }
    else{
        coord = splitString(tempPositions[4], ' ')[2];
        res = splitString(tempPositions[5], ' ');
        if (res.size()>2)
        {
            otherLion = res[2];
        }
    }
    pair<int, int> pos = convertCoordinates(coord);
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

vector<string> zebraMoves(vector<string> &moves){
    string coord;
    vector<string> res;
    if(tempTurn=='b'){
        res = splitString(tempPositions[7], ' ');
        if(res.size()<3){
            return {};
        }
        coord = res[2];
    }
    else{
        res = splitString(tempPositions[6], ' ');
        if(res.size()<3){
            return {};
        }
        coord = res[2];
    }
    pair<int, int> pos = convertCoordinates(coord);
    for(int i=0; i<zebraPossibleMoves.size(); i++){
        pair<int, int> newMove = {pos.first+zebraPossibleMoves[i].first, pos.second+zebraPossibleMoves[i].second};
        if(isInBounds(newMove)){
            if(!isTeamMate(pos, newMove)){
                moves.push_back(coordinatesToString(coord, newMove.second, newMove.first));
            }
        }
    }
    sort(moves.begin(), moves.end());
    return moves;
}

vector<string> elephantMoves(vector<string> &moves){
    vector<string> coords;
    if(tempTurn=='b'){
        vector<string> res = splitString(tempPositions[3], ' ');
        for(int i=2; i<res.size(); i++){
            coords.push_back(res[i]);
        }
    }
    else{
        vector<string> res = splitString(tempPositions[2], ' ');
        for(int i=2; i<res.size(); i++){
            coords.push_back(res[i]);
        }
    }

    for(int k=0; k<coords.size(); k++){
        string coord = coords[k];
        pair<int, int> pos = convertCoordinates(coord);
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


vector<string> blackPawnMoves(vector<string> &moves){
    vector<string> coords;

    vector<string> res = splitString(tempPositions[1], ' ');
    if(res.size()<3){
        return {};
    }
    for(int i=2; i<res.size(); i++){
        coords.push_back(res[i]);
    }

    for(int k=0; k<coords.size(); k++){
        string coord = coords[k];
        pair<int, int> pos = convertCoordinates(coord);
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

vector<string> whitePawnMoves(vector<string> &moves){
    vector<string> coords;

    vector<string> res = splitString(tempPositions[0], ' ');
    if(res.size()<3){
        return {};
    }
    for(int i=2; i<res.size(); i++){
        coords.push_back(res[i]);
    }

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

vector<string> pawnMoves(vector<string> &moves){
    if(tempTurn=='b'){
        return blackPawnMoves(moves);
    }
    else{
        return whitePawnMoves(moves);
    }
}

string removeSpaces(string str){
    string result = "";
    int iterator = 0;
    int spaceCount = 0;
    while(iterator<str.size()){
        if(str[iterator]!='#'){
            if(spaceCount!=0){
                result += to_string(spaceCount);
                spaceCount = 0;
            }
            result += str[iterator];
        }
        else{
            spaceCount++;
        }
        iterator++;
    }
    if(spaceCount!=0){
        result += to_string(spaceCount);
    }
    return result;
}

string boardToFEN(vector<vector<char>> board){
    string result = "";
    for(int i=0; i<board.size(); i++){
        vector<char> row = board[i];
        for(int j=0; j<row.size(); j++){
            result += board[i][j];
        }
        if(i!=board.size()-1){
            result += '/';
        }
    }
    result = removeSpaces(result);
    return result;
}

void memoriseRiverPieces(vector<pair<char, string>> &whitePiecesInRiver, vector<pair<char, string>> &blackPiecesInRiver){
    for(int i=0; i<7; i++){
        char piece = tempBoard[3][i];
        string pos = coordinatesToString("", i, 3);
        if(isBlack(piece)){
            blackPiecesInRiver.push_back({piece, pos});
        }
        else{
            whitePiecesInRiver.push_back({piece, pos});
        }
    }
}

void checkIfBlackPiecesStillInRiver(vector<pair<char, string>> blackPiecesInRiver){
    for(int i=0; i<7; i++){
        char piece = tempBoard[3][i];
        string pos = coordinatesToString("", i, 3);
        for(int j=0; j<blackPiecesInRiver.size(); j++){
            pair<char, string> temp = blackPiecesInRiver[j];
            if(temp.first==piece && temp.second==pos){
                tempBoard[3][i] = '#';
            }
        }
    }
}

void checkIfWhitePiecesStillInRiver(vector<pair<char, string>> whitePiecesInRiver){
    for(int i=0; i<7; i++){
        char piece = tempBoard[3][i];
        string pos = coordinatesToString("", i, 3);
        for(int j=0; j<whitePiecesInRiver.size(); j++){
            pair<char, string> temp = whitePiecesInRiver[j];
            if(temp.first==piece && temp.second==pos){
                tempBoard[3][i] = '#';
            }
        }
    }
}

string makeMove(string move){
    vector<pair<char, string>> whitePiecesInRiver;
    vector<pair<char, string>> blackPiecesInRiver;

    memoriseRiverPieces(whitePiecesInRiver, blackPiecesInRiver);

    string initialPos = move.substr(0, 2);
    string wantToMoveTo = move.substr(2, 2);

    pair<int, int> current = convertCoordinates(initialPos);
    pair<int, int> next = convertCoordinates(wantToMoveTo);

    char piece = tempBoard[current.first][current.second];

    tempBoard[next.first][next.second] = piece;
    tempBoard[current.first][current.second] = '#';
    if(current.first==3 && next.first==3){
        tempBoard[next.first][next.second] = '#';
    }

    // function to print boards as FEN string
    if(tempTurn=='w'){
        checkIfWhitePiecesStillInRiver(whitePiecesInRiver);
        string FEN = boardToFEN(tempBoard);
        return FEN + " b " + to_string(tempMoveNumber);
    }
    else{
        tempMoveNumber++;
        checkIfBlackPiecesStillInRiver(blackPiecesInRiver);
        string FEN = boardToFEN(tempBoard);
        return FEN + " w " + to_string(tempMoveNumber);
    }

}

int stateOfGame(){
    bool isBlackFound = false;
    bool isWhiteFound = false;
    int numberOfPieces = 0;

    for(int row=0; row<7; row++){
        for(int col=0; col<7; col++){
            char piece = tempBoard[row][col];
            if(piece=='l'){
                isBlackFound = true;
            }
            else if(piece=='L'){
                isWhiteFound = true;
            }
            if(piece!='#'){
                numberOfPieces++;
            }
        }
    }

    if(isBlackFound && isWhiteFound && numberOfPieces>2){
        // game continues
        return 3;
    }
    else if(isBlackFound && !isWhiteFound){
        // black wins
        return 1;
    }
    else if(!isBlackFound && isWhiteFound){
        // white wins
        return 2;
    }
    else if(isBlackFound && isWhiteFound && numberOfPieces==2){
        // draw
        // cout<<"number of pieces: "<<numberOfPieces<<endl;
        return 0;
    }

    return -1;
}

int calcWhiteMinusBlack(){
    int blackScore = 100*(splitString(tempPositions[1], ' ').size()-2) + 
        200*(splitString(tempPositions[3], ' ').size()-2) + 
        300*(splitString(tempPositions[7], ' ').size()-2);
    int whiteScore = 100*(splitString(tempPositions[0], ' ').size()-2) + 
        200*(splitString(tempPositions[2], ' ').size()-2) + 
        300*(splitString(tempPositions[6], ' ').size()-2);
    return whiteScore-blackScore;
}

int calcScore(){
    int stateOfLions = stateOfGame();
    if(stateOfLions==0){
        // only lions, draw
        return 0;
    }
    else if(stateOfLions==1){
        // black alive, white dead
        int res = -10000;
        if(tempTurn=='b'){
            return res*-1;
        }
        else{
            return res;
        }
    }
    else if(stateOfLions==2){
        // black dead, white alive
        int res = 10000;
        if(tempTurn=='b'){
            return res*-1;
        }
        else{
            return res;
        }
    }
    else if(stateOfLions==3){
        // black alive, white alive
        int toReturn = calcWhiteMinusBlack();
        if(toReturn==0){
            // all pieces still on board
            return -2;
        }
        return toReturn;
    }

    return -1;
}

bool isGameOver(){
    int resIsGameOver = calcScore();
    if(resIsGameOver==10000 || resIsGameOver==-10000 || resIsGameOver==0){
        return true;
    }
    return false;
}

vector<string> generateMoves(){
    vector<string> moves;

    lionMoves(moves);
    zebraMoves(moves);
    elephantMoves(moves);
    pawnMoves(moves);

    return moves;
}

int minimax(string currentState, int depth){
    tempPositions = settingUpBoard(currentState);
    vector<string> res = splitString(currentState, ' ');
    tempBoard = putIntoBoard(res[0]);
    tempTurn = res[1][0];
    tempMoveNumber = stoi(res[2]);


    if(isGameOver() || depth <= 0){
        int score = calcScore();
        answers.push_back(score);
        return score;
    }


    int value = -10000000;
    vector<string> moves = generateMoves();


    for(int i=0; i<moves.size(); i++){
        tempPositions = settingUpBoard(currentState);
        vector<string> res = splitString(currentState, ' ');
        tempBoard = putIntoBoard(res[0]);
        tempTurn = res[1][0];
        tempMoveNumber = stoi(res[2]);
        
        string move = moves[i];
        string nextState = makeMove(move);
        int eval = -minimax(nextState, depth-1);
        value = max(value, eval);
    }

    return value;
}

int main(){
    takeInInput();
    for(boardIndex=0; boardIndex<FENStrings.size(); boardIndex++){
        // cout<<FENStrings[boardIndex]<<endl;
        // minimax("2ele1z/ppppppp/7/7/7/PPP1PPP/2ELE1Z w 4", 3);
        string s = "1z5/pPp1lP1/5ep/4P1e/4L1p/2p2pP/7 w 12";
        vector<string> sArr = splitString(s, ' ');
        int value = minimax(s, 2);
        if(sArr[1][0]=='b'){
            value = value*-1;
        }
        cout << value << endl;
        // cout << minimax(FENStrings[boardIndex], 0) << endl;
    }

    // for(int i=0; i<answers.size(); i++){
    //     cout << answers[i] << ' ';
    // }
    // cout<<endl;
    
}