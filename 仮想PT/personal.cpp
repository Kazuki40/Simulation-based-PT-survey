#pragma once
#include "personal.h"
#include"func.h"
#include<iostream>
#include<random>
#include<limits>


extern std::mt19937_64 seed;

personal::personal() {

	//����
	this->Sex = -1;

	//�N��
	this->Age = -1;//0-120

	//�E�ƁE�w��
	this->Work_status = -1; //0:inemployed 1:employed 2:student


	//�Ԃ̗L��
	this->Hold_driving_license = -1;

	//�ʋ΂Ō������
	this->To_work_by_transportation = false;

	//������ʗ��p�m��
	this->Probability_of_transportation_weekdays = -1.0;

	//������ʗ��p�m��
	this->Probability_of_transportation_weekends = -1.0;

	calculate();
};

personal::~personal() {
	std::cout << "Calculation_of_person_complete" << std::endl;
};


//�l�̌v�Z
void personal::calculate() {
	std::uniform_int_distribution<long long int> dist(0, std::numeric_limits<long long int>::max());

	//std::cout << "personal::calculate()" << std::endl;
	//����


	this->Sex = Sex_s_test_function(dist(seed));


	//�N��	
	this->Age = Age_s_test_function(dist(seed));//0-120

	//�E�ƁE�w��
	this->Work_status = work_s_test_function(dist(seed), this->Age); //0:inemployed 1:employed 2:student

	//�ꏊ
	this->Work_place = -1;

	//�Ԃ̗L��

	this->Hold_driving_license = Hold_driving_license_test_function(dist(seed), this->Sex, this->Age);


	//�ʋ΂Ō������
	this->To_work_by_transportation = To_work_by_transportation_test_function(dist(seed), this->Work_status);


	std::uniform_real_distribution<> dist_double((double)0.0, (double)1.0);
	//������ʗ��p�m��

	this->Probability_of_transportation_weekdays = dist_double(seed);

	//������ʗ��p�m��
	this->Probability_of_transportation_weekends = dist_double(seed);

	this->hold_IC = hold_IC_test_function(dist(seed), this->Age);

	return;
}
