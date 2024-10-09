#pragma once
#include<iostream>
#include<vector>

class setting_by_transportation
{
public:
	setting_by_transportation();
	~setting_by_transportation();

	std::vector<std::vector<std::string>> route_iter;

private:
	void setting_function();
	int Number_of_routes;
	void plot_stop(std::vector<std::vector<std::string>>);
};

