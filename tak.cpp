#include <iostream>
#include <vector>
using namespace std;
#define size 5

struct Matrix{
	public:
		vector<int> arrArrVect[size][size];
		// 11 white flat stone
		// 12 black flat stone
		// 21 white standing stone
		// 22 black standing stone
		// 31 white cap stone
		// 32 black cap stone
};
int main(){
    Matrix matrix;
    matrix.arrArrVect[0][0].push_back(1);
    cout<< matrix.arrArrVect[0][0].at(0)<<endl;
}