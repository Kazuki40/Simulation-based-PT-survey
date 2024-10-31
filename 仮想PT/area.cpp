#pragma once
#include "area.h"
#include "template.h"
#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>
#include <limits>
#include<numbers>
#include<numeric>


area::area() {
	this->Number_of_areas = 0;
	this->X_distance_of_Area = 0;
	this->Y_distance_of_Area = 0;

}

void area::set_start() {
	create_area();
	calculation_of_costs();
}

area::~area() {

	std::cout << "delete area" << std::endl;

}


void area::overall_value() {
	//エリアの事前情報
	std::cout << "How many areas do you envision?" << std::endl;
	std::cin >> this->Number_of_areas;

	std::cout << "How many in the x direction?" << std::endl;
	std::cin >> this->X_distance_of_Area;

	std::cout << "How many in the y direction?" << std::endl;
	std::cin >> this->Y_distance_of_Area;

	if (Number_of_areas > (X_distance_of_Area * Y_distance_of_Area)) {
		std::cout << "The number of areas is too Small" << std::endl;
		exit(54);
	}

	this->Area_list_name.resize(this->X_distance_of_Area, std::vector<std::string>(this->Y_distance_of_Area, " "));

	//x，ｙ方向の設定
	return;
}

void area::create_area_detail() {

	//詳細情報の記入
	std::cout << "Please write to Area's infomation" << std::endl << "number: Area_name x y" << std::endl;

	for (this->Loop_values = 0; this->Loop_values < this->Number_of_areas; this->Loop_values++) {

		std::cout << this->Loop_values << ":";
		std::string temp_area_name;
		long int temp_x;
		long int temp_y;
		//場所の設定
		std::cin >> temp_area_name >> temp_x >> temp_y;

		auto temp_tuple = std::make_tuple(temp_x, temp_y);

		bool flag = false;

		//判定
		if (Area_list.count(temp_tuple) == 1) {
			std::cout << "This area already wrote it" << std::endl;
			flag = true;
		}

		std::map<std::tuple<long int, long int>, std::string>::iterator it;

		for (it = Area_list.begin(); it != Area_list.end(); it++) {
			if (it->second == temp_area_name) {
				std::cout << "This area already wrote it" << std::endl;
				flag = true;
			}
		}

		if (flag == true) {
			this->Loop_values--;
		}
		else {
			Area_list.emplace(temp_tuple, temp_area_name);
			this->Area_list_name[temp_x][temp_y] = temp_area_name;
			this->area_name.emplace(temp_area_name, this->Loop_values);
			this->reverse_area_name.emplace(this->Loop_values, temp_area_name);
		}



	}
	return;
}

void area::create_area() {

	//エリアの事前情報
	overall_value();

	//エリアの事前情報
	create_area_detail();

	//エリアの情報を表示
	custom_function::plot_area(this->Area_list_name);

	//詳細設定
	detail_area();
	return;
}

void area::calculation_of_costs() {
	this->Cost_matrix.resize(this->Number_of_areas, std::vector<long double>(this->Number_of_areas, std::numeric_limits<long double>::max() / 10));

	std::cout << "write_the_route_cost" << std::endl;

	//変数
	std::string Departure_Area;
	std::string Arrival_Area;
	long double Cost;
	int Last_flag;
	bool flag = true;

	std::cout << "Departure_area Arrival_area Cost(Numeric) 'When it is last,it is 1. otherwise it is 0.' " << std::endl;
	while (flag) {

		std::cin >> Departure_Area >> Arrival_Area >> Cost >> Last_flag;
		this->Cost_matrix[area_name[Departure_Area]][area_name[Arrival_Area]] = Cost;

		if (Last_flag == 1) {
			flag = false;
		}

	}

	this->Cost_matrix = custom_function::floyd_warshall_algorithm(this->Cost_matrix);

	plot_cost_func(this->Cost_matrix, this->reverse_area_name);

	return;

}

void area::plot_cost_func(std::vector<std::vector<long double>>& table, std::unordered_map< long int, std::string>& name_table) {
	std::cout << "コスト関数" << std::endl;

	std::cout << "  | ";
	for (long int data_loop_x = 0; data_loop_x < table.size(); data_loop_x++) {

		std::cout << name_table[data_loop_x] << " | ";
	}
	std::cout << std::endl;

	for (long int data_loop_y = 0; data_loop_y < table.size(); data_loop_y++) {
		std::cout << name_table[data_loop_y] << " | ";

		for (long int data_loop_x = 0; data_loop_x < table.size(); data_loop_x++) {
			if (data_loop_y == data_loop_x) {
				std::cout << 0 << " | ";
			}
			else {
				std::cout << table[data_loop_y][data_loop_x] << " | ";
			}
		}
		std::cout << std::endl;
	}

	return;

};

void area::detail_Plac_area() {
	//確率の設定
	probability_of_workplace_area.resize(this->Number_of_areas);//職場のエリアの確率
	probability_of_residence_area.resize(this->Number_of_areas);//住居のエリアの確率
	probability_of_shopping_area.resize(this->Number_of_areas);//買い物のエリアの確率
	probability_of_school_area_elementary.resize(this->Number_of_areas);//学校のエリアの確率
	probability_of_school_area_JHS.resize(this->Number_of_areas);//学校のエリアの確率
	probability_of_school_area_HS.resize(this->Number_of_areas);//学校のエリアの確率
	probability_of_school_area_university.resize(this->Number_of_areas);//学校のエリアの確率
	probability_of_hospital_area.resize(this->Number_of_areas);//病院のエリアの確率
	probability_of_sightseeing_area.resize(this->Number_of_areas);//観光のエリアの確率
	probability_of_other_area.resize(this->Number_of_areas);//観光のエリアの確率
	return;

}

void area::detail_area() {

	//初期化
	detail_Plac_area();

	std::vector<long int> workplace_area(this->Number_of_areas, 0);
	std::vector<long int> residence_area(this->Number_of_areas, 0);
	std::vector<long int> shopping_area(this->Number_of_areas, 0);
	std::vector<long int> school_area_e(this->Number_of_areas, 0);
	std::vector<long int> school_area_j(this->Number_of_areas, 0);
	std::vector<long int> school_area_h(this->Number_of_areas, 0);
	std::vector<long int> school_area_u(this->Number_of_areas, 0);
	std::vector<long int> hospital_area(this->Number_of_areas, 0);
	std::vector<long int> sightseeing_area(this->Number_of_areas, 0);
	std::vector<long int> other_area(this->Number_of_areas, 0);


	for (auto loop = 0; loop < probability_of_workplace_area.size(); loop++) {

		//エリアの名前
		std::cout << "Setting " << reverse_area_name[loop] << std::endl;

		std::cout << "wight of workplace (long int):";
		std::cin >> workplace_area[loop];

		std::cout << "wight of residence (long int):";
		std::cin >> residence_area[loop];

		std::cout << "wight of shopping (long int):";
		std::cin >> shopping_area[loop];

		std::cout << "wight of school elementary (long int):";
		std::cin >> school_area_e[loop];
		std::cout << "wight of school JHS(long int):";
		std::cin >> school_area_j[loop];
		std::cout << "wight of school HS(long int):";
		std::cin >> school_area_h[loop];
		std::cout << "wight of school university(long int):";
		std::cin >> school_area_u[loop];

		std::cout << "wight of hospital (long int):";
		std::cin >> hospital_area[loop];

		std::cout << "wight of sightseeing (long int):";
		std::cin >> sightseeing_area[loop];

		std::cout << "wight of other (long int):";
		std::cin >> other_area[loop];

	}

	//累積和
	long int workplace_area_sum = std::accumulate(workplace_area.begin(), workplace_area.end(), 0);
	long int residence_area_sum = std::accumulate(residence_area.begin(), residence_area.end(), 0);
	long int shopping_area_sum = std::accumulate(shopping_area.begin(), shopping_area.end(), 0);
	long int school_area_sum_e = std::accumulate(school_area_e.begin(), school_area_e.end(), 0);
	long int school_area_sum_j = std::accumulate(school_area_j.begin(), school_area_j.end(), 0);
	long int school_area_sum_h = std::accumulate(school_area_h.begin(), school_area_h.end(), 0);
	long int school_area_sum_u = std::accumulate(school_area_u.begin(), school_area_u.end(), 0);
	long int hospital_area_sum = std::accumulate(hospital_area.begin(), hospital_area.end(), 0);
	long int sightseeing_area_sum = std::accumulate(sightseeing_area.begin(), sightseeing_area.end(), 0);
	long int other_area_sum = std::accumulate(other_area.begin(), other_area.end(), 0);

	//確率の設定
	auto estimate_prob_func = [=](std::vector<long int>vec, long int num) -> std::vector<double> {
		std::vector<double>res(vec.size(), 0.0);
		for (auto loop = 0; loop < vec.size(); loop++) {
			res[loop] = ((double)vec[loop] / (double)num);
		}
		return res;
		};


	//答え
	this->probability_of_workplace_area = estimate_prob_func(workplace_area, workplace_area_sum);
	this->probability_of_residence_area = estimate_prob_func(residence_area, residence_area_sum);
	this->probability_of_shopping_area = estimate_prob_func(shopping_area, shopping_area_sum);
	this->probability_of_school_area_elementary = estimate_prob_func(school_area_e, school_area_sum_e);
	this->probability_of_school_area_JHS = estimate_prob_func(school_area_j, school_area_sum_j);
	this->probability_of_school_area_HS = estimate_prob_func(school_area_h, school_area_sum_h);
	this->probability_of_school_area_university = estimate_prob_func(school_area_u, school_area_sum_u);
	this->probability_of_hospital_area = estimate_prob_func(hospital_area, hospital_area_sum);
	this->probability_of_sightseeing_area = estimate_prob_func(sightseeing_area, sightseeing_area_sum);
	this->probability_of_other_area = estimate_prob_func(other_area, other_area_sum);


	return;

};