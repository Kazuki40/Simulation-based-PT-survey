#pragma once
#include "Generate_parson.h"
#include<iostream>
#include"householder.h"

Generate_parson::Generate_parson() {
	std::cout << "generate_parson" << std::endl;
}


Generate_parson::~Generate_parson() {
	std::cout << "delete_generate_parson" << std::endl;
}

//人口分布等
//名前，人数
void Generate_parson::generate_user_func(std::string area_name, long int num) {

	this->generate_list.resize(num);
	return;
}