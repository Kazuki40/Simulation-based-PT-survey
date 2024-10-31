#pragma once
#include<string>
#include<vector>
#include<algorithm>
#include<random>
#include"householder.h"


class Generate_parson
{

public:
	std::vector<householder>generate_list;
	Generate_parson();
	~Generate_parson();
	void generate_user_func(std::string, long int);
};

