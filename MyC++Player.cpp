#include <bits/stdc++.h>
using namespace std;

class Game{
    public:
        int n;
        int total_squares;
        vector<vector<string>> board;
        int turn;
        Game(int n);
        vector<Player> players;
        int max_flats;
        int max_capstones;
        int max_movable;
        int max_down;
        int max_up;
        char max_left;
        string square_to_string(int i);
        int square_to_num(string square_string);
        void execute_move(string move_string);
        void partition(int n);
        check_valid(int square, char direction, partition )
        void generate_stack_moves(int square);
        void generate_all_moves(Player player);
        vector<vector<int>> partition(int n);
}
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
Game::Game(int n){
    this->n=n;
    this->total_squares=n*n;
    vector<vector<string>> v;
    this->board=v;
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
string Game::square_to_string(int square):
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
		if isalpha(move_string[0]){
			square = self.square_to_num(move_string[1:])
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
		return part_list

	def check_valid(self, square, direction, partition):
		'''For given movement (partition), check if stack on
		square can be moved in direction. Assumes active player
		is topmost color
		'''
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
			if (self.board[next_square].size() > 0 && self.board[next_square][-1][1] == 'S' && i != partition.size() - 1){
                	return 0;
            }
			if i == len(partition) - 1 and len(self.board[next_square]) > 0 and self.board[next_square][-1][1] == 'S' and partition[i] > 1:
				return False
			if i == len(partition) - 1 and len(self.board[next_square]) > 0 and self.board[next_square][-1][1] == 'S' and self.board[square][-1][1] != 'C':
				return False
        }
		return True

	def generate_stack_moves(self, square):
		'''Generate stack moves from square
		Assumes active player is topmost color
		'''

		all_moves = []
		r = square % self.n
		c = square / self.n
		size = len(self.board[square])
		dirs = ['+', '-', '<', '>']
		up = self.n - 1 - c
		down = c
		right = self.n - 1 - r
		left = r
		rem_squares = [up, down, left, right]
		for num in xrange(min(size, self.n)):
			part_list = self.partition(num + 1)
			for di in range(4):
				part_dir = [part for part in part_list if len(part) <= rem_squares[di]]
				# sys.stderr.write(self.all_squares[square] + ' ' + dirs[di] + ' ' + str(part_dir) + '\n')
				for part in part_dir:
					if self.check_valid(square, dirs[di], part):
						part_string = ''.join([str(i) for i in part])
						all_moves.append(str(sum(part)) + self.all_squares[square] + dirs[di] + part_string)
		return all_moves

	def generate_all_moves(self, player):
		'''Generate all possible moves for player
		Returns a list of move strings
		'''
		all_moves = []
		for i in xrange(len(self.board)):
			if len(self.board[i]) == 0:
				if self.players[player].flats > 0:
					all_moves.append('F' + self.all_squares[i])
				if self.moves != player and self.players[player].flats > 0:
					all_moves.append('S' + self.all_squares[i])
				if self.moves != player and self.players[player].capstones > 0:
					all_moves.append('C' + self.all_squares[i])
		for i in xrange(len(self.board)):
			if len(self.board[i]) > 0 and self.board[i][-1][0] == player:
				all_moves += self.generate_stack_moves(i)
		return all_moves

class RandomPlayer:

	def __init__(self):
		data = sys.stdin.readline().strip().split()
		self.player = int(data[0]) - 1
		self.n = int(data[1])
		self.time_left = int(data[2])
		self.game = Game(self.n)
		self.play()

	def play(self):
		if self.player == 1:
			move = sys.stdin.readline().strip()
			self.game.execute_move(move)
		while True:
			all_moves = self.game.generate_all_moves(self.player)
			move = all_moves[random.randint(0, len(all_moves)-1)]
			self.game.execute_move(move)
			move = move + '\n'
			sys.stderr.write('Possible moves: ' + str(all_moves) + '\n')
			sys.stderr.write('Chosen move: ' + move)
			sys.stdout.write(move)
			sys.stdout.flush()
			move = sys.stdin.readline().strip()
			self.game.execute_move(move)

random_player = RandomPlayer()
