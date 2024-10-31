#pragma once
#include "estimate_move.h"
#include<iostream>
#include<random>
#include<limits>
#include<string>
#include<vector>
#include <numeric>
#include"enums.h"

#define house_rate 15
#define work_school_rate 60
#define shop_rate 20
#define hospital_rate 5
#define other_rate 5
#define sightseeing_rate 5


extern std::mt19937_64 seed;

estimate_move::~estimate_move() {

};

estimate_move::estimate_move() {

};



void  estimate_move::external_input(area area, setting_by_transportation tram, householder& householder, long long int num, std::unordered_map< long int, std::string> num_string_area) {

	this->this_area = area;
	this->this_tram = tram;
	this->this_householder = &householder;

	if (this_householder->personal_list[0].Age == 87) {
		std::cout << "test";
	}

	this->stay_area_num = num;
	this->string_map = num_string_area;
	trip_num.resize(this->this_householder->personal_list.size(), -1);
	setting();
	setting_work_place();
	trip_setting();
};

//移動の推定
void estimate_move::setting() {


	//トリップ数
	std::poisson_distribution<int> dist(1.5);

	for (auto trip_num_loop = 0; trip_num_loop < this->this_householder->personal_list.size(); trip_num_loop++) {
		trip_num[trip_num_loop] = dist(seed);

		if (trip_num[trip_num_loop] == 1) {

			//再度抽選
			do {
				trip_num[trip_num_loop] = dist(seed);
			} while (trip_num[trip_num_loop] == 1);

		}

		if (trip_num[trip_num_loop] == 0) {

			//何かしら職・学生の人は何かしらの行動をする
			if (this->this_householder->personal_list[trip_num_loop].Work_status != unemployment) {

				//再度抽選
				do {
					trip_num[trip_num_loop] = dist(seed);
				} while (trip_num[trip_num_loop] < 2);
			}

		}

		if (this->this_householder->personal_list[trip_num_loop].Work_status == preschoolers) {
			this->this_householder->personal_list[trip_num_loop] = this->this_householder->personal_list[0];
		}

	}


	people_facility.resize(this->this_householder->personal_list.size(), std::vector<users_stay>());
	people_trip.resize(this->this_householder->personal_list.size(), std::vector<users_trip>());

	//トリップの施設設定
	for (auto trip_num_loop = 0; trip_num_loop < this->this_householder->personal_list.size(); trip_num_loop++) {

		bool work_tf;
		if (this->this_householder->personal_list[trip_num_loop].Work_status == worker) {
			work_tf = true;
		}
		else {
			work_tf = false;
		}

		//トリップの施設設定
		people_facility[trip_num_loop] = estimate_move_func(trip_num[trip_num_loop], home, work_tf);

		if (this->this_householder->personal_list[trip_num_loop].Work_status == unemployment) {
			for (auto num_unem = 0; num_unem < people_facility[trip_num_loop].size(); num_unem++) {
				if ((people_facility[trip_num_loop][num_unem].facility == work) || (people_facility[trip_num_loop][num_unem].facility == school)) {
					people_facility[trip_num_loop][num_unem].facility = other;
				}
			}

		}
		// 要素0に既定の値を入れる
		users_stay default_value;
		default_value.facility = home;
		default_value.zone_area = this->stay_area_num;
		default_value.zone_name = this->string_map[this->stay_area_num];

		// 配列の先頭に挿入
		people_facility[trip_num_loop].insert(people_facility[trip_num_loop].begin(), default_value);


		//値
		if (this->this_householder->personal_list[trip_num_loop].Work_status != unemployment) {

			bool temp_btf = false;
			//職・学生の人は学校と職場に行く
			for (auto e : people_facility[trip_num_loop]) {
				if ((e.facility == work) || (e.facility == school)) {
					temp_btf = true;
				}
			}

			if (temp_btf == false) {
				//再度抽選
				std::uniform_int_distribution<>t_dist(1, people_facility[trip_num_loop].size() - 1);
				if (this->this_householder->personal_list[trip_num_loop].Work_status == 5) {
					people_facility[trip_num_loop][t_dist(seed)].facility = work;
				}
				else {
					people_facility[trip_num_loop][t_dist(seed)].facility = school;
				}
			}

		}

		// people_tripの初期化
		for (auto trip_num_loop = 0; trip_num_loop < people_facility.size(); ++trip_num_loop) {
			if (!people_facility[trip_num_loop].empty()) {
				auto newSize = people_facility[trip_num_loop].size() - 1;
				people_trip[trip_num_loop].resize(newSize); // 個人ごとに異なるサイズにリサイズ
			}
		}

	}

	//値の
	for (auto loop = 0; loop < people_facility.size(); loop++) {
		for (auto loop_2 = 0; loop_2 < people_facility[loop].size(); loop_2++) {
			//世帯
			if ((people_facility[loop][loop_2].facility == home) || (people_facility[loop][loop_2].facility == work) || (people_facility[loop][loop_2].facility == school)) {



				long int temp_num_d = 0;

				auto func_pe = [](std::vector<double>prob)->long long int {

					std::uniform_real_distribution<>rand_num(0.0, 1.0);

					double rand_num_seed = rand_num(seed);
					double temp = 0.0;
					long long int temp_do = -1;
					do {
						temp_do++;
						temp += prob[temp_do];

					} while (rand_num_seed < temp);
					return temp_do;
					};

				if (people_facility[loop][loop_2].facility == shop) {

					people_facility[loop][loop_2].zone_area = func_pe(this->this_area.probability_of_shopping_area);
					people_facility[loop][loop_2].zone_name = this->this_area.reverse_area_name[people_facility[loop][loop_2].zone_area];

				}
				else if (people_facility[loop][loop_2].facility == hospital) {

					people_facility[loop][loop_2].zone_area = func_pe(this->this_area.probability_of_hospital_area);
					people_facility[loop][loop_2].zone_name = this->this_area.reverse_area_name[people_facility[loop][loop_2].zone_area];

				}
				else if (people_facility[loop][loop_2].facility == other) {

					people_facility[loop][loop_2].zone_area = func_pe(this->this_area.probability_of_other_area);
					people_facility[loop][loop_2].zone_name = this->this_area.reverse_area_name[people_facility[loop][loop_2].zone_area];

				}
				else if (people_facility[loop][loop_2].facility == sightseeing) {

					people_facility[loop][loop_2].zone_area = func_pe(this->this_area.probability_of_sightseeing_area);
					people_facility[loop][loop_2].zone_name = this->this_area.reverse_area_name[people_facility[loop][loop_2].zone_area];

				}

			}

		}
	}



	return;
}

//目的の関数
facility_type estimate_move::estimate_func(facility_type pre_est, bool home_tf, bool work_tf) {
	std::uniform_int_distribution<long long int> dist(0, std::numeric_limits<long long int>::max());
	facility_type ans;


	bool temp_tf = false;



	do {
		int temp_num = dist(seed) % 100;
		if (temp_num < house_rate) {
			ans = home;
		}
		else if (temp_num < (work_school_rate + house_rate)) {
			if (home_tf == true) {
				ans = work;
			}
			else {
				ans = school;
			}
		}
		else if (temp_num < (shop_rate + work_school_rate + house_rate)) {
			ans = shop;
		}
		else if (temp_num < (hospital_rate + shop_rate + work_school_rate + house_rate)) {
			ans = hospital;
		}
		else if (temp_num < (other_rate + hospital_rate + shop_rate + work_school_rate + house_rate)) {
			ans = other;
		}
		else if (temp_num <= (sightseeing_rate + other_rate + hospital_rate + shop_rate + work_school_rate + house_rate)) {
			ans = sightseeing;
		}
		else {
			fprintf(stderr, "rand_error");
		}

		if (pre_est == ans) {
			if ((ans == home) || (ans == work) || (ans == school)) {
				temp_tf = false;
			}
			else {
				temp_tf = true;
			}
		}
		else {
			temp_tf = true;
		}


	} while (temp_tf != true);

	return ans;

};



//移動について
std::vector<users_stay> estimate_move::estimate_move_func(long long int time, facility_type facility, bool work_tf) {
	std::vector<users_stay> ans;
	users_stay user_info;


	//計算終了
	if (time <= 0) {
		return ans;
	}
	else if (time == 1) {
		//最後の施設
		//自宅
		user_info.facility = home;

		user_info.zone_area = this->stay_area_num;
		user_info.zone_name = string_map[this->stay_area_num];

	}
	else if ((time == 2) || (facility == home)) {
		user_info.facility = estimate_func(facility, true, work_tf);

		user_info.zone_area = -1;
		user_info.zone_name = "aaa ";
	}
	else {
		user_info.facility = estimate_func(facility, false, work_tf);

		user_info.zone_area = -1;
		user_info.zone_name = "aaa";
	}


	ans.push_back(user_info);


	// 再帰呼び出し
	auto recursive_ans = estimate_move_func(time - 1, user_info.facility, work_tf);
	ans.insert(ans.end(), recursive_ans.begin(), recursive_ans.end());

	return ans;
}



void estimate_move::setting_work_place() {
	std::uniform_real_distribution<double> dist_e(0.0, 1.0);



	auto work_school_place = [&](std::vector<double>prob)->long long int {
		long long int ans = -1;
		double judge = dist_e(seed);



		//内内
		std::vector<double> temp = prob;
		temp[this->stay_area_num] *= 2.0;
		double temp_num_all = std::accumulate(temp.begin(), temp.end(), 0.0);

		judge = dist_e(seed);
		double temp_v = 0.00;
		long long int temp_num = -1;
		do {
			temp_num++;
			temp_v += temp[temp_num] / temp_num_all;

		} while (judge > temp_v);

		ans = temp_num;


		return ans;
		};


	for (auto temp_loop = 0; temp_loop < this->this_householder->personal_list.size(); temp_loop++) {
		//if (this->this_householder->personal_list[temp_loop].Work_status == 6) {
			  //	//無職の働く場所の定義はない
			  //}



		if (this->this_householder->personal_list[temp_loop].Work_status == worker) {

			//職場の場所の設定
			this->this_householder->personal_list[temp_loop].Work_place = work_school_place(this->this_area.probability_of_workplace_area);
		}
		else if (this->this_householder->personal_list[temp_loop].Work_status == student) {

			//職場の場所の設定
			this->this_householder->personal_list[temp_loop].Work_place = work_school_place(this->this_area.probability_of_school_area_university);

		}
		else if (this->this_householder->personal_list[temp_loop].Work_status == high_school) {

			//職場の場所の設定
			this->this_householder->personal_list[temp_loop].Work_place = work_school_place(this->this_area.probability_of_school_area_HS);

		}
		else if (this->this_householder->personal_list[temp_loop].Work_status == junior_high_school) {

			//職場の場所の設定
			this->this_householder->personal_list[temp_loop].Work_place = work_school_place(this->this_area.probability_of_school_area_JHS);

		}
		else if (this->this_householder->personal_list[temp_loop].Work_status == primary_school) {

			//職場の場所の設定
			this->this_householder->personal_list[temp_loop].Work_place = work_school_place(this->this_area.probability_of_school_area_elementary);

		}
		else if (this->this_householder->personal_list[temp_loop].Work_status == preschoolers) {

			//職場の場所の設定
			this->this_householder->personal_list[temp_loop].Work_place = this->this_householder->personal_list[0].Work_place;

		}
		else {
			fprintf(stderr, "error");
		}



	}
	return;
}

//トリップとトリップの間の設定
void estimate_move::trip_setting() {
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	int num_householder = this->this_householder->personal_list.size();//値

	std::vector<short> householder_w_s(num_householder, 0);
	long long int temp_num;
	//通勤，学校の設定
	for (temp_num = 0; temp_num < num_householder; temp_num++) {

		//個数
		long long int w_time = 0;
		long long int w_all_time = 0;
		long long int temp_trip;
		for (temp_trip = 0; temp_trip < this->people_facility[temp_num].size(); temp_trip++) {

			if ((this->people_facility[temp_num][temp_trip].facility == work) || (this->people_facility[temp_num][temp_trip].facility == school)) {
				w_all_time++;
			}
		}

		householder_w_s[temp_num] = w_all_time;
		long long int temp_ws_area = 0;

		//既定の行動設定
		for (temp_trip = 0; temp_trip < this->people_facility[temp_num].size() - 1; temp_trip++) {

			if ((this->people_facility[temp_num][temp_trip].facility == work) || (this->people_facility[temp_num][temp_trip].facility == school)) {
				w_time++;

				if (w_time == 1) {
					if (this->people_facility[temp_num][temp_trip].facility == work) {
						std::uniform_int_distribution<long long int>dist1(6.5 * 60, 9 * 60);
						this->people_trip[temp_num][temp_trip - 1].departure_time = dist1(seed);

					}
					else {
						std::uniform_int_distribution<long long int>dist2(7 * 60, 8.5 * 60);
						this->people_trip[temp_num][temp_trip - 1].departure_time = dist2(seed);
					}
					temp_ws_area = this->this_householder->personal_list[temp_num].Work_place;
				}
				else if ((w_time == 2) && (w_all_time > 2)) {
					std::uniform_int_distribution<long long int>dist3(11 * 60, 13 * 60);
					this->people_trip[temp_num][temp_trip - 1].departure_time = dist3(seed);
					this->this_householder->personal_list[temp_num].Work_place = temp_ws_area;
				}
				else {
					std::uniform_int_distribution<long long int>dist4(15 * 60, 22 * 60);
					this->people_trip[temp_num][temp_trip - 1].departure_time = dist4(seed);
					this->this_householder->personal_list[temp_num].Work_place = temp_ws_area;
				}


			}
		}
	}

	//行動の設定
	//ゾーンの設定
	auto place_func = [&](std::vector<double>prob)->long long int {
		double temp_prov_use = dist(seed);

		double temp_v = 0.00;
		long long int temp_num = -1;
		do {
			temp_num++;
			temp_v += prob[temp_num];

		} while (temp_prov_use >= temp_v);

		return temp_num;
		};

	long long int temp_fac;
	for (temp_num = 0; temp_num < num_householder; temp_num++) {
		for (temp_fac = 0; temp_fac < this->people_facility[temp_num].size(); temp_fac++) {

			double temp_prov = dist(seed);


			//値
			if (this->people_facility[temp_num][temp_fac].facility == shop) {
				this->people_facility[temp_num][temp_fac].zone_area = place_func(this->this_area.probability_of_shopping_area);
			}
			else if (this->people_facility[temp_num][temp_fac].facility == hospital) {
				this->people_facility[temp_num][temp_fac].zone_area = place_func(this->this_area.probability_of_hospital_area);
			}
			else if (this->people_facility[temp_num][temp_fac].facility == other) {
				this->people_facility[temp_num][temp_fac].zone_area = place_func(this->this_area.probability_of_other_area);

			}
			else if (this->people_facility[temp_num][temp_fac].facility == sightseeing) {
				this->people_facility[temp_num][temp_fac].zone_area = place_func(this->this_area.probability_of_sightseeing_area);

			}
			else if (this->people_facility[temp_num][temp_fac].facility == home) {
				this->people_facility[temp_num][temp_fac].zone_area = this->stay_area_num;
			}
			else {
				this->people_facility[temp_num][temp_fac].zone_area = this->this_householder->personal_list[temp_num].Work_place;
			}

		}

	}

	//車の利用
	std::vector <int> use_car(num_householder, 0);
	long int num = this->this_householder->Number_of_vehicle;

	for (temp_num = 0; temp_num < num_householder; temp_num++) {
		if (this->this_householder->personal_list[temp_num].Hold_driving_license == true) {
			use_car[temp_num] = 1;
			num--;

			if (num == 0) {
				break;
			}

		}
	}

	//代表交通手段の設定
	for (temp_num = 0; temp_num < num_householder; temp_num++) {
		//home to home 
		long long int temp_loop = 0;
		long long int temp_loop_min = -1;
		long long int temp_loop_max = -1;
		bool work_bf = false;
		for (temp_fac = 0; temp_fac < (this->people_facility[temp_num].size()); temp_fac++) {
			//代表交通手段の設定
			if (this->people_facility[temp_num][temp_fac].facility == home) {
				temp_loop++;
				if (temp_loop == 1) {
					temp_loop_min = temp_fac;
				}
				else {
					temp_loop_max = temp_loop;

					//通勤行動あり
					std::uniform_real_distribution<double> main_tram_rand(0.0, 1.0);
					double temp_main_tram_prob = main_tram_rand(seed);

					for (auto t_nums = temp_loop_min; t_nums < temp_loop_max - 1; t_nums++) {
						if (work_bf == true) {
							if (this->this_householder->personal_list[temp_num].To_work_by_transportation == true) {
								this->people_trip[temp_num][t_nums].main_mode = mode_tram;
							}
							else {
								if (use_car[temp_num] == 1) {

									this->people_trip[temp_num][t_nums].main_mode = mode_car;
								}
								else {
									if (temp_main_tram_prob < .70) {
										this->people_trip[temp_num][t_nums].main_mode = mode_bicycle;
									}
									else {
										this->people_trip[temp_num][t_nums].main_mode = mode_walk;
									}

								}
							}
						}
						else {
							//自宅-職場-自宅以外
							//車を利用可能か
							if (use_car[temp_num] == 1) {
								if (temp_main_tram_prob < 0.25) {
									this->people_trip[temp_num][t_nums].main_mode = mode_car;
								}
								else if (temp_main_tram_prob < 0.5) {
									this->people_trip[temp_num][t_nums].main_mode = mode_tram;
								}
								else if (temp_main_tram_prob < 0.75) {
									this->people_trip[temp_num][t_nums].main_mode = mode_walk;
								}
								else {
									this->people_trip[temp_num][t_nums].main_mode = mode_bicycle;
								}
							}
							else {

								if (temp_main_tram_prob < 0.5) {
									this->people_trip[temp_num][t_nums].main_mode = mode_tram;
								}
								else if (temp_main_tram_prob < 0.75) {
									this->people_trip[temp_num][t_nums].main_mode = mode_walk;
								}
								else {
									this->people_trip[temp_num][t_nums].main_mode = mode_bicycle;
								}
							}
						}


					}

					temp_loop_min = temp_loop_max;
					work_bf = false;
				}
			}
			else if (this->people_facility[temp_num][temp_fac].facility == work) {
				work_bf = true;
			}
		}
	}

	//各アンリンクトトリップの設定

	for (temp_num = 0; temp_num < num_householder; temp_num++) {
		long int time_num = 9 * 60;
		for (temp_fac = 0; temp_fac < (this->people_facility[temp_num].size() - 1); temp_fac++) {
			std::uniform_int_distribution<>dist_time(time_num, 24 * 60);//出発時間
			//車
			if (this->people_trip[temp_num][temp_fac].main_mode == mode_car) {
				people_trip[temp_num][temp_fac].time.push_back(this->this_area.Cost_matrix[people_facility[temp_num][temp_fac].zone_area][people_facility[temp_num][temp_fac + 1].zone_area]);
				people_trip[temp_num][temp_fac].mode.push_back(mode_car);
			}
			else if (this->people_trip[temp_num][temp_fac].main_mode == mode_tram) {

				if (this->this_tram.tram_cost[people_facility[temp_num][temp_fac].zone_area][people_facility[temp_num][temp_fac + 1].zone_area] != 0) {
					people_trip[temp_num][temp_fac].time.push_back(this->this_area.Cost_matrix[people_facility[temp_num][temp_fac].zone_area][people_facility[temp_num][temp_fac].zone_area]);
					people_trip[temp_num][temp_fac].mode.push_back(mode_walk);

					people_trip[temp_num][temp_fac].time.push_back(this->this_tram.tram_cost[people_facility[temp_num][temp_fac].zone_area][people_facility[temp_num][temp_fac + 1].zone_area]);
					people_trip[temp_num][temp_fac].mode.push_back(mode_tram);

					people_trip[temp_num][temp_fac].time.push_back(this->this_area.Cost_matrix[people_facility[temp_num][temp_fac + 1].zone_area][people_facility[temp_num][temp_fac + 1].zone_area]);
					people_trip[temp_num][temp_fac].mode.push_back(mode_walk);
				}
				else {

					//公共交通がないので歩く
					double temp_double_ans = 9999999999;
					int stop_cell_i = 999999;
					long long int num_tram, num_stop;
					for (num_tram = 0; num_tram < this->this_tram.route_iter.size(); num_tram++) {
						for (num_stop = 0; num_stop<this->this_tram.route_iter[num_tram].size(); num_stop++) {

							double temp_double = this->this_area.Cost_matrix[people_facility[temp_num][temp_fac].zone_area][this->this_area.area_name[this->this_tram.route_iter[num_tram][num_stop]]];
							//移動について
							if (temp_double_ans > temp_double) {
								temp_double_ans = temp_double;
								stop_cell_i = this->this_area.area_name[this->this_tram.route_iter[num_tram][num_stop]];
							}
						}
					}

					temp_double_ans = 9999999999;
					int stop_cell_j = 999999;
					for (num_tram = 0; num_tram < this->this_tram.route_iter.size(); num_tram++) {
						for (num_stop = 0; num_stop < this->this_tram.route_iter[num_tram].size(); num_stop++) {

							double temp_double_2 = this->this_area.Cost_matrix[this->this_area.area_name[this->this_tram.route_iter[num_tram][num_stop]]][people_facility[temp_num][temp_fac + 1].zone_area];
							//移動について
							if (temp_double_ans > temp_double_2) {
								temp_double_ans = temp_double_2;
								stop_cell_j = this->this_area.area_name[this->this_tram.route_iter[num_tram][num_stop]];
							}
						}
					}

					people_trip[temp_num][temp_fac].time.push_back(this->this_area.Cost_matrix[people_facility[temp_num][temp_fac].zone_area][stop_cell_i]);
					people_trip[temp_num][temp_fac].mode.push_back(mode_walk);

					people_trip[temp_num][temp_fac].time.push_back(this->this_tram.tram_cost[stop_cell_i][stop_cell_j]);
					people_trip[temp_num][temp_fac].mode.push_back(mode_tram);

					people_trip[temp_num][temp_fac].time.push_back(this->this_area.Cost_matrix[stop_cell_j][people_facility[temp_num][temp_fac + 1].zone_area]);
					people_trip[temp_num][temp_fac].mode.push_back(mode_walk);
				}


			}
			else if ((this->people_trip[temp_num][temp_fac].main_mode == mode_walk)) {

				people_trip[temp_num][temp_fac].time.push_back(5 * this->this_area.Cost_matrix[people_facility[temp_num][temp_fac].zone_area][people_facility[temp_num][temp_fac + 1].zone_area]);
				people_trip[temp_num][temp_fac].mode.push_back(mode_walk);
			}
			else if ((this->people_trip[temp_num][temp_fac].main_mode == mode_bicycle)) {
				people_trip[temp_num][temp_fac].time.push_back(4 * this->this_area.Cost_matrix[people_facility[temp_num][temp_fac].zone_area][people_facility[temp_num][temp_fac + 1].zone_area]);
				people_trip[temp_num][temp_fac].mode.push_back(mode_bicycle);
			}

		}
	}

	return;
}