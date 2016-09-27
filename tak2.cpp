#include <bits/stdc++.h>
using namespace std;

int blackFlatStoneLeft=21;
int whiteFlatStoneLeft=21;
int blackCapStoneLeft=1;
int whiteCapStoneLeft=1;
//enums
char[] strChar(string);
string encodeI(int);
string encodeJ(int);
string[] decodeMyMove5(string);
string[] decodeMyMove4(string);
string myCharToString(char,char);
string myCharToString(char);
int decodeJ(string);
int decodeI(string);

bool isRoad(vector<int> node[5][5], bool isWhite) { // unfinished
	int tmpArr[5][5];
	for(int i = 0 ; i < 5 ; i++) {
		for(int j = 0 ; j < 5 ; j++) {
			if(node[i][j].pop_back()%10==1 && isWhite)
				tmpArr[i][j] = 1;
			else if(node[i][j].pop_back()%10==2 && !isWhite)
				tmpArr[i][j] = 1;
			else
				tmpArr[i][j] = 0;
		}
	}
}

int evaluation(vector<int> node[5][5]) {

}
string encodeJ(int j){
        string res="";
        int d=j+1;
    switch (d){
    case 1:
        res="a";
        break;
    case 2:
        res="b";
        break;
    case 3:
        res="c";
        break;
    case 4:
        res="d";
        break;
    case 5:
        res="e";
        break;}
    return res;
}
string encodeI(int i){
    return to_string(i+1);
}
vector<string> getChildren(vector<int> node[5][5]) {
//return all different valid moves in string
	//IN=	FLATnWall-> (ADJACENT-WALL-CAP)
	//IN=	CAP->		(ADJACENT-CAP)
	//OUT=  AllLeft->   UNOCCUPIED ONLY

	//towards j(=a) >    	---------------------right
	//away j <				---------------------left
	//towards i(==) -		---------------------up
	//away i +				---------------------down
	vector<string> allMoves;
	//in--------------------
	for(int i = 0 ; i < 5 ; i++) {
		for(int j = 0 ; j < 5 ; j++) {
			int size=node[i][j].size();
			if(i==0){
				if(j==0){
					//right down
					//whether a wall or cap stone is in path or not--have to consider*****************************
					//also hav to insert and update the matrix---here or while using getChildren
					if(size==1){
						//right
						string res=to_string(size)+encodeJ(j)+encode(i);
						allMoves.push_back(res +">1");
						//down
						allMoves.push_back(res+"+1");
					}
				}else if(j==4){
					//right up
				}else{
					//up down right
				}
			}else if(i==4){
				if(j==0){
					//left down
				}else if(j==4){
					//left up
				}else{
					//up down left
				}
			}else{
				if(j==0){
					//down right left
				}else if(j==4){
					//up right left
				}else{
					// mid of matrix
					//all four directions
				}
			}
		}
	}
	//in--------------------
}

int alphabeta(vector<int> node[5][5], int depth, int alpha, int beta, bool maximizingPlayer) {
	int v;
	vector<string> validMoves = getChildren(node);
	vector<int> child[5][5];

	if(depth==0 || validMoves.size()==0)
		return evaluation(node);

	if(maximizingPlayer) {
		v = -INT_MAX;
		for(int i = 0 ; i < validMoves.size() ; i++) {
			child = move_state(node, validMoves[i]);//will use decodeMyMove4,5
			v = max(v, alphabeta(child, depth-1, alpha, beta, false));
			alpha = max(alpha, v);
			if(beta <= alpha)
				break;
		}
		return v;
	}
	else {
		v = INT_MAX;
		for(int i = 0 ; i < validMoves.size() ; i++) {
			child = move_state(node, validMoves[i]);
			v = min(v, alphabeta(child, depth-1, alpha, beta, false));
			beta = min(beta, v);
			if(beta <= alpha)
				break;
		}
		return v;
	}
}

int main() {
	return 0;
}

/*
char decodeMove(string move){
	for(int i=0; i<move.size();i++){
	
	}
    char size=move.at(0);
    return size;
}
*/
/*
main(){}
	string g= "2";
    vector<string> v;
    g= g+ "a1>"+encodeJ(2)+encodeI(1);
    v.push_back(g);
    
    cout<<v.at(0)<<endl;
    cout<<decodeMove(g)<<endl;
    string s(1, decodeMove(g)); 
    std::cout << s << std::endl;
    string h;
    h.push_back(decodeMove(g));
    cout << h << std::endl;
    cout << g.size() << std::endl;
*/
int decodeI(string X){
    int i = (int) X.at(0);//size of X should be 1;
    return i-1;
}
int decodeJ(string Y){
        int res=0;
        //int d=j+1;
    switch (Y){
    case "a":
        res=0;
        break;
    case "b":
        res=1;
        break;
    case "c":
        res=2;
        break;
    case "d":
        res=3;
        break;
    case "e":
        res=4;
        break;}
    return res;
}
string myCharToString(char c){
    char firstLetter=c;
    string first;
    first.push_back(firstLetter);
    return first;
}
string myCharToString(char c1,char c2){
    string str;
    str.push_back(c1);
    str.push_back(c2);
    return str;
}
string[] decodeMyMove5(string move){
    string str[5];
    //0->size//1->positionX//2->positionY//3->direction//4->no. of stones dropped in sequence
    char firstLetter=move.at(0);
    int size = (int)firstLetter;
    str[0] = myCharToString(firstLetter);
    str[1]=myCharToString(move.at(1));
    str[2]=myCharToString(move.at(2));
    str[3]=myCharToString(move.at(3));
    string drops;
    for(int i=4;i<move.size();i++){
        drops.push_back(myCharToString(move.at(i)));
    }
    str[4]=drops;
    return str;
}
string[] decodeMyMove4(string move){
    string str[4];
    //0->size//1->positionX//2->positionY//3->direction//4->no. of stones dropped in sequence
    char firstLetter=move.at(0);
    int size = (int)firstLetter;
    str[0] = myCharToString(firstLetter);
    str[1]=myCharToString(move.at(1),move.at(2));//In this case size will be 4
    str[2]=myCharToString(move.at(3));
    string drops;
    for(int i=4;i<move.size();i++){
        drops.push_back(myCharToString(move.at(i)));
    }
    str[3]=drops;
    return str;
}
string encodeJ(int j){
        string res="";
        int d=j+1;
    switch (d){
    case 1:
        res="a";
        break;
    case 2:
        res="b";
        break;
    case 3:
        res="c";
        break;
    case 4:
        res="d";
        break;
    case 5:
        res="e";
        break;}
    return res;
}
string encodeI(int i){
    return to_string(i+1);
}
char[] strChar(string tmp){
    char tab2[1024];
    strncpy(tab2, tmp.c_str(), sizeof(tab2));
    tab2[sizeof(tab2) - 1] = 0;
    return tab2;
}