#pragma once
#include "visitors.h"
#include<random>
#include<limits>


extern std::mt19937_64 seed;

visitors::visitors() {

	this->setting_func();

};

visitors::~visitors() {

};


enum Purpose_of_visit {
	Worker = 0,
	Sightseeing = 1
};

void visitors::setting_func() {

	//乱数の設定
	std::uniform_int_distribution<long long int> dist(0, std::numeric_limits<long long int>::max());


	//車の利用
	int use_car = dist(seed) % 10;

	//ttps://prtimes.jp/main/html/rd/p/000000282.000018246.html
	//車の利用を50％程度
	//新幹線　25％
	//飛行機　10％
	//その他　10％
	//→20％程度？

	if (use_car < 2) {
		//公共交通
		this->Use_Vehicle = false;
	}
	else {
		//車
		this->Use_Vehicle = true;
	}

	//目的
	this->Purpose_of_visit;

	int temp_purpose = dist(seed) % 10;

	//出張等と観光の比率
	if (temp_purpose < 6) {
		this->Purpose_of_visit = Worker;
	}
	else {
		this->Purpose_of_visit = Sightseeing;
	}

	//目的値
	this->aim = -1;

	//年間何回訪れるか

	std::poisson_distribution<int> dist2(7);

	int temp_poisson = 0;

	do {

		temp_poisson = dist2(seed);

	} while (temp_poisson == 0);

	//年間何回訪れるか
	this->how_many_time_per_year = temp_poisson;


	int hold_IC_temp = dist(seed) % 10;


	this-> hold_IC = hold_IC_temp < 6 ? true : false;

	return;

};

