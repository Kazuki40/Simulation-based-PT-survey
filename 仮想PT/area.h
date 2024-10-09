#pragma once
#include<map>
#include<string>
#include<tuple>
#include<vector>
#include<unordered_map>

class area
{
public:
	area();
	~area();

	long int Loop_values;
	std::vector<std::vector<long double>> Cost_matrix;
	std::map<std::tuple<long int, long int>, std::string> Area_list;
	std::unordered_map<std::string, long int> area_name;
	std::unordered_map< long int, std::string> reverse_area_name;

private:

	std::vector<std::vector<std::string>> Area_list_name;
	long int X_distance_of_Area;
	long int Y_distance_of_Area;
	long int Number_of_areas;
	void create_area();
	void overall_value();
	void create_area_detail();
	void calculation_of_costs();
	void plot_cost_func(std::vector<std::vector<long double>>&, std::unordered_map< long int, std::string>&);

};

