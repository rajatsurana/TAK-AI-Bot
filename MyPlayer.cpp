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
        bool check_valid(int square, char direction, vector<int> partition );
        vector<string> generate_stack_moves(int square);
        vector<string> generate_all_moves(int player);
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
    //cerr<<row<<" row"<<endl;
    int col = (int)square_string[1] - (int)'0';
    //cerr<<col<<" col"<<endl;
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
		//cerr<<move_string<<" isalpha"<<endl;
		//cerr<<move_string[0]<<" isalphabhai"<<endl;
		//cerr<<count<<" isalphaCount"<<endl;
        //cerr<<move_string.substr(1)<<" meri square string"<<endl;
        square = this->square_to_num(move_string.substr(1));////////////////// hope this clears
        pair<int, string> tmp_pair (current_piece, string(1,move_string[0]));
        if (move_string[0] == 'F' || move_string[0] == 'S'){
			//cerr<<move_string[0]<<" if isalpha"<<endl;
			//cerr<<square<<" square isalpha"<<endl;
            this->board[square].push_back(tmp_pair);/////////////????????????
            this->players[current_piece].flats -= 1;

        }
        else if (move_string[0] == 'C'){
			//cerr<<move_string[0]<<" elif isalpha"<<endl;
                this->board[square].push_back(tmp_pair);
                this->players[current_piece].capstones -= 1;
        }
        //cerr<<"move_string[0]"<<" isalpha2"<<endl;
    }
  else if (isdigit(move_string[0])){

        count = (int)move_string[0]-(int)'0';
        //cerr<<count<<" isdigit"<<endl;
        //cerr<<move_string<<" meri square string"<<endl;
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
                    all_moves.push_back(push + this->all_squares[square] + dirs[di] + part_string);/////////
                }
            }
        }
    }
    return all_moves;
}

vector<string> Game::generate_all_moves(int player){
    ///Generate all possible moves for player
    ///Returns a list of move strings
    vector<string> all_moves;
    for (int i=0; i<this->board.size();i++){/////////////////////
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
        if (this->board[i].size() > 0 && this->board[i].back().first == player){
            vector<string> tmp_vect = this->generate_stack_moves(i);
            for(int j = 0 ; j < tmp_vect.size() ; j++) {
                all_moves.push_back(tmp_vect[j]);
            }
        }
    }
    return all_moves;
}


int evaluation() {
  return 1;
}

class MyPlayer{
    public:
        int player;
        int n;
        int time_left;
        MyPlayer();
        Game game;
        void play();
        int alphabeta(int alpha, int beta, int depth, bool maximizingPlayer, string &res, vector<string> all_moves);
        string alphabetaUtil();
};

MyPlayer::MyPlayer(){
    //cerr<<"line88"<<endl;
    char line[100];
    cin.getline(line,100);
    string data[3];
    int i = 0;
    //cerr<<"line"<<endl;

    stringstream ssin(line);
    while (ssin.good() && i < 3){
        ssin >> data[i];
        //cerr<<data[i]<<" data"<<endl;
        ++i;
    }

    /*modify
    char *cstr = new char[data[0].length() + 1];
    strcpy(cstr, data[0].c_str());
    scanf(cstr,"%d",this->player);//
    this->player =  this->player - 1;

    char *cstr2 = new char[data[1].length() + 1];
    strcpy(cstr2, data[1].c_str());
    sprintf(cstr2,"%d",this->n);//data[1]
    char *cstr3 = new char[data[2].length() + 1];
    strcpy(cstr3, data[2].c_str());
    sprintf(cstr3,"%d",this->time_left);//2
    *///modify
    this->player=2;//stoi(data[0]);//2
    this->n=5;//stoi(data[1]);//5
    this->time_left=40;//stoi(data[2]);//40

    //cerr<<"line88"<<endl;
    this->game = Game(this->n);
    //cerr<<"line8"<<endl;
    this->play();
}

int MyPlayer::alphabeta(int alpha, int beta, int depth, bool maximizingPlayer, string &res, vector<string> all_moves) {
  int v;
  string temp_str;
  vector<string> tmp_moves;
  //vector<string> all_moves = this->game.generate_all_moves(this->player);
  MyPlayer child = *this;

  if(depth==0 || all_moves.size()==0)
    return evaluation();  //return evaluation(node->game->board); // to implement

  if(maximizingPlayer) {
    v = -INT_MAX;
    for(int i = 0 ; i < all_moves.size() ; i++) {
      //cerr<<"depth : "<<depth<<"checking move : "<<all_moves[i]<<endl;
      child = *this;
      child.game.execute_move(all_moves[i]);
      tmp_moves = child.game.generate_all_moves(child.player);

      int child_ab = child.alphabeta(alpha, beta, depth-1, false, temp_str, tmp_moves);
      if(v < child_ab) {
        v = child_ab;
        if(depth==2) {
          res = all_moves[i];
          cerr<<"res : "<<res<<endl;
        }
      }
      alpha = max(alpha, v);
      if(beta <= alpha)
        break;
    }
    return v;
  }

  else {
    v = INT_MAX;
    for(int i = 0 ; i < all_moves.size() ; i++) {
      //cerr<<"depth : "<<depth<<"checking move : "<<all_moves[i]<<endl;
      child = *this;
      child.game.execute_move(all_moves[i]);
      tmp_moves = child.game.generate_all_moves(child.player);

      int child_ab = child.alphabeta(alpha, beta, depth-1, false, temp_str, tmp_moves);
      if(v > child_ab) {
        v = child_ab;
        if(depth==2) {
          res = all_moves[i];
          cerr<<"res : "<<res<<endl;
        }
      }
      beta = min(beta, v);
      if(beta <= alpha)
        break;
    }
    return v;
  }
}

string MyPlayer::alphabetaUtil() {
  //cerr<<"in alpbetUtil\n";
  vector<string> all_moves = this->game.generate_all_moves(this->player);
  cerr<<all_moves.size()<<endl;
	int depth = 2, alpha = -INT_MAX, beta = INT_MAX;
	bool maximizingPlayer = true;
	string val = "";
	this->alphabeta(alpha, beta, depth, maximizingPlayer, val, all_moves);
  cerr<<"val : "<<val<<endl;
	return val;
}

void MyPlayer::play(){
	/*
  if (this->player == 1){
        string move="";
        cin>>move ;/////////////strip
        cerr<<move<<"inputmove"<<endl;
        this->game.execute_move(move);
  }
  */
  //int i=0;
    while(1){
        vector<string> all_moves = this->game.generate_all_moves(this->player);
        //cerr<<all_moves[0]<<all_moves[1]<<all_moves[2]<<all_moves.size()<<endl;
        //string move = all_moves[0];///////////////////////rand() correct//rand()%all_moves.size() ; add alphabeta here ;
        cerr<<"before util\n";
        string move = this->alphabetaUtil();
        this->game.execute_move(move);
        cerr<<move<<"outmove"<<endl;
        move = move + '\n';
        //cout<<"Possible moves: "<< str(all_moves) << '\n';
        //cout<<"Chosen move: "<< move<<endl;
        cout<<move<<std::flush;

        cin>>move;/////////////strip
        cerr<<move<<"inputsmove"<<endl;
        this->game.execute_move(move);
        cerr<<move<<"execsmove"<<endl;
    }
}

int main(){
    //cerr<<"line1"<<endl;

    MyPlayer mp;
    return 0;
}
