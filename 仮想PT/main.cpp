//PT調査をシミュレーションによって生成
#pragma once
#include<iostream>
#include<ostream>
#include<istream>
#include<fstream>
#include<sstream>
#include<string>
#include<random>
#include<vector>
#include<cmath>
#include<limits>
#include<numeric> 

#include"template.h"
#include"householder.h"
#include"personal.h"
#include"visitors.h"
#include"area.h"
#include"setting_by_transportation.h"
#include"Generate_parson.h"
#include"estimate_move.h"
#include"enums.h"

constexpr double rsda = 0.2;
constexpr double rsd_k = 1.96;


#define num_of_householder 1000

// 家　通勤　通学　観光　病院　買い物　他
#define trip_aime_num 7
// 車 自転車　徒歩　電車
#define trip_mode_num count_mode

//
#define trip_num 2.3

std::mt19937_64 seed(42);

void write_func(auto residents) {
	std::ofstream write_csv("out.csv", std::ios::out);

	for (auto temp_i = 0; temp_i < residents.size(); temp_i++) {
		for (auto temp_j = 0; temp_j < residents[temp_i].generate_list.size(); temp_j++) {
			for (auto temp_k = 0; temp_k < residents[temp_i].generate_list[temp_j].personal_list.size(); temp_k++) {

				write_csv << temp_i << "," << temp_j << "," << temp_k << ",";
				write_csv << residents[temp_i].generate_list[temp_j].Number_of_household_members << ",";
				write_csv << residents[temp_i].generate_list[temp_j].Number_of_vehicle << ",";
				write_csv << residents[temp_i].generate_list[temp_j].Number_of_cycle << ",";

				write_csv << residents[temp_i].generate_list[temp_j].personal_list[temp_k].Sex << ",";
				write_csv << residents[temp_i].generate_list[temp_j].personal_list[temp_k].Age << ",";
				write_csv << residents[temp_i].generate_list[temp_j].personal_list[temp_k].Work_status << ",";
				write_csv << residents[temp_i].generate_list[temp_j].personal_list[temp_k].Work_place << ",";
				write_csv << residents[temp_i].generate_list[temp_j].personal_list[temp_k].Hold_driving_license << ",";
				write_csv << residents[temp_i].generate_list[temp_j].personal_list[temp_k].To_work_by_transportation << ",";
				write_csv << residents[temp_i].generate_list[temp_j].personal_list[temp_k].Probability_of_transportation_weekdays << ",";
				write_csv << residents[temp_i].generate_list[temp_j].personal_list[temp_k].Probability_of_transportation_weekends << ",";
				write_csv << residents[temp_i].generate_list[temp_j].personal_list[temp_k].hold_IC << ",";

				write_csv << std::endl;

			}
		}
	}
}

// Function to write users_stay and users_trip to CSV
void write_users_to_csv(const std::vector<users_stay>& stays, const std::vector<users_trip>& trips) {
    std::ofstream write_csv("users_data.csv", std::ios::out);

    // Write headers
    write_csv << "Zone Area,Zone Name,Facility Type,Departure Time,Arrival Time,Move Times,Transport Modes,Main Mode" << std::endl;

    // Write user stays and trips
    for (const auto& stay : stays) {
        // Find corresponding trips (if needed)
        for (const auto& trip : trips) {
            write_csv << stay.zone_area << ","
                       << stay.zone_name << ","
                       << stay.facility << ","
                       << trip.departure_time << ","
                       << trip.arrival_time << ",";

            // Write move times
            for (const auto& time : trip.time) {
                write_csv << time << " ";
            }
            write_csv << ",";

            // Write transport modes
            for (const auto& mode : trip.mode) {
                write_csv << mode << " ";
            }
            write_csv << ",";

            // Main mode
            write_csv << trip.main_mode << std::endl;
        }
    }

    write_csv.close();
}


//サンプル比率の計算
double sampling_rate_func(double N, long int ZK) {
	double ans;

	ans = (double)1 / ((double)(N / (ZK - 1)) * std::powl((rsda / rsd_k), 2.0) + 1);

	return ans;
}


int main() {

	//エリアの設定
	area make;
	make.set_start();

	//公共交通の設定
	setting_by_transportation transportation;
	transportation.setting_function(make.area_name);

	//人物の設定
	std::vector<Generate_parson>residents(make.reverse_area_name.size());

	//PT調査の設定
	std::vector<long int>pt_extract(make.reverse_area_name.size(), 0);



	for (int generate_data = 0; generate_data < make.reverse_area_name.size(); generate_data++) {
		long long int num_people = std::roundl(make.probability_of_residence_area[generate_data] * num_of_householder);


		//人数が0の場合
		if (num_people == 0) {
			num_people++;
		}
		residents.at(generate_data).generate_user_func(make.reverse_area_name[generate_data], num_people);

	}


	//5歳以上の人口を取得
	long long int num_people = 0;
	for (auto temp_i = 0; temp_i < residents.size(); temp_i++) {
		for (auto temp_j = 0; temp_j < residents[temp_i].generate_list.size(); temp_j++) {
			for (auto temp_k = 0; temp_k < residents[temp_i].generate_list[temp_j].personal_list.size(); temp_k++) {


				//値の設定
				if (residents[temp_i].generate_list[temp_j].personal_list[temp_k].Age >= 5) {
					num_people++;
				}

			}
		}
	}



		//エリア内
	std::cout << "Settings within the target area" << std::endl;
	std::cout << "Settings within the target area num" << std::endl;
	long long int area_num;
	std::cin >> area_num;


long double num_people_n = (long double)num_people * trip_num;
	long long int num_aim = trip_aime_num;
	long long int num_mode = trip_mode_num;
	long long int num = area_num * num_aim * num_mode;


	//PT調査抽出率
	long double temp_sampling_rate = sampling_rate_func(num_people_n, num);

	////平均世帯人数
	//long double average_household_size = (long double)num_people / num_of_householder;

	//PTの世帯判定
	//PT調査対象の世帯判定




	std::vector<std::string>area_name(area_num);
	for (auto area_num_temp = 0; area_num_temp < area_num; area_num_temp++) {
		std::cin >> area_name[area_num_temp];
	}

	std::vector<std::vector<int>>pt_household(make.area_name.size(), std::vector<int>());
	std::uniform_real_distribution<>rand(0, 0.10);
	for (auto temp : area_name) {

		long long int temp_i = make.area_name[temp];


		pt_household[temp_i].resize(residents[temp_i].generate_list.size(), 0);

		long long int temp_house = residents[temp_i].generate_list.size();

		std::uniform_int_distribution<>pt_rand(0, temp_house - 1);

		long double temp_db_num = temp_sampling_rate + rand(seed);

		temp_db_num = (temp_db_num >= 1.0) ? 1.0 : temp_db_num;

		//対象のセルでの世帯数
		long long int target_num = std::ceill(temp_db_num * temp_house);
		long long int temp_area_pt = 0;

		//PTの抽出方法
		do {
			temp_area_pt = 0;
			pt_household[temp_i][pt_rand(seed)] = 1;

			temp_area_pt = std::accumulate(pt_household[temp_i].begin(), pt_household[temp_i].end(), 0);
		} while (target_num > temp_area_pt);
	}

	std::vector<estimate_move> simulation(num_people);

	std::ofstream write_csv_pt("target_PT.csv", std::ios::out);
	for (auto pt_temp_i = 0; pt_temp_i < pt_household.size(); pt_temp_i++) {
		for (auto pt_temp_j = 0; pt_temp_j < pt_household[pt_temp_i].size(); pt_temp_j++) {
			write_csv_pt << pt_temp_i << "," << pt_temp_j << "," << pt_household[pt_temp_i][pt_temp_j] << std::endl;
		}
	}


	long long int temp_num = 0;
	//シミュレーションの実行
	for (auto temp_i = 0; temp_i < residents.size(); temp_i++) {
		for (auto temp_j = 0; temp_j < residents[temp_i].generate_list.size(); temp_j++) {

			simulation[temp_num].external_input(make, transportation, residents[temp_i].generate_list[temp_j], temp_i, make.reverse_area_name);

			temp_num++;
		}
		std::vector<estimate_move> simulation(num_people);
	}


	write_func(residents);

	std::ofstream write_csv2("out2.csv");
	for (auto temp_a = 0; temp_a<simulation.size(); temp_a++) {
		for (auto temp_b = 0; temp_b < simulation[temp_a].people_facility.size(); temp_b++) {
			for (auto temp_c = 0; temp_c < simulation[temp_a].people_facility[temp_b].size(); temp_c++) {
				write_csv2 << temp_a << "," << temp_b << "," << temp_c << ",";
				write_csv2 << simulation[temp_a].people_facility[temp_b][temp_c].facility << ",";
				write_csv2 << simulation[temp_a].people_facility[temp_b][temp_c].zone_area << ",";
				write_csv2 << simulation[temp_a].people_facility[temp_b][temp_c].zone_name << std::endl;;
			}
		}
	}


	std::ofstream write_csv3("out2.csv");
	for (auto temp_a = 0; temp_a < simulation.size(); temp_a++) {
		for (auto temp_b = 0; temp_b < simulation[temp_a].people_trip.size(); temp_b++) {
			for (auto temp_c = 0; temp_c < simulation[temp_a].people_trip[temp_b].size(); temp_c++) {
				write_csv3 << temp_a << "," << temp_b << "," << temp_c << ",";
				write_csv3 << simulation[temp_a].people_trip[temp_b][temp_c].arrival_time << ",";
				write_csv3 << simulation[temp_a].people_trip[temp_b][temp_c].departure_time << ",";
				write_csv3 << simulation[temp_a].people_trip[temp_b][temp_c].main_mode << ",";

				for (auto temp_d = 0; temp_d < simulation[temp_a].people_trip[temp_b][temp_c].mode.size(); temp_d++) {
					write_csv3 << simulation[temp_a].people_trip[temp_b][temp_c].mode[temp_d] << ",";
				}

				for (auto temp_e = 0; temp_e < simulation[temp_a].people_trip[temp_b][temp_c].time.size(); temp_e++) {
					write_csv3 << simulation[temp_a].people_trip[temp_b][temp_c].time[temp_e] << ",";
				}
				write_csv3 << std::endl;
			}
		}
	}



	return 0;

}