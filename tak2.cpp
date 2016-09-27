#include <bits/stdc++.h>
using namespace std;

int blackFlatStoneLeft=21;
int whiteFlatStoneLeft=21;
int blackCapStoneLeft=1;
int whiteCapStoneLeft=1;
//enums

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

vector<string> getChildren(vector<int> node[5][5]) {
//return all different valid moves in string
	//IN=	FLATnWall-> (ADJACENT-WALL-CAP)
	//IN=	CAP->		(ADJACENT-CAP)
	//OUT=  AllLeft->   UNOCCUPIED ONLY
	vector<string> allMoves;
	//in--------------------
	for(int i = 0 ; i < 5 ; i++) {
		for(int j = 0 ; j < 5 ; j++) {
			if(i==0){
				if(j==0){
					//right down
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
			child = move_state(node, validMoves[i]);
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