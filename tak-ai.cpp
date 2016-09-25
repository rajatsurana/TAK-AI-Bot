#include <bits/stdc++.h>
using namespace std;

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
