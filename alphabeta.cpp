#include <bits/stdc++.h>
using namespace std;

int evaluation(MyPlayer node) {
	int current_piece, moves = node.game.moves;

    if (node.game.turn == 0)
        moves += 1;
    if (moves != 1)
        current_piece = node.game.turn;
    else
        current_piece = 1 - node.game.turn;

	int eval = 0;

	eval = eval + (node.game.max_flats - node.game.players[current_piece].flats);	// flats on board

	return eval;
}

int alphabeta(MyPlayer node, int alpha, int beta, int depth, bool maximizingPlayer, vector<string> res, vector<vector<string>> horizon) {
	int v;
	MyPlayer child, child1, child2;
	vector<string> all_moves = node.game.generate_all_moves(node.player);

	if(depth==0 || all_moves.size()==0)	// children should be zero even if road formed ; game ended ;
		return evaluation(node->game->board);	// vector<vector<int>>

	if(maximizingPlayer) {
		v = -INT_MAX;

		// descending order by evaluation of children ;
		for(int i = 0 ; i < all_moves.size() ; i++) {
			for(int j = 0 ; j < i ; j++) {
				child1 = node;
				child1.execute_move(all_moves[i]);
				child2 = node;
				child2.execute_move(all_moves[j]);

				if(evaluation(child1) < evaluation(child2)) { // descending ;
					string tmp = all_moves[i];
					all_moves[i] = all_moves[j];
					all_moves[j] = all_moves[i];
				}
			}
		}

		for(int i = 0 ; i < all_moves.size() ; i++) {
			child = node;
			child.execute_move(all_moves[i]);

			int child_ab = alphabeta(child, alpha, beta, depth-1, false, res);
			if(v < child_ab) {
				v = child_ab;	// max(v, child_ab) ;
				res.back() = all_moves[i];
			}
			alpha = max(alpha, v);
			if(beta <= alpha)
				break;
		}
		res.push_back("");
    for(int i = 0 ; i < horizon.size() ; i++) {
      if(res==horizon[i])
        return -INT_MAX;
    }
		return v;
	}
	else {
		v = INT_MAX;

		// ascending order by evaluation of children ;
		for(int i = 0 ; i < all_moves.size() ; i++) {
			for(int j = 0 ; j < i ; j++) {
				child1 = node;
				child1.execute_move(all_moves[i]);
				child2 = node;
				child2.execute_move(all_moves[j]);

				if(evaluation(child1) > evaluation(child2)) { // ascending ;
					string tmp = all_moves[i];
					all_moves[i] = all_moves[j];
					all_moves[j] = all_moves[i];
				}
			}
		}

		for(int i = 0 ; i < all_moves.size() ; i++) {
			child = node;
			child = execute_move(node, validMoves[i]);

			int child_ab = alphabeta(child, alpha, beta, depth-1, false, res);
			if(v > child_ab) {
				v = child_ab;	// min(v, child_ab) ;
				res.back() = all_moves[i];
			}
			beta = min(beta, v);
			if(beta <= alpha)
				break;
		}
		res.push_back("");
    for(int i = 0 ; i < horizon.size() ; i++) {
      if(res==horizon[i])
        return INT_MAX;
    }
		return v;
	}
}

bool safe_horizontal(MyPlayer node, vector<string> res) {
	MyPlayer temp;
	temp = node;
	for(int i = 0 ; i < res.size() ; i++) {
		temp.execute_move(move);
	}
	if(alphabetaUtil(temp, 3)==-INT_MAX)	// oppponent wins ; improve this ;
		return false;
	return true;
}

string alphabetaUtil(MyPlayer node) {
	int depth = 6, alpha = -INT_MAX, beta = INT_MAX;
	bool maximizingPlayer = true;
	vector<string> res;
  vector<vector<string>> horizon;
	res.push_back("");
	alphabeta(node, alpha, beta, depth, maximizingPlayer, res, horizon);
  if(!safe_horizontal(node, res)) {
    horizon.push_back(res);
    res.clear();
    res.push_back("");
  	alphabeta(node, alpha, beta, depth, maximizingPlayer, res, horizon);
  }
	return res[0];
}

void MyPlayer::play(){
  if (this->player == 1){
        string move;
        cin>>move ;/////////////strip
        this->game.execute_move(move);
  }
    while(1){
        //vector<string> all_moves = this->game.generate_all_moves(this->player);
        //string move = all_moves[rand()%all_moves.size()];// alpha beta here
        string move = this.alphabetaUtil();
        this->game.execute_move(move);
        move = move + '\n';
        //cout<<"Possible moves: "<< str(all_moves) << '\n';
        cout<<"Chosen move: "<< move<<endl;
        cout<<move<<std::flush;
        cin>>move;/////////////strip
        this->game.execute_move(move);
  }
}

int main() {
	return 0;
}
