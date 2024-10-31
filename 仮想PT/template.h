#pragma once
#include <vector>
#include <string>
#include <iostream>

namespace custom_function {
    std::vector<std::string> split(std::string str, char del);

    template<typename vector_type>
    void plot_area(std::vector<std::vector<vector_type>> temp_vector_data) {
        long int data_loop_x = 0;
        long int data_loop_y = 0;
        std::cout << "ƒGƒŠƒA" << std::endl;

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
    }

    std::vector<std::vector<long double>> floyd_warshall_algorithm(std::vector<std::vector<long double>>& matrix);
}
