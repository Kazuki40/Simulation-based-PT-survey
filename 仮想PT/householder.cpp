#include "householder.h"
#include<random>
#include<iostream>

extern std::mt19937_64 seed;

householder::householder()
{
	//l”
	std::poisson_distribution<int> num_of_members(1.0);
	Number_of_household_members = num_of_members(seed);
	personal_list.resize(Number_of_household_members);
	std::cout << Number_of_household_members << std::endl;
}

householder::~householder()
{
}