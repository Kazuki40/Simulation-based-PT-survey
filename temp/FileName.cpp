#include<iostream>
#include<vector>
#include<string>


//移動について
std::vector<int> estimate_move_func(long long int time) {
	std::vector<int> ans;

	if (time <= 0) return ans; // ベースケース

	if (time == 1) {
		ans.push_back(-1); 
	}
	else if(time == 2){
		ans.push_back(-2); 
	}
	else {
		ans.push_back(time);
	}

	// 再帰呼び出し
	auto recursive_ans = estimate_move_func(time - 1);
	ans.insert(ans.end(), recursive_ans.begin(), recursive_ans.end());

	return ans;
}

int main() {
	estimate_move_func(9);
}