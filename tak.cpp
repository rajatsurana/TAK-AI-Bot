#include <iostream>
#include <vector>
using namespace std;
#define size 5

class Matrix{
	public:
		vector<int> arrArrVect[size][size];
		validMove(int type,int i, int j,int dirn);
		insert(int i,int j,int type);
		// 11 white flat stone
		// 12 black flat stone
		// 21 white standing stone
		// 22 black standing stone
		// 31 white cap stone
		// 32 black cap stone
};

void Matrix::validMove(int type,int i, int j,int dirn){//type=(in/out)
	int posX=i;
	int posY=j;
	int direction=dirn;
}
void Matrix::insert(int i,int j,int type){
	arrArrVect[i][j].push_back(type);
}
int main(){
    Matrix matrix;
    matrix.insert(0,0,11);
    cout<< matrix.arrArrVect[0][0].at(0)<<endl;
}
