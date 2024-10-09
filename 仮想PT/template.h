#pragma once
#include<vector>
#include<string>
#include<map>
#include<unordered_map>
#include<tuple>
#include<algorithm>
#include<iostream>

namespace  custom_function {

	//スプリント関数
	std::vector<std::string> split(std::string str, char del) {
		unsigned long long int first = 0;
		unsigned long long int last = str.find_first_of(del);

		std::vector<std::string> result;

		while (first < str.size()) {
			std::string subStr(str, first, last - first);

			result.push_back(subStr);

			first = last + 1;
			last = str.find_first_of(del, first);

			if (last == std::string::npos) {
				last = str.size();
			}
		}

		return result;
	}



	template<typename vector_type> void plot_area(std::vector<std::vector<vector_type>> temp_vector_data) {

		long int data_loop_x = 0;
		long int data_loop_y = 0;
		std::cout << "エリア" << std::endl;

		std::cout << "  | ";
		for (data_loop_x = 0; data_loop_x < temp_vector_data.size(); data_loop_x++) {

			std::cout << data_loop_x << " | ";
		}
		std::cout << std::endl;

		for (data_loop_y = (temp_vector_data[0].size() - 1); data_loop_y >= 0; data_loop_y--) {
			std::cout << data_loop_y << " | ";

			for (data_loop_x = 0; data_loop_x < temp_vector_data.size(); data_loop_x++) {

				std::cout << temp_vector_data[data_loop_x][data_loop_y] << " | ";
			}
			std::cout << std::endl;
		}


		return;
	}

	std::vector<std::vector<long double>> floyd_warshall_algorithm(std::vector<std::vector<long double>>& matrix) {

		for(auto temp_loop_i=0;temp_loop_i<matrix.size();temp_loop_i++){
			for (auto temp_loop_j = 0; temp_loop_j < matrix.size(); temp_loop_j++) {
				for (auto temp_loop_k = 0; temp_loop_k < matrix.size(); temp_loop_k++) {
					matrix[temp_loop_j][temp_loop_k] = std::min(matrix[temp_loop_j][temp_loop_k],(matrix[temp_loop_j][temp_loop_i] + matrix[temp_loop_i][temp_loop_k]));
				}
			}
		
		}
		return matrix;
	}




}
