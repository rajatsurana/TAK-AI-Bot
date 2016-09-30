#include <bits/stdc++.h>
using namespace std;

void place(int stones, int index, vector<int> A, vector< vector<int>>& res) {
	if(stones==0) {
		res.push_back(A);
		return;
	}
	if(index==A.size()-1) {
		A[index] = stones;
		res.push_back(A);
		return;
	}
	for(int j = 1 ; j < stones+1 ; j++) {
		vector<int> tmp;
		for(int k = 0 ; k < A.size() ; k++)
			tmp.push_back(A[k]);
		A[index] = j;
		place(stones-j, index+1, A, res);
		A = tmp;
	}
	return;
}

void place_wrapper(int stones, int index, vector<int> A, vector< vector<int>>& res, int width) {
	if(A.size()==1) {
		res.push_back(A);
		return;
	}
    int stackSize=min(width, stones);
	for(int k = 1 ; k <= stackSize ; k++) {//zero stones cant be placed so k=1
		vector<int> tmp;
		for(int l = 0 ; l < A.size() ; l++){
			tmp.push_back(A[l]);
		}
		A[index] = k;

		place(stackSize-k, index+1, A, res);//k stones placed

		A = tmp;
	}
	return;
}
int countCells(int direction,int i,int j,int width){
    int numCells=0;
    switch (direction){
        case 0://right
            numCells=width -(i+1);
            break;
        case 1://left
            numCells=i;
            break;
        case 2://up
            numCells=j;
            break;
        case 3://down
            numCells=width -(j+1);
            break;
            
    }
}
void filterMoves(vector<int> &possibleMoves,vector<vector<int>> res,int numCells){
    //#nonZeroElements= atMax(numCells);
    for(int i = 0 ; i < res.size() ; i++) {
        int counterNonZero = 0;
		for(int j = 0 ; j < res[i].size() ; j++) {
			if(res[i][j]!=0){
			    counterNonZero = counterNonZero+1;
			}
		}
		if(counterNonZero<=numCells){
		    possibleMoves.push_back(i);
		    //or possibleMoves.push_back(res[i]);if possibleMoves is vector<vector<int>>
		}
	}
}
int main() {
    
	vector<vector<int>> res;
	vector<int> A(4, 0);//stone drop sequence
	int stones = 9, index = 0, width = 5;
	//place(stones, index, A, res);
	A[0] = stones;
	place_wrapper(stones, index, A, res, width);
	//now i have
	//incorporate i and j---i.e. position
    //incorporate direction
    //consider the number of blanks
    //#blanks:
    //  toLeft= i;
    //  toRight = width-(i+1)
    //  toUp= j;
    //  toDown = width- (j+1)
    //#(non zero elements in res = atMax(#(blanks))
    int direction=0, i=2, j=2;
    int numCells=countCells(direction,i,j,width);
    //cout<<numCells<<endl;
    vector<int> possibleMoves;
    filterMoves(possibleMoves,res, numCells);
    //cout<<possibleMoves.size()<<" size"<<endl;
    for(int i = 0 ; i < possibleMoves.size() ; i++) {
        int k=possibleMoves[i];
		for(int j = 0 ; j < res[k].size() ; j++) {
			cout<<res[k][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}