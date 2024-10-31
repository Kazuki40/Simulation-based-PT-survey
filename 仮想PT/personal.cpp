#pragma once
#include "personal.h"
#include"func.h"
#include<iostream>
#include<random>
#include<limits>


extern std::mt19937_64 seed;

personal::personal() {

	//性別
	this->Sex = -1;

	//年齢
	this->Age = -1;//0-120

	//職業・学生
	this->Work_status = -1; //0:inemployed 1:employed 2:student


	//車の有無
	this->Hold_driving_license = -1;

	//通勤で公共交通
	this->To_work_by_transportation = false;

	//公共交通利用確率
	this->Probability_of_transportation_weekdays = -1.0;

	//公共交通利用確率
	this->Probability_of_transportation_weekends = -1.0;

	calculate();
};

personal::~personal() {
	std::cout << "Calculation_of_person_complete" << std::endl;
};


//個人の計算
void personal::calculate() {
	std::uniform_int_distribution<long long int> dist(0, std::numeric_limits<long long int>::max());

	//std::cout << "personal::calculate()" << std::endl;
	//性別


	this->Sex = Sex_s_test_function(dist(seed));


	//年齢	
	this->Age = Age_s_test_function(dist(seed));//0-120

	//職業・学生
	this->Work_status = work_s_test_function(dist(seed), this->Age); //0:inemployed 1:employed 2:student

	//場所
	this->Work_place = -1;

	//車の有無

	this->Hold_driving_license = Hold_driving_license_test_function(dist(seed), this->Sex, this->Age);


	//通勤で公共交通
	this->To_work_by_transportation = To_work_by_transportation_test_function(dist(seed), this->Work_status);


	std::uniform_real_distribution<> dist_double((double)0.0, (double)1.0);
	//公共交通利用確率

	this->Probability_of_transportation_weekdays = dist_double(seed);

	//公共交通利用確率
	this->Probability_of_transportation_weekends = dist_double(seed);

	this->hold_IC = hold_IC_test_function(dist(seed), this->Age);

	return;
}
