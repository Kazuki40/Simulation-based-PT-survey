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
	void set_start();//初期設定
	long int Loop_values;//ループの計算
	std::vector<std::vector<long double>> Cost_matrix;//最大コスト
	std::map<std::tuple<long int, long int>, std::string> Area_list;//エリアの名前
	std::unordered_map<std::string, long int> area_name;//エリアの名前
	std::unordered_map< long int, std::string> reverse_area_name;//エリアの取り出し

	//詳細設定
	std::vector<double> probability_of_workplace_area;//職場のエリアの確率
	std::vector<double> probability_of_residence_area;//住居のエリアの確率
	std::vector<double> probability_of_shopping_area;//買い物のエリアの確率
	std::vector<double> probability_of_school_area_elementary;//学校のエリアの確率
	std::vector<double> probability_of_school_area_JHS;//学校のエリアの確率
	std::vector<double> probability_of_school_area_HS;//学校のエリアの確率
	std::vector<double> probability_of_school_area_university;//学校のエリアの確率
	std::vector<double> probability_of_hospital_area;//病院のエリアの確率
	std::vector<double> probability_of_sightseeing_area;//観光のエリアの確率
	std::vector<double> probability_of_other_area;//観光のエリアの確率

private:

	std::vector<std::vector<std::string>> Area_list_name;//エリアの都市と名前
	long int X_distance_of_Area;//ｘ方向のエリアの数
	long int Y_distance_of_Area;//ｙ方向のエリアの数
	long int Number_of_areas;//すべてのエリア数
	void create_area();//エリアの作成
	void overall_value();//事前情報の設定
	void create_area_detail();//詳細の設定
	void calculation_of_costs();//計算のコスト
	void plot_cost_func(std::vector<std::vector<long double>>&, std::unordered_map< long int, std::string>&);//コストの表示
	void detail_area();//エリアの設定
	void detail_Plac_area();
};

