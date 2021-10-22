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
	printBoard(board);
	boards.push_back(board);
}

void takeInInput()
{
    int N;
    // cin >> N;
	// string temp;
	// getline(cin, temp);
	// N = stoi(temp);
	N = 1;

    vector<string> input(N);

    for(int i = 0; i < N; i++){
    	string x = "4E2/2P1l1p/7/7/2L4/2p4/4e2 w 36";
		// string x;
    	// getline(cin, x);
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
