#pragma once
#include<vector>
#include"personal.h"

class householder
{
private:

public:

	householder();
	~householder();

	std::vector<personal> personal_list;//世帯の人数分の人物

	int Number_of_household_members;//世帯の人数
	int Number_of_vehicle;//世帯の車の数
	int Number_of_cycle;//世帯の自転車の数

};

