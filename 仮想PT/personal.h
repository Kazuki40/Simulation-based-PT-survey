#pragma once


class personal {

private:
public:
	//����
	int Sex; // 1: man 2: female

	//�N��
	int Age;//0-120

	//�E�ƁE�w��
	int Work_status; //0:inemployed 1:employed 2:student

	//�ꏊ
	int Work_place; 

	//�Ԃ̗L��
	int Hold_driving_license;

	//�ʋ΂Ŏ�
	bool To_work_by_transportation;

	//������ʗ��p�m��
	double Probability_of_transportation_weekdays;

	//������ʗ��p�m��
	double  Probability_of_transportation_weekends;

	bool hold_IC;


	personal();
	~personal();

	//�v�Z
	void calculate();

};

