#pragma once
#ifndef __STUDENT_H_
#define __STUDENT_H_
#include<iostream>
#include<string>
using namespace std;

struct Student {
	int student_no;
	//char student_name[20];
	string student_name;
	float student_score;
	string student_tag[10];
	int student_wish[5];
	string student_schedule[50];
	int department_no[5];
	int department_count;
	int student_cur;
}; 

#endif 