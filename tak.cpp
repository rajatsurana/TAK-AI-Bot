#include <iostream>
#include <vector>
using namespace std;
#define size 5

class Matrix{
	public:
		vector<int> arrArrVect[size][size];
		void validMove(int type,int i, int j,int dirn);
		void insert(int i,int j,int type);
		int blackFlatStoneLeft=21;
		int whiteFlatStoneLeft=21;
		int blackCapStoneLeft=1;
		int whiteCapStoneLeft=1;
		//enums
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
	switch type:
	case 11:
		//decrement the type of stone;
		whiteFlatStoneLeft-=1;
		break;
	case 12:
		blackFlatStoneLeft-=1;
		break;
	case 21:
		whiteFlatStoneLeft-=1;
		break;
	case 22:
		blackFlatStoneLeft--;
		break;
	case 31:
		whiteCapStoneLeft-=1;
		break;
	case 32:
		blackCapStoneLeft-=1;
		break;
	arrArrVect[i][j].push_back(type);
	//send signal of insertion to opponent
	//Fa1 -> Flat at a1
	//Sd3 -> standing at d3
	//Cb4 -> cap at b4
}
int main(){
    Matrix matrix;
    matrix.insert(0,0,11);
    cout<< matrix.arrArrVect[0][0].at(0)<<endl;
}
