#pragma once
#include <iostream>
#include<vector>
#include<string>

#include"householder.h"
#include"personal.h"
#include"visitors.h"
#include"area.h"
#include"setting_by_transportation.h"
#include"Generate_parson.h"
#include"estimate_move.h"
#include"template.h"
#include"enums.h"

//施設
enum facility_type {
	home,
	work,
	school,
	shop,
	hospital,
	other,
	sightseeing,
	COUNT
};


struct users_stay {
	int zone_area = -1;
	std::string zone_name = "aaa";
	facility_type facility;
};

struct users_trip {
	long int departure_time; //出発
	long int arrival_time;//到着

	std::vector<long int> time;// 移動時間
	std::vector<mode_type> mode;//手段
	mode_type main_mode;

};


class estimate_move
{
private:
	//キーの情報
	area this_area;
	setting_by_transportation this_tram;
	householder *this_householder;
	std::unordered_map< long int, std::string> string_map;

	long long int stay_area_num;

	void setting();
	void trip_setting();
	void setting_work_place();

public:
	estimate_move();
	~estimate_move();

	std::vector<long long int >trip_num;//トリップ数

	facility_type estimate_func(facility_type, bool, bool);
	std::vector<std::vector<users_stay>>people_facility;
	std::vector< std::vector< users_trip>> people_trip;

	std::vector<users_stay> estimate_move_func(long long int, facility_type, bool);

	void external_input(area, setting_by_transportation, householder&, long long int, std::unordered_map< long int, std::string>);
	
};

