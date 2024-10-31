#pragma once
#include "setting_by_transportation.h"
#include "template.h"
#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<limits>
#include<algorithm>

setting_by_transportation::setting_by_transportation()
{

}

setting_by_transportation::~setting_by_transportation()
{


}

//Œö‹¤Œğ’Ê‚Ìİ’è
void setting_by_transportation::setting_function(std::unordered_map<std::string, long int>area_name)
{
	tram_cost.resize(area_name.size(), std::vector<long double>(area_name.size(), std::numeric_limits<long double>::max() / 10));

	std::cout << "Number of routes: ";
	std::cin >> Number_of_routes;//˜Hü”
	std::vector<std::vector<std::string>> Route_list;
	this->route_iter.resize(Number_of_routes * 2);//‰•œ‚ğİ’è

	for (auto num_route = 0; num_route < Number_of_routes; num_route++) {

		std::cout << num_route + 1 << " 's number of stop:";
		int number_of_stop;





		std::cin >> number_of_stop;//’â—¯Š”

		std::cout << num_route + 1 << " 's stop:";
		//’â—¯Š‚ÌƒŠƒXƒg‚Ìİ’è
		for (auto stop = 0; stop < number_of_stop; stop++) {
			std::string stop_name;
			std::cin >> stop_name;
			this->route_iter.at(num_route * 2).push_back(stop_name);
		}


		std::cout << "time Cost" << std::endl;
		long double time;
		std::cin >> time;

		for (long long int t_stop = 0; t_stop < (number_of_stop - 1); t_stop++) {

			tram_cost[area_name[route_iter[(num_route * 2)][t_stop]]][area_name[route_iter[(num_route * 2)][t_stop + 1]]] = std::min(time, tram_cost[area_name[route_iter[(num_route * 2)][t_stop]]][area_name[route_iter[(num_route * 2)][t_stop + 1]]]);

			tram_cost[area_name[route_iter[(num_route * 2)][t_stop + 1]]][area_name[route_iter[(num_route * 2)][t_stop]]] = std::min(time, tram_cost[area_name[route_iter[(num_route * 2)][t_stop + 1]]][area_name[route_iter[(num_route * 2)][t_stop]]]);


		}


		//‹t•ûŒü
		this->route_iter.at(num_route * 2 + 1) = this->route_iter.at(num_route * 2);

		// ”½“]
		std::reverse(this->route_iter.at(num_route * 2 + 1).begin(),
			this->route_iter.at(num_route * 2 + 1).end());
	}


	this->tram_cost = custom_function::floyd_warshall_algorithm(this->tram_cost);

	for (auto temp_row = 0; temp_row < this->tram_cost.size(); temp_row++) {
		for (auto temp_col = 0; temp_col < this->tram_cost[temp_row].size(); temp_col++) {
			if (this->tram_cost[temp_row][temp_col] == std::numeric_limits<long double>::max() / 10) {
				this->tram_cost[temp_row][temp_col] = 0;
			}
		}
	}

	plot_stop(this->route_iter);
	return;
}

void setting_by_transportation::plot_stop(std::vector<std::vector<std::string>>stop_list) {

	std::cout << "Route list" << std::endl;
	for (auto route = 0; route < stop_list.size(); route++) {
		std::cout << route << " : ";
		for (auto stop = 0; stop < stop_list.at(route).size(); stop++) {
			std::cout << stop_list.at(route).at(stop) << " ";
		}
		std::cout << std::endl;
	}
	return;
}