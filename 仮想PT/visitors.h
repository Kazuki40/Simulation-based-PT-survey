#pragma once
#include<vector>
#include<limits>
#include<random>
class visitors
{
	public:
		bool Use_Vehicle;
		int Purpose_of_visit; //0: Worker 1:Sightseeing;
		int aim; //�ړI�n
		int  how_many_time_per_year; //�N�ԉ���K��邩
		visitors();
		~visitors();
		void setting_func();
		bool hold_IC;
};

