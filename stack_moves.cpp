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

int main() {
   
	vector<vector<int>> res;
	vector<int> A(4, 0);//stone drop sequence
	int stones = 9, index = 0, width = 5;
	//place(stones, index, A, res);
	A[0] = stones;
	place_wrapper(stones, index, A, res, width);

	for(int i = 0 ; i < res.size() ; i++) {
		for(int j = 0 ; j < res[i].size() ; j++) {
			cout<<res[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}