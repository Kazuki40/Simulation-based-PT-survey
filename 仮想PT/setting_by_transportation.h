#pragma once
#include<iostream>
#include<vector>
#include<unordered_map>

class setting_by_transportation
{
public:
	setting_by_transportation();
	~setting_by_transportation();
	void setting_function(std::unordered_map<std::string, long int>);
	std::vector<std::vector<std::string>> route_iter;
	std::vector<std::vector<long double>> tram_cost;
private:

	int Number_of_routes;
	void plot_stop(std::vector<std::vector<std::string>>);
};

