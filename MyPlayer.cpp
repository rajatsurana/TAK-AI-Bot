#include <bits/stdc++.h>
using namespace std;

class Player{
    public:
        int flats;
        int capstones;
        Player(int flats,int capstones);
};

Player::Player(int flats,int capstones){
    this->flats=flats;
    this->capstones=capstones;
}
class Game{
    public:
        int n;
        int total_squares;
        vector<vector<pair<int, string> > > board;
        int turn;
        Game();
        Game(int n);
        vector<Player> players;
        int max_flats;
        int max_capstones;
        int max_movable;
        int max_down;
        int max_up;
        char max_left;
        char max_right;
        int moves;
        vector<string> all_squares;
        string square_to_string(int i);
        int square_to_num(string square_string);
        void execute_move(string move_string);
        void execute_move_opponent(string move_string,int player);
        bool check_valid(int square, char direction, vector<int> partition );
        vector<string> generate_stack_moves(int square);
        vector<string> generate_all_moves(int player);
        vector<string> generate_all_moves_opponent(int player);
        vector<vector<int> > partition(int n);
};
Game::Game() {

}
Game::Game(int n){
    this->n=n;
    this->total_squares=n*n;
    vector<vector<pair<int, string> > > v(n*n); // initialized with n*n empty vectors ; still think for stack ;
    this->board=v;/////////////////////////////////////////////////////??
    this->turn=0;
    if(n==5){
        this->max_flats = 21;
        this->max_capstones = 1;
    }else if(n==6){
        this->max_flats = 30;
        this->max_capstones = 1;
    }else if(n==7){
        this->max_flats = 40;
        this->max_capstones = 1;
    }
    this->max_movable = n;
    this->max_down = 1;
    this->max_up = n;
    this->max_left = 'a';
    this->max_right = (char)((int)'a' + n - 1);
    this->moves = 0;
    Player p1(this->max_flats,this->max_capstones);
    this->players.push_back(p1);
    Player p2(this->max_flats,this->max_capstones);
    this->players.push_back(p2);
    for(int i=0; i<this->total_squares;i++){
        this->all_squares.push_back(this->square_to_string(i)) ;
    }
}
int Game::square_to_num(string square_string){
    // Return -1 if square_string is invalid
    if (square_string.size() != 2){
        return -1;
    }
    if (!(isalpha(square_string[0])) || !(islower(square_string[0])) || !(isdigit(square_string[1]))){
        return -1;
    }
    int row = ((int) square_string[0])- 96;

    int col = (int)square_string[1] - (int)'0';

    if (row < 1 || row > this->n || col < 1 || col > this->n)
        return -1;
    return this->n * (col - 1) + (row - 1) ;
}
string Game::square_to_string(int square){
    ///Convert square number to string
    if (square < 0 || square >= this->total_squares){
        return "";
    }
    int row = square % this->n;
    int col = square / this->n;
    string s;
    s.push_back((char)(row + 97));
    s.push_back('0' + col+1);
    return s;
}
void Game::execute_move_opponent(string move_string,int player){
    ///Execute move
    int current_piece = player;
    int square, count, next_square, next_count;
    //count=0;

    if (isalpha(move_string[0])){
        square = this->square_to_num(move_string.substr(1));
        pair<int, string> tmp_pair (current_piece, string(1,move_string[0]));
        if (move_string[0] == 'F' || move_string[0] == 'S'){
            this->board[square].push_back(tmp_pair);
            //cerr<<tmp_pair.first<<" "<<tmp_pair.second<<" turn:"<< this->turn<<endl;
            this->players[current_piece].flats -= 1;
        }
        else if (move_string[0] == 'C'){
                this->board[square].push_back(tmp_pair);
                this->players[current_piece].capstones -= 1;
        }

    }
  else if (isdigit(move_string[0])){
        count = (int)move_string[0]-(int)'0';
        square = this->square_to_num(move_string.substr(1,2));///1:3 python excludes the latter digit
        char direction = move_string[3];
        int change =0;
        if (direction == '+'){
            change = this->n;
        }else if (direction == '-'){
            change = -this->n;
        }else if (direction == '>'){
            change = 1;
        }else if (direction == '<'){
            change = -1;
        }
        int prev_square = square;
        for(int i =4;i< move_string.size();i++){
            next_count = (int)move_string[i]-(int)'0';
            next_square = prev_square + change;
            if (this->board[next_square].size() > 0 && this->board[next_square].back().second==string(1,'S')){
                pair<int, string> tmp_pair (this->board[next_square].back().first, string(1,'F'));
                this->board[next_square].back() = (tmp_pair);
            }
            if (next_count - count == 0){
                for(int k = this->board[square].size() - count ; k < this->board[square].size() ; k++) {
                  this->board[next_square].push_back(this->board[square][k]);
                }
            }
            else{
                for(int k = this->board[square].size() - count ; k < this->board[square].size() - count + next_count ; k++) {
                  this->board[next_square].push_back(this->board[square][k]);
                }
            }
            prev_square = next_square;
            count -= next_count;
        }
        count = (int)move_string[0]-(int)'0';
    vector<pair<int, string> > tmp_vect;
    for(int k = 0 ; k < this->board[square].size() - count ; k++) {
      tmp_vect.push_back(this->board[square][k]);
    }
        this->board[square] = tmp_vect;
  }
    this->turn = 1 - this->turn;
}
void Game::execute_move(string move_string){
    ///Execute move
    int current_piece = 0;
    int square, count, next_square, next_count;
    //count=0;
    if (this->turn == 0){
        this->moves += 1;
    }
    if (this->moves != 1){
        current_piece = this->turn;
    }
    else{
        current_piece = 1 - this->turn;
    }
    if (isalpha(move_string[0])){
        square = this->square_to_num(move_string.substr(1));
        pair<int, string> tmp_pair (current_piece, string(1,move_string[0]));
        if (move_string[0] == 'F' || move_string[0] == 'S'){
            this->board[square].push_back(tmp_pair);
            //cerr<<tmp_pair.first<<" "<<tmp_pair.second<<" turn:"<< this->turn<<endl;
            this->players[current_piece].flats -= 1;
        }
        else if (move_string[0] == 'C'){
                this->board[square].push_back(tmp_pair);
                this->players[current_piece].capstones -= 1;
        }

    }
  else if (isdigit(move_string[0])){
        count = (int)move_string[0]-(int)'0';
        square = this->square_to_num(move_string.substr(1,2));///1:3 python excludes the latter digit
        char direction = move_string[3];
        int change =0;
        if (direction == '+'){
            change = this->n;
        }else if (direction == '-'){
            change = -this->n;
        }else if (direction == '>'){
            change = 1;
        }else if (direction == '<'){
            change = -1;
        }
        int prev_square = square;
        for(int i =4;i< move_string.size();i++){
            next_count = (int)move_string[i]-(int)'0';
            next_square = prev_square + change;
            if (this->board[next_square].size() > 0 && this->board[next_square].back().second==string(1,'S')){
                pair<int, string> tmp_pair (this->board[next_square].back().first, string(1,'F'));
                this->board[next_square].back() = (tmp_pair);
            }
            if (next_count - count == 0){
                for(int k = this->board[square].size() - count ; k < this->board[square].size() ; k++) {
                  this->board[next_square].push_back(this->board[square][k]);
                }
            }
            else{
                for(int k = this->board[square].size() - count ; k < this->board[square].size() - count + next_count ; k++) {
                  this->board[next_square].push_back(this->board[square][k]);
                }
            }
            prev_square = next_square;
            count -= next_count;
        }
        count = (int)move_string[0]-(int)'0';
    vector<pair<int, string> > tmp_vect;
    for(int k = 0 ; k < this->board[square].size() - count ; k++) {
      tmp_vect.push_back(this->board[square][k]);
    }
        this->board[square] = tmp_vect;
  }
    this->turn = 1 - this->turn;
}


vector<vector<int> > Game::partition(int n){
    ///Generates all permutations of all partitions of n
    vector<vector<int> > part_list, tmpList;
    vector<int> xx;///////////
    xx.push_back(n);
    part_list.push_back(xx);//////////////// correct

    for(int x = 1 ; x < n ; x++){
        tmpList = this->partition(n - x);
        for(int y = 0 ; y < tmpList.size() ; y++) {
            vector<int> tmp_vect;////////////
            tmp_vect.push_back(x);
            for(int k = 0 ; k < tmpList[y].size() ; k++) {
                tmp_vect.push_back(tmpList[y][k]);
            }
            part_list.push_back(tmp_vect);
        }
    }
    return part_list;
}
bool Game::check_valid(int square, char direction, vector<int> partition){
    //For given movement (partition), check if stack on
    ///square can be moved in direction. Assumes active player
    ///is topmost color
    int change, next_square;
    if(direction == '+'){
        change = this->n;
    }
    else if (direction == '-'){
        change = -this->n;
    }
    else if (direction == '>'){
        change = 1;
    }
    else if (direction == '<'){
        change = -1;
    }
    for (int i=0;i < partition.size();i++){
        next_square = square + change * (i + 1);
        if (this->board[next_square].size() > 0 && this->board[next_square].back().second == string(1,'C')){
            return false;
        }
        if (this->board[next_square].size() > 0 && this->board[next_square].back().second == string(1,'S') && i != partition.size() - 1){
            return false;
        }
        if (i == partition.size() - 1 && this->board[next_square].size()  > 0 && this->board[next_square].back().second == string(1,'S') && partition[i] > 1){
            return false;
        }
        if (i == partition.size()  - 1 && this->board[next_square].size()  > 0 && this->board[next_square].back().second == string(1,'S') && this->board[square].back().second != string(1,'C')){
            return false;
        }
    }
    return true;
}

vector<string> Game::generate_stack_moves(int square){
    //Generate stack moves from square
    //Assumes active player is topmost color
    vector<string> all_moves;
    int r = square % this->n;
    int c = square / this->n;
    int size = this->board[square].size();
    char dirs[4] = {'+', '-', '<', '>'};
    int up = this->n - 1 - c;
    int down = c;
    int right = this->n - 1 - r;
    int left = r;
    int rem_squares[4] = { up, down, left, right };
    for(int num=0; num <min(size, this->n);num++){
        vector<vector<int> > part_list = this->partition(num + 1);
        for (int di=0;di<4;di++){
            vector<vector<int> > part_dir;
            for(int k = 0 ; k < part_list.size() ; k++) {
                if(part_list[k].size() <= rem_squares[di]) {
                  part_dir.push_back(part_list[k]);
                }
            }
            vector<int> part;
            for(int k = 0 ; k < part_dir.size() ; k++){
                part = part_dir[k];
                if (this->check_valid(square, dirs[di], part)){
                    string part_string  = "";
                    int part_sum = 0;
                    for(int j = 0 ; j < part.size() ; j++) {
                        part_string.push_back('0'+part[j]);
                        part_sum = part_sum + part[j];
                    }
                    string push;
                    push.push_back('0'+part_sum);
                    all_moves.push_back(push + this->all_squares[square] + dirs[di] + part_string);
                }
            }
        }
    }
    return all_moves;
}
vector<string> Game::generate_all_moves_opponent(int player){
  vector<string> all_moves;
    for (int i=0; i<this->board.size();i++){
        if (this->board[i].size() == 0){
            if (this->players[player].flats > 0){
                all_moves.push_back("F" + this->all_squares[i]);
            }
            if (this->moves != player and this->players[player].flats > 0){

                all_moves.push_back("S" +this->all_squares[i]);
            }
            if (this->moves != player && this->players[player].capstones > 0){
                all_moves.push_back("C" + this->all_squares[i]);
            }
        }
    }
    return all_moves;
}
vector<string> Game::generate_all_moves(int player){
    ///Generate all possible moves for player
    ///Returns a list of move strings
    vector<string> all_moves;
    for (int i=0; i<this->board.size();i++){
        if (this->board[i].size() == 0){
            if (this->players[player].flats > 0){
                all_moves.push_back("F" + this->all_squares[i]);
            }
            if (this->moves != player and this->players[player].flats > 0){
                all_moves.push_back("S" +this->all_squares[i]);

            }
            if (this->moves != player && this->players[player].capstones > 0){
                all_moves.push_back("C" + this->all_squares[i]);
            }
        }
    }

    for (int i=0;i<this->board.size();i++){
        if (this->board[i].size() > 0 && this->board[i].back().first == player && this->moves != player){
            vector<string> tmp_vect = this->generate_stack_moves(i);
            for(int j = 0 ; j < tmp_vect.size() ; j++) {
                all_moves.push_back(tmp_vect[j]);
            }
        }
    }
    return all_moves;
}



class MyPlayer{
    public:
        int player;
        int n;
        int time_left;
        MyPlayer();
        Game game;
        void play();
};

MyPlayer::MyPlayer(){

    char line[100];
    cin.getline(line,100);
    int data[3];
    int i = 0;
    stringstream ssin(line);
    while (ssin.good() && i < 3){
        ssin >> data[i];
        ++i;
    }
    this->player=data[0]-1;
    this->n=data[1];
    this->time_left=data[2];
    this->game = Game(this->n);
    this->play();
}

int getNeighbour(int player_id) {
  if(player_id==0)
    return 1;
  else
    return 0;
}

int max(int a,int b){
    return a<b?b:a;
}

int min(int a,int b){
    return a>b?b:a;
}

void isRoadUtil(vector<vector<int> > &A, int x, int y, int n) {
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

int getRoadLen(vector<vector<int> > A) {
  int x_min = A.size()+1, y_min = A.size()+1;
  int x_max = -1, y_max = -1;
  for(int i = 0 ; i < A.size() ; i++) {
    for(int j = 0 ; j < A[i].size() ; j++) {
      if(A[i][j] == -1) {
        if(i < x_min)
          x_min = i;
        if(j < y_min)
          y_min = j;
        if(i > x_max)
          x_max = i;
        if(j > y_max)
          y_max = j;
      }
    }
  }
  return max(y_max - y_min, x_max - x_min);
}

vector<vector<int> > clearNeg(vector<vector<int> > A) {
  for(int i = 0 ; i < A.size() ; i++) {
    for(int j = 0 ; j < A[i].size() ; j++) {
      if(A[i][j] == -1)
        A[i][j] = 0;
    }
  }
  return A;
}

int longRoad(vector<vector<pair<int, string> > > board, int player) {
  int N = sqrt(board.size());
  vector<vector<int> > stor_play;
  for(int i = 0 ; i < N ; i++) {
    vector<int> tmp_vect;
    for(int j = 0 ; j < N ; j++) {
      tmp_vect.push_back(0);
    }
    stor_play.push_back(tmp_vect);
  }
  for(int i = 0 ; i < board.size() ; i++) {
    int row = i % N;
    int col = i / N;
    if(board[i].size() > 0) {
      if(board[i].back().first == player && board[i].back().second != "S") {
        stor_play[row][col] = 1;
      }
    }
  }

  int road_len = 0;
  for(int i = 0 ; i < stor_play.size() ; i++) {
    for(int j = 0 ; j < stor_play[i].size() ; j++) {
      if(stor_play[i][j] == 1) {
        isRoadUtil(stor_play, i, j, N);
        road_len = max(road_len, getRoadLen(stor_play));
        stor_play = clearNeg(stor_play);
      }
    }
  }

  return road_len;
}

float evaluation(MyPlayer node) {

  int count_0 = 0, count_1 = 0, stand_0 = 0, stand_1 = 0;   // counts tiles/stacks with top/control ; counts number of standing walls ;
  int big_stack_0 = 0, big_stack_1 = 0;   // controlling big stacks ;
  int center_0 = 0, center_1 = 0;         // distance from center ;
  int flat_0 = 0, flat_1 = 0;

  for(int i = 0 ; i < node.game.board.size() ; i++) {
    if(node.game.board[i].size() > 0) {

      if(node.game.board[i].back().second == "S") {  // standing stones ;
        if(node.game.board[i].back().first == 0) // controlled by first player ;
          stand_0++;
        else
          stand_1++;
      }

      if(node.game.board[i].back().second == "F") {  // flats stones ;
        if(node.game.board[i].back().first == 0) // controlled by first player ;
          flat_0++;
        else
          flat_1++;
      }

      int row = i % node.game.n;
      int col = i / node.game.n;
      if(node.game.board[i].back().first == 0) {// controlled by first player ;
        count_0++;
        big_stack_0 += (node.game.board[i].size());
        center_0 += min((row - 0), (node.game.n - 1 - row)) + min((col - 0), (node.game.n - 1 - col));
      }
      else {
        count_1++;
        big_stack_1 += (node.game.board[i].size());
        center_1 += min((row - 0), (node.game.n - 1 - row)) + min((col - 0), (node.game.n - 1 - col));
      }
    }
  }

  int road_0 = longRoad(node.game.board, 0);
  int road_1 = longRoad(node.game.board, 1);

  // Normallize all functions first ;
  // Current function account for - # stack controlled , bigger stack controlled , flat stones and center pieces ;
  if(node.game.turn == 1) {
    road_0 = max(road_0 - 2, 0);
    //return 0.1*(center_1);
    return (0.1*(center_1)/(node.game.n*node.game.board.size())) + (0.1*flat_1/node.game.board.size()) + (0.1*big_stack_1/(node.game.max_flats*node.game.n)) + (0.2*road_1) - (0.15*road_0*road_0);
    //return (0.4*road_0) - (0.3*road_1*road_1) + (0.2*(flat_0 - flat_1)/node.game.board.size()) + (0.1*(big_stack_0 - big_stack_1)/node.game.max_flats) + (0.3*(count_0 - count_1)/node.game.board.size()) + (0.15*(center_0 - center_1));
  }
  else {
    road_1 = max(road_1 - 2, 0);
    //return 0.1*(center_0);
    return (0.1*(center_0)/(node.game.n*node.game.board.size())) + (0.1*flat_0/node.game.board.size()) + (0.1*big_stack_0/(node.game.max_flats*node.game.n)) + (0.2*road_0) - (0.15*road_1*road_1);
    //return (0.4*road_1) - (0.3*road_0*road_0) + (0.2*(flat_1 - flat_0)/node.game.board.size()) + (0.1*(big_stack_1 - big_stack_0)/node.game.max_flats) + (0.3*(count_1 - count_0)/node.game.board.size()) + (0.15*(center_1 - center_0));
  }
}

vector<string> sort_by_eval(MyPlayer node, vector<string> all_moves, bool maximizingPlayer) {
  string tmp_str;
  float tmp_val;
  vector<float> child_eval;

  for(int i = 0 ; i < all_moves.size() ; i++) {
    MyPlayer child = node;
    child.game.execute_move(all_moves[i]);
    child_eval.push_back(evaluation(child));
  }

  for(int i = 0 ; i < all_moves.size() ; i++) {
    for(int j = 0 ; j < i ; j++) {
      if(maximizingPlayer) {    // sort descending by evaluation fn
        if(child_eval[i] < child_eval[j]) {
          tmp_val = child_eval[i];
          child_eval[i] = child_eval[j];
          child_eval[j] = tmp_val;

          tmp_str = all_moves[i];
          all_moves[i] = all_moves[j];
          all_moves[j] = tmp_str;
        }
      }
      else {                    // sort ascending by evaluation fn
        if(child_eval[i] > child_eval[j]) {
          tmp_val = child_eval[i];
          child_eval[i] = child_eval[j];
          child_eval[j] = tmp_val;

          tmp_str = all_moves[i];
          all_moves[i] = all_moves[j];
          all_moves[j] = tmp_str;
        }
      }
    }
  }

  return all_moves;
}

float alphabeta(MyPlayer node, float alpha, float beta, int depth, bool maximizingPlayer, string &res) {
  float v;
  string temp_str;
  MyPlayer child = node;
  vector<string> all_moves = node.game.generate_all_moves(node.player);
  //all_moves = sort_by_eval(node, all_moves, maximizingPlayer);  // Yes, sorting was a bad idea ;

  if(depth==0 || all_moves.size()==0)
    return evaluation(node);

  if(maximizingPlayer) {
    v = (float)-INT_MAX;
    for(int i = 0 ; i < all_moves.size() ; i++) {
      child = node;
      child.game.execute_move(all_moves[i]);
      child.player=child.game.turn;
      float child_ab = alphabeta(child, alpha, beta, depth-1, false, temp_str);
      if(v < child_ab) {
        v = child_ab;
        res = all_moves[i];
        //cerr<<res<<" "<<depth<<" "<<child_ab<<endl;
      }
      alpha = max(alpha, v);
      if(beta <= alpha)
        break;
    }
    //cerr<<endl;
    return v;
  }

  else {
    v = (float)INT_MAX;
    for(int i = 0 ; i < all_moves.size() ; i++) {
      child = node;
      child.game.execute_move(all_moves[i]);
      child.player=child.game.turn;
      float child_ab = alphabeta(child, alpha, beta, depth-1, true, temp_str);
      if(v > child_ab) {
        v = child_ab;
        res = all_moves[i];
        //cerr<<res<<" "<<depth<<" "<<child_ab<<endl;
      }
      beta = min(beta, v);
      if(beta <= alpha)
        break;
    }
    //cerr<<endl;
    return v;
  }
}

int genMove(MyPlayer child,string move){
      child.game.execute_move_opponent(move,1-child.player);
      return longRoad(child.game.board, 1-child.player);
}

int checkRoadLen(MyPlayer node,string &change){
  MyPlayer child=node;
  vector<string> all_moves = child.game.generate_all_moves_opponent(1-node.player);
  int childRoadLength=0;
  for(int i=0;i<all_moves.size();i++){
      //MyPlayer childNew=node;
      int len = genMove(child,all_moves[i]);

      childRoadLength=len;
      if(len>=3){
        change=all_moves[i];
        break;
      }

  }
    return childRoadLength;
    //child.game.board;
}

string alphabetaUtil(MyPlayer node,int depth) {
  vector<string> all_moves = node.game.generate_all_moves(node.player);

    float alpha = (float)-INT_MAX, beta =(float) INT_MAX;
  bool maximizingPlayer = true;

	string val = "";
	//string change="";
  //int opponentLength=checkRoadLen(node,change);//opponent
  //int mylength=longRoad(node.game.board, node.player);
  /*if( mylength<opponentLength && opponentLength>=3)
  {
      string cg=change.substr(1);
     // cerr<<cg<<endl;
      if(node.game.board[node.game.square_to_num(cg)].size()==0){
          return change;
      }
  }*/

  alphabeta(node, alpha, beta, depth, maximizingPlayer, val);

	return val;
}

void MyPlayer::play(){
    if (this->player == 1){
        string move="";
        cin>>move ;
        this->game.execute_move(move);
    }
    int counter=0;
    int depth=2;
    while(1){
        if(counter<100){
            depth=2;
        }else if(counter < 300 && counter>=100){
            depth=3;
        }else {
            depth=4;
        }
        vector<string> all_moves = this->game.generate_all_moves(this->player);
        string move = alphabetaUtil(*this,depth);
        this->game.execute_move(move);
        move = move + '\n';
        cout<<move<<std::flush;
        cin>>move;
        this->game.execute_move(move);
        counter++;
    }
}
/*
    Flat count
    Standing stones, especially earlier in the game, especially if they can get on top of some stacks.
    Your colour of pieces in stacks, even in stacks controlled by opponents.
    Controlling big stacks.
    Having control in the centre of the board.
    Being close to finishing a road.
    Being closer than opponent to finishing a road, more so the closer the road is to being finished. Remember, if the count is even, the advantage goes to whoever has the turn.
    Having the option of spreading with a lot of flat gain.
    Having the option of spreading on top of large stacks.
    Some sneaky way of not counting spread options much if the opponent is able to spread on top of a stack before the spread is utilised.

    High eval if : road win , flat win , board completely filled ;
*/
int main(){
    MyPlayer mp;
    return 0;
}
