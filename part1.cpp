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
    string S;
	string s;
	string G;
	string g;
	string M;
	string m;
	string E;
	string e;
	string L;
	string l;
	string C;
	string c;
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
		else if(input[i] == 'S'){
			if(S.empty()){
				S = str;}
			else{S = S + " " + str;
			}
			k++;
		}
		else if(input[i] == 's'){
			if(s.empty()){
				s = str;}
			else{s = s + " " + str;
			}
			k++;
		}
		else if(input[i] == 'G'){
			if(G.empty()){
				G = str;}
			else{G = G + " " + str ;
			}
			k++;
		}
		else if(input[i] == 'g'){
			if(g.empty()){
				g = str;}
			else{g = g + " " + str;
			}
			k++;
		}
		else if(input[i] == 'M'){
			if(M.empty()){
				M = str;}
			else{M = M + " " + str;
			}
			k++;
		}
		else if(input[i] == 'm'){
			if(m.empty()){
				m = str;}
			else{m = m + " " + str ;
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
		else if(input[i] == 'C'){
			if(C.empty()){
				C = str;}
			else{C = C + " " + str;
			}
			k++;
		}
		else if(input[i] == 'c'){
			if(c.empty()){
				c = str;}
			else{c =c + " " + str;
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
	if(!(S.empty())){
		output[2] = "white superpawn:" + space + sortInAlph(S);
	}else{
		output[2] = "white superpawn:";
	}
	if(!(s.empty())){
		output[3] = "black superpawn:" + space + sortInAlph(s);
	}else{
		output[3] = "black superpawn:";
	}
	if(!(G.empty())){
		output[4] = "white giraffe:" + space + sortInAlph(G);
	}else{
		output[4] = "white giraffe:";
	}
	if(!(g.empty())){
		output[5] = "black giraffe:" + space + sortInAlph(g);
	}else{
		output[5] = "black giraffe:";
	}
	if(!(M.empty())){
		output[6] = "white monkey:" + space + sortInAlph(M);
	}else{
		output[6] = "white monkey:";
	}
	if(!(m.empty())){
		output[7] = "black monkey:" + space + sortInAlph(m);
	}else{
		output[7] = "black monkey:";
	}
	if(!(E.empty())){
		output[8] = "white elephant:" + space + sortInAlph(E);
	}else{
		output[8] = "white elephant:";
	}
	if(!(e.empty())){
		output[9] = "black elephant:" + space + sortInAlph(e);
	}else{
		output[9] = "black elephant:";
	}
	if(!(L.empty())){
		output[10] = "white lion:" + space + sortInAlph(L);
	}else{
		output[10] = "white lion:";
	}
	if(!(l.empty())){
		output[11] = "black lion:" + space + sortInAlph(l);
	}else{
		output[11] = "black lion:";
	}
	if(!(C.empty())){
		output[12] = "white crocodile:" + space + sortInAlph(C);
	}else{
		output[12] = "white crocodile:";
	}
	if(!(c.empty())){
		output[13] = "black crocodile:" + space + sortInAlph(c);
	}else{
		output[13] = "black crocodile:";
	}
	if(!(Z.empty())){
		output[14] = "white zebra:" + space + sortInAlph(Z);
	}else{
		output[14] = "white zebra:";
	}
	if(!(z.empty())){
		output[15] = "black zebra:" + space + sortInAlph(z);
	}else{
		output[15] = "black zebra:";
	}

	output[16] = "side to play:" + space + sideToPlay;

	return output;
}

int main()
{
    int N;
    cin >> N;
    cin.ignore();

    vector<string> input(N);

    for(int i = 0; i < N; i++){
    	string x;
    	getline(cin, x);
    	input[i] = x;
	}

	vector<string> x(17);

  	for(int i = 0; i < N; i++){
	    x = settingUpBoard(input[i]);
	    for(int i = 0; i < x.size(); i++){
	    	cout << x[i] << endl;
		}
	}

	return 0;
}
