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
	void set_start();//�����ݒ�
	long int Loop_values;//���[�v�̌v�Z
	std::vector<std::vector<long double>> Cost_matrix;//�ő�R�X�g
	std::map<std::tuple<long int, long int>, std::string> Area_list;//�G���A�̖��O
	std::unordered_map<std::string, long int> area_name;//�G���A�̖��O
	std::unordered_map< long int, std::string> reverse_area_name;//�G���A�̎��o��

	//�ڍאݒ�
	std::vector<double> probability_of_workplace_area;//�E��̃G���A�̊m��
	std::vector<double> probability_of_residence_area;//�Z���̃G���A�̊m��
	std::vector<double> probability_of_shopping_area;//�������̃G���A�̊m��
	std::vector<double> probability_of_school_area_elementary;//�w�Z�̃G���A�̊m��
	std::vector<double> probability_of_school_area_JHS;//�w�Z�̃G���A�̊m��
	std::vector<double> probability_of_school_area_HS;//�w�Z�̃G���A�̊m��
	std::vector<double> probability_of_school_area_university;//�w�Z�̃G���A�̊m��
	std::vector<double> probability_of_hospital_area;//�a�@�̃G���A�̊m��
	std::vector<double> probability_of_sightseeing_area;//�ό��̃G���A�̊m��
	std::vector<double> probability_of_other_area;//�ό��̃G���A�̊m��

private:

	std::vector<std::vector<std::string>> Area_list_name;//�G���A�̓s�s�Ɩ��O
	long int X_distance_of_Area;//�������̃G���A�̐�
	long int Y_distance_of_Area;//�������̃G���A�̐�
	long int Number_of_areas;//���ׂẴG���A��
	void create_area();//�G���A�̍쐬
	void overall_value();//���O���̐ݒ�
	void create_area_detail();//�ڍׂ̐ݒ�
	void calculation_of_costs();//�v�Z�̃R�X�g
	void plot_cost_func(std::vector<std::vector<long double>>&, std::unordered_map< long int, std::string>&);//�R�X�g�̕\��
	void detail_area();//�G���A�̐ݒ�
	void detail_Plac_area();
};

