#pragma once
#include "template.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

namespace custom_function {
    // スプリット関数の実装
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

    // 最短経路探索の実装
    std::vector<std::vector<long double>> floyd_warshall_algorithm(std::vector<std::vector<long double>>& matrix) {
        for (auto temp_loop_i = 0; temp_loop_i < matrix.size(); temp_loop_i++) {
            for (auto temp_loop_j = 0; temp_loop_j < matrix.size(); temp_loop_j++) {
                for (auto temp_loop_k = 0; temp_loop_k < matrix.size(); temp_loop_k++) {
                    matrix[temp_loop_j][temp_loop_k] = std::min(matrix[temp_loop_j][temp_loop_k],
                        (matrix[temp_loop_j][temp_loop_i] + matrix[temp_loop_i][temp_loop_k]));
                }
            }
        }
        return matrix;
    }
}
