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
        vector<vector<pair<int, string>>> board;
        int turn;
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
        vector<vector<int>> partition(int n);
};

Game::Game(int n){
    this->n=n;
    this->total_squares=n*n;
    vector<vector<pair<int, string>>> v(n*n); // initialized with n*n empty vectors ; still think for stack ;
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
    int col = (int)square_string[1];
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
    s = s + to_string(col + 1);
    return s;
}

void Game::execute_move(string move_string){
    ///Execute move
    int current_piece = 0;
    int square, count, next_square, next_count;
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
        square = this->square_to_num(move_string.substr(1,3));////////////////// hope this clears
        pair<int, string> tmp_pair (current_piece, string(1,move_string[0]));
        if (move_string[0] == 'F' || move_string[0] == 'S'){
            this->board[square].push_back(tmp_pair);/////////////????????????
            this->players[current_piece].flats -= 1;
        }
        else if (move_string[0] == 'C'){
                this->board[square].push_back(tmp_pair);
                this->players[current_piece].capstones -= 1;
        }
    }
  else if (isdigit(move_string[0])){
        count = (int)move_string[0];
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
            next_count = (int)move_string[i];
            next_square = prev_square + change;
            if (this->board[next_square].size() > 0 && this->board[next_square].back().second == 'S'){
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
        count = (int)move_string[0];
    vector<pair<int, string>> tmp_vect;
    for(int k = 0 ; k < this->board[square].size() - count ; k++) {
      tmp_vect.push_back(this->board[square][k]);
    }
        this->board[square] = tmp_vect;
  }
    this->turn = 1 - this->turn;
}

vector<vector<int>> Game::partition(int n){
    ///Generates all permutations of all partitions of n
    vector<vector<int>> part_list, tmpList;
    vector<int> xx ;///////////
    xx.push_back(n);
    part_list.push_back(xx);//////////////// correct

    for(int x = 1 ; x < n ; x++){
        tmpList = this->partition(n - x);
        for(int y = 0 ; y < tmpList.size() ; y++) {
            vector<int> tmp_vect { x };
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
    for (i=0;i < partition.size();i++){
        next_square = square + change * (i + 1);
        if (this->board[next_square].size() > 0 && this->board[next_square].back().second == 'C'){
            return false;
    }
        if (this->board[next_square].size() > 0 && this->board[next_square].back().second == 'S' && i != partition.size() - 1){
      return false;
    }
        if (i == partition.size() - 1 && this->board[next_square] > 0 && this->board[next_square].back().second == 'S' && partition[i] > 1){
            return false;
    }
        if (i == partition.size()  - 1 && this->board[next_square].size()  > 0 && this->board[next_square].back().second == 'S' && this->board[square].back().second != 'C'){
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
        vector<vector<int>> part_list = this->partition(num + 1);
        for (int di=0;di<4;di++){
            vector<vector<int>> part_dir;
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
                        part_string =part_string + to_string(part[j]);
                        part_sum = part_sum + part[j];
                    }
                    all_moves.push_back(to_string(part_sum) + this->all_squares[square] + dirs[di] + part_string);/////////
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
    
    char line[100];
    cin.getline(line,100);
    string data[3];
    int i = 0;
    stringstream ssin(line);
    while (ssin.good() && i < 3){
        ssin >> data[i];
        ++i;
    }
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
    this->game = Game(this->n);
    this->play();
}

void MyPlayer::play(){
  if (this->player == 1){
        string move;
        cin>>move ;/////////////strip
        this->game.execute_move(move);
  }
    while(1){
        vector<string> all_moves = this->game.generate_all_moves(this->player);
        string move = all_moves[rand()%all_moves.size()];///////////////////////rand() correct
        this->game.execute_move(move);
        move = move + '\n';
        //cout<<"Possible moves: "<< str(all_moves) << '\n';
        cout<<"Chosen move: "<< move<<endl;
        cout<<move<<std::flush;
        cin>>move;/////////////strip
        this->game.execute_move(move);
  }
}
int main(){
    //MyPlayer mp();
    return 0;
}
//https://github.com/TehShrike/tak-game