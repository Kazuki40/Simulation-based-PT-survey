#pragma once


class personal {

private:
public:
	//性別
	int Sex; // 1: man 2: female

	//年齢
	int Age;//0-120

	//職業・学生
	int Work_status; //0:inemployed 1:employed 2:student

	//場所
	int Work_place; 

	//車の有無
	int Hold_driving_license;

	//通勤で車
	bool To_work_by_transportation;

	//公共交通利用確率
	double Probability_of_transportation_weekdays;

	//公共交通利用確率
	double  Probability_of_transportation_weekends;

	bool hold_IC;


	personal();
	~personal();

	//計算
	void calculate();

};

