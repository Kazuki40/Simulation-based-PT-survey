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

	//�����̐ݒ�
	std::uniform_int_distribution<long long int> dist(0, std::numeric_limits<long long int>::max());


	//�Ԃ̗��p
	int use_car = dist(seed) % 10;

	//ttps://prtimes.jp/main/html/rd/p/000000282.000018246.html
	//�Ԃ̗��p��50�����x
	//�V�����@25��
	//��s�@�@10��
	//���̑��@10��
	//��20�����x�H

	if (use_car < 2) {
		//�������
		this->Use_Vehicle = false;
	}
	else {
		//��
		this->Use_Vehicle = true;
	}

	//�ړI
	this->Purpose_of_visit;

	int temp_purpose = dist(seed) % 10;

	//�o�����Ɗό��̔䗦
	if (temp_purpose < 6) {
		this->Purpose_of_visit = Worker;
	}
	else {
		this->Purpose_of_visit = Sightseeing;
	}

	//�ړI�l
	this->aim = -1;

	//�N�ԉ���K��邩

	std::poisson_distribution<int> dist2(7);

	int temp_poisson = 0;

	do {

		temp_poisson = dist2(seed);

	} while (temp_poisson == 0);

	//�N�ԉ���K��邩
	this->how_many_time_per_year = temp_poisson;


	int hold_IC_temp = dist(seed) % 10;


	this-> hold_IC = hold_IC_temp < 6 ? true : false;

	return;

};

