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

//�l�����z��
//���O�C�l��
void Generate_parson::generate_user_func(std::string area_name, long int num) {

	this->generate_list.resize(num);
	return;
}