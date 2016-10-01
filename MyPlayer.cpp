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
        vector<vector<int>> board;
        int turn;
        Game(int n);
        vector<Player> players;
        int max_flats;
        int max_capstones;
        int max_movable;
        int max_down;
        int max_up;
        char max_left;
        vector<string> all_squares;
        string square_to_string(int i);
        int square_to_num(string square_string);
        void execute_move(string move_string);
        void partition(int n);
        void check_valid(int square, char direction, vector<vector<int>> partition );
        vector<string> generate_stack_moves(int square);
        vector<string> generate_all_moves(Player player);
        vector<vector<int>> partition(int n);
};

Game::Game(int n){
    this->n=n;
    this->total_squares=n*n;
    vector<vector<int>> v;
    this->board=v;/////////////////////////////////////////////////////
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
    if (square_string.size() != 2)){
        return -1;
    }
    if (!(isalpha(square_string[0])) || !(islower(square_string[0])) || !(isdigit(square_string[1]))){
        return -1;
    }
    int row = ((int) square_string[0])- 96;
    int col = atoi(square_string[1])
    if (row < 1 || row > this->n || col < 1 || col > this->n)
        return -1
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
    s = s + to_string(col + 1);
    return s;
}
void Game::execute_move(string move_string){
	///Execute move
    int current_piece =0;
	if (this->turn == 0){
		this->moves += 1;
    }
	if (this->moves != 1){
		current_piece = this->turn;
    }
	else{
		current_piece = 1 - this->turn
    }
	if (isalpha(move_string[0])){
		square = this->square_to_num(move_string[1:]);//////////////////
		if (move_string[0] == 'F' || move_string[0] == 'S'){
			this->board[square].push_back((current_piece, move_string[0]));/////////////????????????
			this->players[current_piece].flats -= 1;
		}else if (move_string[0] == 'C'){
			this->board[square].push_back((current_piece, move_string[0]));
			this->players[current_piece].capstones -= 1;
        }
	}else if (isdigit(move_string[0])){
		count = (int)move_string[0];
		square = this->square_to_num(move_string.substr(1,3));///1:3
		char direction = move_string[3];
		if (direction == '+'){
			change = this->n;
        }else if (direction == '-'){
			change = -this->n;
        }else if (direction == '>'){
			change = 1;
        }else if (direction == '<'){
			change = -1;
        }
		int prev_square = square
		for( i =4;i< move_string.size();i++){
			next_count = (int)move_string[i]
			next_square = prev_square + change;
			if (this->board[next_square].size() > 0) && (this->board[next_square][-1][1] == 'S'){
				this->board[next_square][-1] = (this->board[next_square][-1][0], 'F');
            }
			if (next_count - count == 0){
				this->board[next_square] += this->board[square][-count:];
			}else{
				this->board[next_square] += this->board[square][-count:-count+next_count];
            }
			prev_square = next_square
			count -= next_count
        }
		count = (int)move_string[0];
		this->board[square] = this->board[square][:-count]
    }
	this->turn = 1 - this->turn;
}
void Game::partition(int n){
	///Generates all permutations of all partitions of n
	vector<vector<int>> part_list;
    vector<int> xx;
    xx.push_back(n);
	part_list.push_back(xx);////////////////
	for (int x=1; x<n;x++){
		for( y : this->partition(n - x)){/////////////////////
			part_list.push_back([x] + y);//////////////////
        }
    }
	return part_list;
}

bool Game::check_valid(int square, char direction, vector<vector<int>> partition){
	//For given movement (partition), check if stack on
	///square can be moved in direction. Assumes active player
	///is topmost color

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
	for (i=0;i< partition.size();i++){
		next_square = square + change * (i + 1);
		if (this->board[next_square].size() > 0 && this->board[next_square][-1][1] == 'C'){
			return 0;
        }
		if (this->board[next_square].size() > 0 && this->board[next_square][-1][1] == 'S' && i != partition.size() - 1){
            return 0;
        }
		if (i == partition.size() - 1 && this->board[next_square] > 0 && this->board[next_square][-1][1] == 'S' && partition[i] > 1){
			return 0;
        }
		if (i == partition.size()  - 1 && this->board[next_square].size()  > 0 && this->board[next_square][-1][1] == 'S' && this->board[square][-1][1] != 'C'){
			return 0;
        }
    }
	return 1;
}
vector<string> Game::generate_stack_moves(int square){
	//Generate stack moves from square
	//Assumes active player is topmost color
	vector<string> all_moves;
	int r = square % this->n;
	int c = square / this->n;
	int size = this->board[square].size();
	char dirs[4] = ['+', '-', '<', '>'];
	int up = this->n - 1 - c;
	int down = c;
	int right = this->n - 1 - r;
	int left = r;
	int rem_squares[] = [up, down, left, right]
	for(int num=0; num <min(size, this->n);num++){
		vector<vector<int>> part_list = this->partition(num + 1)
		for di in range(4){
			part_dir = [part for part in part_list if len(part) <= rem_squares[di]];//////////////////////////////
			# sys.stderr.write(this->all_squares[square] + " " + dirs[di] + " " + str(part_dir) + '\n');////////////////
			for( part in part_dir:){
				if (this->check_valid(square, dirs[di], part)){
					part_string = ''.join([str(i) for i in part]);//////////////////////////
					all_moves.push_back(str(sum(part)) + this->all_squares[square] + dirs[di] + part_string);/////////
                }
            }
        }
    }
	return all_moves;
}
vector<string> Game::generate_all_moves(Player player){
	///Generate all possible moves for player
	///Returns a list of move strings
	vector<string> all_moves;
	for (int i=0; i<this->board;i++){
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
		if (this->board[i].size() > 0 && this->board[i][-1][0] == player){
			all_moves += this->generate_stack_moves(i);///////////////////////////
        }
    }
	return all_moves;
}

class MyPlayer{
    public:
        int player;
        int n;
        int time_left;
        Game game;
        MyPlayer();
        void play();
};

MyPlayer::MyPlayer(){
    string data[3] = sys.stdin.readline().strip().split();///////////////
	this->player = (int)data[0] - 1;
	this->n = (int)data[1]);
	this->time_left = (int)data[2];
	this->game = Game(this->n);
	this->play();
}

void MyPlayer::play(){
    if (this->player == 1){
		cin>>move ;/////////////strip
		this->game.execute_move(move);
    }
	while(1){
		vector<string> all_moves = this->game.generate_all_moves(this->player);
		string move = all_moves[rand()%all_moves.size()];///////////////////////rand()
		this->game.execute_move(move);
		move = move + '\n';
		cout<<"Possible moves: "<< str(all_moves) << '\n';
		cout<<"Chosen move: "<< move<<endl;
		cout<<move<<endl;
		cout.flush();
		cin>>move;/////////////strip
		this->game.execute_move(move);
    }
}
int main(){
    MyPlayer mp();
    return 0;
}
//https://github.com/TehShrike/tak-game
