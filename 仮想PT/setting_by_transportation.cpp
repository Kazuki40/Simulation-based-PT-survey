#include "setting_by_transportation.h"
#include<iostream>
#include<vector>
#include<string>

setting_by_transportation::setting_by_transportation()
{
	setting_function();
}

setting_by_transportation::~setting_by_transportation()
{
}

void setting_by_transportation::setting_function()
{
	std::cout << "Number of routes: ";
	std::cin >> Number_of_routes;
	std::vector<std::vector<std::string>> Route_list;
	this->route_iter.resize(Number_of_routes * 2);

	for (auto num_route = 0; num_route < Number_of_routes; num_route++) {

		std::cout << num_route << " 's number of stop:";
		int number_of_stop;
		std::cin >> number_of_stop;

		std::cout << num_route << " 's stop:";



		for (auto stop = 0; stop < number_of_stop; stop++) {
			std::string stop_name;
			std::cin >> stop_name;
			this->route_iter.at(num_route * 2).push_back(stop_name);
		}

		//‹t•ûŒü
		this->route_iter.at(num_route * 2 + 1) = this->route_iter.at(num_route * 2);

		// ”½“]
		std::reverse(this->route_iter.at(num_route * 2 + 1).begin(),
			this->route_iter.at(num_route * 2 + 1).end());
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