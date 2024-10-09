#include "area.h"
#include "template.h"
#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>
#include <limits>

area::area() {
	this->Number_of_areas = 0;
	this->X_distance_of_Area = 0;
	this->Y_distance_of_Area = 0;
	create_area();
	calculation_of_costs();
}

area::~area() {
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

}