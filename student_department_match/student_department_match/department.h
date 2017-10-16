#pragma once
#ifndef __DEPARTMENT_H_
#define __DEPARTMENT_H_

#include<iostream>
#include<string>
#include"department.h"
using namespace std;

//struct Department {
//	int department_no;
//	int department_member_limit;
//	float department_score_limit;
//	string department_name;
//	string department_schedule[10];
//	string department_tag[10];
//	int schedule_count;
//	int tag_count;
//	int chosen_num;
//	int student_no[15];
//};

struct Department {
	int department_no; // 部门编号
	string department_name;  //部门名称
	int department_member_limit;   // 纳新上限
	float department_score_limit;  //绩点要求下限
	int schedule_count;   //部门行程总数
	string department_schedule[10];  //部门常规活动时间
	int tag_count;     //部门标签数
	string department_tag[10];       //部门标签
	int chosen_num;  // 已中选的学生数
	int student_no[15]; // 中选的学生学号
};

#endif 