#pragma once
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<limits.h>
#include <stdbool.h>
#include"enums.h"

#define rand_min 0
#define rand_max LLONG_MAX

#define wight_of_0to9 71788149768399400
#define wight_of_10to19 86383813690169800
#define wight_of_20to29 102266147709727000
#define wight_of_30to39 107975746268657000
#define wight_of_40to49 135751737004632000
#define wight_of_50to59 144171384457025000
#define wight_of_60to69 119338651569738000
#define wight_of_70to79 130999099330932000
#define wight_of_80to89 79395586721564600
#define wight_of_90to99 21246139989706600
#define wight_of_100more 699626865671642

//«•Ê‚Ì”ä—¦‚Ìİ’è
int Sex_s_test_function(long long int rand_num) {
	int ans = -1;

	//«•Ê‚Ì”ä—¦
	double sex_rate = 0.5;

	long long int mid = (long long int)roundl((double)(rand_min + rand_max) * sex_rate);


	//’j
	if ((rand_min <= rand_num) && (rand_num <= mid)) {
		ans = 1;
	}
	else if ((mid < rand_num) && (rand_num <= rand_max)) {
		//—
		ans = 0;
	}
	else {
		fprintf(stderr, "rand_error");
	}

	return ans;

}

int Age_step_func(long long int num) {

	int ans = -1;

	long long int wight_age = wight_of_0to9 + wight_of_10to19 + wight_of_20to29 + wight_of_30to39 + wight_of_40to49 + wight_of_50to59 + wight_of_60to69 + wight_of_70to79 + wight_of_80to89 + wight_of_90to99 + wight_of_100more;

	long double wight_age_0to9 = (long double)wight_of_0to9 / wight_age;
	long double wight_age_10to19 = wight_age_0to9 + (long double)wight_of_10to19 / wight_age;
	long double wight_age_20to29 = wight_age_10to19 + (long double)wight_of_20to29 / wight_age;
	long double wight_age_30to39 = wight_age_20to29 + (long double)wight_of_30to39 / wight_age;
	long double wight_age_40to49 = wight_age_30to39 + (long double)wight_of_40to49 / wight_age;
	long double wight_age_50to59 = wight_age_40to49 + (long double)wight_of_50to59 / wight_age;
	long double wight_age_60to69 = wight_age_50to59 + (long double)wight_of_60to69 / wight_age;
	long double wight_age_70to79 = wight_age_60to69 + (long double)wight_of_70to79 / wight_age;
	long double wight_age_80to89 = wight_age_70to79 + (long double)wight_of_80to89 / wight_age;
	long double wight_age_90to99 = wight_age_80to89 + (long double)wight_of_90to99 / wight_age;

	//‹æ‰æ
	long long int age_0to9 = (long long int)roundl((long double)rand_max * wight_age_0to9);
	long long int age_10to19 = (long long int)roundl((long double)rand_max * wight_age_10to19);
	long long int age_20to29 = (long long int)roundl((long double)rand_max * wight_age_20to29);
	long long int age_30to39 = (long long int)roundl((long double)rand_max * wight_age_30to39);
	long long int age_40to49 = (long long int)roundl((long double)rand_max * wight_age_40to49);
	long long int age_50to59 = (long long int)roundl((long double)rand_max * wight_age_50to59);
	long long int age_60to69 = (long long int)roundl((long double)rand_max * wight_age_60to69);
	long long int age_70to79 = (long long int)roundl((long double)rand_max * wight_age_70to79);
	long long int age_80to89 = (long long int)roundl((long double)rand_max * wight_age_80to89);
	long long int age_90to99 = (long long int)roundl((long double)rand_max * wight_age_90to99);

	if ((rand_min <= num) && (num <= age_0to9)) {
		ans = 0 + num % 10;
	}
	else if ((age_0to9 < num) && (num <= age_10to19)) {
		ans = 10 + num % 10;
	}
	else if ((age_10to19 < num) && (num <= age_20to29)) {
		ans = 20 + num % 10;
	}
	else if ((age_20to29 < num) && (num <= age_30to39)) {
		ans = 30 + num % 10;
	}
	else if ((age_30to39 < num) && (num <= age_40to49)) {
		ans = 40 + num % 10;
	}
	else if ((age_40to49 < num) && (num <= age_50to59)) {
		ans = 50 + num % 10;
	}
	else if ((age_50to59 < num) && (num <= age_60to69)) {
		ans = 60 + num % 10;
	}
	else if ((age_60to69 < num) && (num <= age_70to79)) {
		ans = 70 + num % 10;
	}
	else if ((age_70to79 < num) && (num <= age_80to89)) {
		ans = 80 + num % 10;
	}
	else if ((age_80to89 < num) && (num <= age_90to99)) {
		ans = 90 + num % 10;
	}
	else if ((age_90to99 < num) && (num <= rand_max)) {
		ans = 100 + num % 20;
	}
	else {
		fprintf(stderr, "rand_error");
	}

	return ans;


}


int Age_s_test_function(long long int rand_num) {

	int ans = Age_step_func(rand_num);


	return ans;
}


//”N—î
int work_s_test_function(long long int rand_num, int age) {

	int ans = -1;
	int temp_num = -1;

	if ((age == 6) || (age == 12) || (age == 15) || (age == 18) || (age == 22) || (age == 24) || (age == 65) || (age == 70) || (age == 75)) {
		temp_num = rand_num % 2;
		if (temp_num == 0) {
			age--;
		}
	}



	if (age < 6) {
		ans = preschoolers;
	}
	else if ((6 <= age) && (age < 12)) {
		ans = primary_school;
	}
	else if ((12 <= age) && (age < 15)) {
		ans = junior_high_school;
	}
	else if ((15 <= age) && (age < 18)) {
		temp_num = rand_num % 100;

		if (temp_num == 0) {
			ans = worker;
		}
		else {
			ans = high_school;
		}
	}
	else if ((18 <= age) && (age < 22)) {

		temp_num = rand_num % 10;
		if (temp_num <= 5) {
			ans = student;
		}
		else {
			ans = worker;
		}
	}
	else if ((22 <= age) && (age < 24)) {
		temp_num = rand_num % 100;

		if (temp_num <= 11) {
			ans = student;
		}
		else {
			ans = worker;
		}
	}
	else if ((24 <= age) && (age < 65)) {
		temp_num = rand_num % 100;

		if (temp_num == 0) {
			ans = student;
		}
		else if (temp_num == 1) {
			ans = unemployment;
		}
		else {
			ans = worker;
		}
	}
	else if ((65 <= age) && (age < 70)) {
		temp_num = rand_num % 2;

		if (temp_num == 0) {
			ans = worker;
		}
		else {
			ans = unemployment;
		}
	}
	else if ((70 <= age) && (age < 75)) {
		temp_num = rand_num % 10;

		if (temp_num <= 2) {
			ans = worker;
		}
		else {
			ans = unemployment;
		}
	}
	else if (75 <= age) {
		temp_num = rand_num % 10;

		if (temp_num == 0) {
			ans = worker;
		}
		else {
			ans = unemployment;
		}
	}

	return ans;
}

//‰^“]–Æ‹–
int  Hold_driving_license_test_function(long long int rand_num, int sex, int age) {
	// ttps://www8.cao.go.jp/koutu/taisaku/r03kou_haku/zenbun/genkyo/h1/h1b1s2_3.html

	int  ans = -1;

	int temp = rand_num % 1000;

	int array_1[] = { 0,211,768,879,935,966,966,969,971,969,944,905,879,709,436 };
	int array_2[] = { 0,161,692,827,874,909,913,915,907,883,820,708,559,312,8 };
	int use;
	if (age <= 15) {
		use = 0;
	}
	else if (age >= 80) {
		use = 14;
	}
	else {
		use = round(age / 5) - 2;
	}

	if (sex == 1) {

		if (temp <= array_1[use]) {
			ans = 1;
		}
		else {
			ans = 0;
		}

	}
	else {
		if (temp <= array_2[use]) {
			ans = 1;
		}
		else {
			ans = 0;
		}

	}

	if ((70 <= age) && (ans == 0)) {

		if (temp >= 950) {
			ans = 2;
		}
	}


	return ans;
}


//’Ê‹Î‚ÅŒö‹¤Œğ’Ê
bool To_work_by_transportation_test_function(long long int rand_num, int work) {
	bool ans = false;

	int temp = rand_num % 100;

	if ((temp < 20) && (work == worker)) {
		ans = true;
	}
	else {
		ans = false;
	}

	return ans;
}


//’Ê‹Î‚ÅŒö‹¤Œğ’Ê
bool hold_IC_test_function(long long int rand_num, int age) {
	bool ans = false;

	int temp = rand_num % 100;

	if (age < 65) {
		if (temp < 70) {
			ans = true;
		}
	}
	else {
		if (temp < 90) {
			ans = true;
		}
	}


	return ans;
}