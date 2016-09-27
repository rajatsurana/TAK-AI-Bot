#include <bits/stdc++.h>
using namespace std;

void isRoadUtil(int A[5][5], int x, int y, int n) {
	A[x][y] = -1;
	if(x-1>=0 && A[x-1][y]==1)
		isRoadUtil(A, x-1, y, n);
	if(y-1>=0 && A[x][y-1]==1)
		isRoadUtil(A, x, y-1, n);
	if(x+1<n && A[x+1][y]==1)
		isRoadUtil(A, x+1, y, n);
	if(y+1<n && A[x][y+1]==1)
		isRoadUtil(A, x, y+1, n);
}

bool isRoad(vector<int> node[5][5], bool isWhite) {
	int N = 5;
	int stor_x[5][5], stor_y[5][5];
	for(int i = 0 ; i < N ; i++) {
		for(int j = 0 ; j < N ; j++) {
			if(node[i][j].back()%10==1 && isWhite) {
				stor_x[i][j] = 1;
				stor_y[i][j] = 1;
			}
			else if(node[i][j].back()%10==2 && !isWhite) {
				stor_x[i][j] = 1;
				stor_y[i][j] = 1;
			}
			else {
				stor_x[i][j] = 0;
				stor_y[i][j] = 0;
			}
		}
	}

	for(int i = 0 ; i < N ; i++) {
		if(stor_x[0][i] > 0)
			isRoadUtil(stor_x, 0, i, N);
	}
	for(int i = 0 ; i < N ; i++) {
		if(stor_x[N-1][i] < 0)
			return true;
	}

	for(int i = 0 ; i < N ; i++) {
		if(stor_y[i][0] > 0)
			isRoadUtil(stor_y, i, 0, N);
	}
	for(int i = 0 ; i < N ; i++) {
		if(stor_y[i][N-1] < 0)
			return true;
	}
	return false;
}

int evaluation(vector<int> node[5][5], bool isWhite) {
	int val = 0;
	if(node.white_out_flat==0 || node.black_out_flat==0 || isRoad(node, isWhite) || isRoad(node, !isWhite)) {	// wins
		if(isWhite) {
			if(node.white_out_flat > node.black_out_flat)	// flat win
				val += node.white_out_flat;
			else if(isRoad(node, isWhite))											// road win
				val += node.white_out_flat + 25;
			else
				val += node.white_in_flat;
		}
		else {
			if(node.white_out_flat < node.black_out_flat)	// flat win
				val += node.black_out_flat;
			if(isRoad(node, isWhite))											// road win
				val += node.black_out_flat + 25;
			else
				val += node.white_in_flat;
		}
		return val;
	}

	if() {	// road win
		if(isRoad(node, isWhite) && isWhite)
			val += 25;
		if(isRoad(node, !isWhite) && !isWhite)
			val += 25;
	}

	int val = node.out_flat;	//	unplayed flatstones
	if(isRoad(node, isWhite))
		val += 25;	// size of the board
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
