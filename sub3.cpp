#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <ostream>
#include <bits/stdc++.h>
#include <sstream>
#include <cstdio>
#include <fstream>
#include <string.h>
#include <algorithm>

using namespace std;

vector<vector<vector<char>>> boards;
vector<string> turn;
vector<vector<string>> positions;
vector<string> x(9);

string sortInAlph(string x){
    vector<string>temp;
    size_t pos = 0;
    string space = " ";
    string token;
    while((pos = x.find(space)) != std::string::npos){
        token = x.substr(0, pos);
        temp.push_back(token);
        x.erase(0, pos + space.length());
    }

    temp.push_back(x);
    sort(temp.begin(), temp.end());
    string res = "";
    for(int i = 0;i<temp.size()-1;i++){
        res += temp[i] + " ";
    }
    res += temp[temp.size()-1];

    return res;
}

vector<string> settingUpBoard(string input){
    string space = " ";
	string P;
    string p;
	string E;
	string e;
	string L;
	string l;
	string Z;
	string z;
	string sideToPlay;
	int k = 0;
	int r = 7;
	vector<string> output(17);

	string v = "abcdefg";
    for(int i = 0; i < input.size(); i++){

        std::ostringstream oss;
        oss << v[k] << r;
        string str = oss.str();
        int numSpace = 0;
        int posOfSecSpace;

        if(input[i] == '/'){
        	r--;
        	k=0;
		}
		else if(input[i] == 'P'){
			if(P.empty()){
				P = str;}
			else{P = P + " " + str;
			}
			k++;
		}
        else if(input[i] == 'p'){
			if(p.empty()){
				p = str;}
			else{p = p + " " + str;
			}
			k++;
		}
		else if(input[i] == 'E'){
			if(E.empty()){
				E = str;}
			else{
				E = E + " " + str;
			}
			k++;
		}
		else if(input[i] == 'e'){
			if(e.empty()){
				e = str;}
			else{e = e + " " + str;
			}
			k++;
		}
		else if(input[i] == 'L'){
			if(L.empty()){
				L = str;}
			else{L = L + " " + str;
			}
			k++;
		}
		else if(input[i] == 'l'){
			if(l.empty()){
				l = str;}
			else{l = l + " " + str;
			}
			k++;
		}
		else if(input[i] == 'Z'){
			if(Z.empty()){
				Z = str;}
			else{Z = Z + " " + str;
			}
			k++;
		}
		else if(input[i] == 'z'){
			if(z.empty()){
				z = str;}
			else{z = z + " " + str;
			}
			k++;
		}
		else if(input[i] == ' ' && numSpace == 0){
			numSpace++;
			if(input[i-1] == 'b'){
				sideToPlay = "black";
			}
			else if(input[i-1] == 'w'){
				sideToPlay = "white";
			}
			else{
				sideToPlay = " yoh ";
			}
		}
		else if(input[i] == ' ' && numSpace == 1){
			posOfSecSpace = i;
		}
		else{
			int y;
			std::stringstream res;
			res << input[i];
			res >> y;
			k += y;
		}
	}
	if(!(P.empty())){
		output[0] = "white pawn:" + space + sortInAlph(P);
	}else{
		output[0] = "white pawn:";
	}
	if(!(p.empty())){
		output[1] = "black pawn:" + space + sortInAlph(p);
	}else{
		output[1] = "black pawn:";
	}
	if(!(E.empty())){
		output[2] = "white elephant:" + space + sortInAlph(E);
	}else{
		output[2] = "white elephant:";
	}
	if(!(e.empty())){
		output[3] = "black elephant:" + space + sortInAlph(e);
	}else{
		output[3] = "black elephant:";
	}
	if(!(L.empty())){
		output[4] = "white lion:" + space + sortInAlph(L);
	}else{
		output[4] = "white lion:";
	}
	if(!(l.empty())){
		output[5] = "black lion:" + space + sortInAlph(l);
	}else{
		output[5] = "black lion:";
	}
	if(!(Z.empty())){
		output[6] = "white zebra:" + space + sortInAlph(Z);
	}else{
		output[6] = "white zebra:";
	}
	if(!(z.empty())){
		output[7] = "black zebra:" + space + sortInAlph(z);
	}else{
		output[7] = "black zebra:";
	}

	output[8] = "side to play:" + space + sideToPlay;

	return output;
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

bool isNumber(char c){
    vector<char> v = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    if(count(v.begin(), v.end(), c)){
        return true;
    }
    return false;
}

void printBoard(vector<vector<char>> board){
    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            cout << board[i][j];
            cout << ' ';
        }
        cout << endl;
    }
}

void putIntoBoard(string input){
	vector<vector<char>> board = {
		{'#', '#', '#', '#', '#', '#', '#'},
		{'#', '#', '#', '#', '#', '#', '#'},
		{'#', '#', '#', '#', '#', '#', '#'},
		{'#', '#', '#', '#', '#', '#', '#'},
		{'#', '#', '#', '#', '#', '#', '#'},
		{'#', '#', '#', '#', '#', '#', '#'},
		{'#', '#', '#', '#', '#', '#', '#'},
	};
    vector<string> splitBySlash = splitString(input, '/');
	int rankIterator = 0;
	// TODO: fix board, is upside down
    for(int i=0; i<7; i++){
        string rank = splitBySlash[i];
        for(int j=0; j<7; j++){
            if(isNumber(rank[rankIterator])){
                int number = rank[rankIterator]-'0';
				j += number-1;
            }
            else{
                board[i][j] = rank[rankIterator];
            }
			rankIterator++;
        }
		rankIterator = 0;
    }
	// printBoard(board);
	boards.push_back(board);
}

void takeInInput()
{
    int N;
    // cin >> N;
	string temp;
	getline(cin, temp);
	N = stoi(temp);

    vector<string> input(N);

    for(int i = 0; i < N; i++){
    	// string x = "2ele1z/ppppppp/7/7/7/PPP1PPP/2ELE1Z w 4";
		string x;
    	getline(cin, x);
		vector<string> res = splitString(x, ' ');
		putIntoBoard(res[0]);
		turn.push_back(res[1]);
    	input[i] = x;
	}

  	for(int i = 0; i < N; i++){
		positions.push_back(settingUpBoard(input[i]));
	    // x = positions[0];
	    // for(int i = 0; i < x.size(); i++){
	    // 	cout << x[i] << endl;
		// }
	}

}

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
    if(blackLion[0]==whiteLion[0]){
        for(int i=posBlack.first+1; i<posWhite.first; i++){
            if(!isEmpty({i, posBlack.second})){
                // cout<<posBlack.first<<','<<posBlack.second<<endl;
                return false;
            }
        }
    }
    return true;
}

bool isDiagonal(){
    if(isEmpty({3,3}) && tolower(boards[boardIndex][4][2])=='l' && tolower(boards[boardIndex][2][4])=='l'){
        return true;
    }
    else if(isEmpty({3,3}) && tolower(boards[boardIndex][2][2])=='l' && tolower(boards[boardIndex][4][4])=='l'){
        return true;
    }
    return false;
}

vector<string> lionMoves(){
    // TODO: take care of situation when other lion is open
    string coord;
    string otherLion;
    if(turn[boardIndex][0]=='b'){
        coord = splitString(positions[boardIndex][5], ' ')[2];
        otherLion = splitString(positions[boardIndex][4], ' ')[2];
    }
    else{
        coord = splitString(positions[boardIndex][4], ' ')[2];
        otherLion = splitString(positions[boardIndex][5], ' ')[2];
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
    if(otherLionIsOpen()){
        moves.push_back(coord+otherLion);
    }
    else if(isDiagonal()){
        moves.push_back(coord+otherLion);
    }
    sort(moves.begin(), moves.end());
    return moves;
}

vector<string> zebraMoves(){
    string coord;
    if(turn[boardIndex][0]=='b'){
        coord = splitString(positions[boardIndex][7], ' ')[2];
    }
    else{
        coord = splitString(positions[boardIndex][6], ' ')[2];
    }
    pair<int, int> pos = convertCoordinates(coord);
    // cout<< pos.first << ',' << pos.second << endl;
    vector<string> moves;
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
    // TODO: test this then work on superPawn
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
        // vector<string> moves = lionMoves();
        // vector<string> moves = zebraMoves();
        vector<string> moves = elephantMoves();
        // vector<string> moves = pawnMoves();
        // cout<< boardIndex << "th iteration:" << endl;
        printVector(moves);
    }
    boardIndex = 0;
    
}