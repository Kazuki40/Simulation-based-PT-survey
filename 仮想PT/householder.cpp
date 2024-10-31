#pragma once
#include "householder.h"
#include<random>
#include<iostream>
#include<algorithm>



extern std::mt19937_64 seed;

householder::householder()
{
	//人数
	std::poisson_distribution<int> num_of_members(1.5);

	do {

		Number_of_household_members = num_of_members(seed);

	} while (Number_of_household_members == 0);

	personal_list.resize(Number_of_household_members);
	std::cout << Number_of_household_members << std::endl;

	//ソート
	std::sort(personal_list.begin(), personal_list.end(), [](const personal& a, const personal& b) {
		return a.Age > b.Age;
		});

	if (personal_list.size() == 1) {
		if (personal_list[0].Age <= 18) {
			std::uniform_int_distribution<long long int> dist(18, 65);
			personal_list[0].Age = dist(seed);
			personal_list[0].Work_status = 5;

		}
	}
	else {
		if ((personal_list[0].Age > 20) && (personal_list[0].Age <= 65)) {
			auto age = personal_list[0].Age - personal_list[1].Age;

			if (age >= 13) {
				personal_list[1].Age = personal_list[0].Age;
			}

			if (personal_list[0].Sex == personal_list[1].Sex) {
				if (personal_list[0].Sex == 1) {
					personal_list[1].Sex = 0;
				}
				else if (personal_list[1].Sex == 0) {
					personal_list[0].Sex = 1;
				}
			}

		}

		if (personal_list[personal_list.size() - 1].Age <= 18) {
			bool flag = false;
			int temp_age = -1;

			for (auto num = 0; num < (personal_list.size() - 1); num++) {

				if ((20 < personal_list[num].Age) && (personal_list[num].Age <= 65)) {
					flag = true;
				}

				if (30 >= personal_list[num].Age) {
					if (num != 0) {
						temp_age = std::max(temp_age, personal_list[num].Age);
					}
				}


			}


			//親の設定
			if (flag == false) {

				std::uniform_int_distribution<long long int> dist2(20+ temp_age, 65);

				personal_list[0].Age = dist2(seed);
				personal_list[0].Work_status = 5;
			}
		}
	}

	//世帯ごとの設定
	long int user_hold_car = 0;
	for (auto num_2 = 0; num_2 < (personal_list.size()); num_2++) {
		if (personal_list[num_2].Hold_driving_license == 1) {
			user_hold_car++;
		}
	}
	std::uniform_int_distribution<long long int> dist3(0, user_hold_car);
	this->Number_of_vehicle = dist3(seed);
	std::uniform_int_distribution<long long int> dist4(0, personal_list.size());
	this->Number_of_cycle = dist4(seed);
}

householder::~householder()
{
}