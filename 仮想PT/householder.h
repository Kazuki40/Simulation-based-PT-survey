#pragma once
#include<vector>
#include"personal.h"

class householder
{
private:
	int Number_of_household_members;
	int Number_of_vehicle;
	int Number_of_cycle;
public:

	int getter_number_of_household_members();
	int getter_number_of_vehicle();

	householder();
	~householder();

	std::vector<personal> personal_list;


};

