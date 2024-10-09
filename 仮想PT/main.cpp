//PT調査をシミュレーションによって生成

#include<iostream>

#include"householder.h"
#include"personal.h"
#include"visitors.h"
#include"area.h"
#include"setting_by_transportation.h"
#include"Generate_parson.h"

std::mt19937_64 seed(42);

int main() {
	
	//エリアの設定
	area make;

	//公共交通の設定
	setting_by_transportation transportation;

	//人物の設定
	std::vector<Generate_parson>residents(make.reverse_area_name.size());

	residents.at(0).generate_user_func(make.reverse_area_name[0], true, 3);

	return 0;

}