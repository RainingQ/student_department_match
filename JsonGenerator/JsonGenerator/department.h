#pragma once
#pragma once
#ifndef __DEPARTMENT_H_
#define __DEPARTMENT_H_
#include<iostream>
#include<string>
using namespace std;

struct Department {
	int department_no;
	//char department_name[20];
	string department_name;
	int department_member_limit;
	float department_score_limit;
	string department_schedule[10];
	string department_tag[10];
	int chosen_num;
	int student_no[15];
};

#endif 