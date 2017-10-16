#pragma once
#ifndef __STUDENT_H_
#define __STUDENT_H_

#include<iostream>
#include<string>
#include"student.h"
using namespace std;

//struct Student {
//	int student_no;
//	float student_score;
//	string student_name;
//	string student_tag[10];
//	string student_schedule[50];
//	int student_wish[5];
//	int schedule_count;
//	int tag_count;
//	int wish_count;
//	int department_no[5];
//	int department_count;
//	int student_cur;
//};

struct Student {
	int student_no; // 学号
	string student_name; //学生姓名
	float student_score;   //学生绩点
	int tag_count;    //学生标签数
	string student_tag[10];    //学生标签
	int wish_count;    //学生志愿数
	int student_wish[5];    // 学生部门志愿，不多于5个
	int schedule_count;   //学生行程总数
	string student_schedule[70]; //学生行程时间
	int chosen_num;   //已中选的部门数
	int department_no[5];    //中选的部门编号
	int student_cur;        // 当前分配进程正在考虑第student_cur个志愿
	int tag_same_num[5];       //学生与已中选部门的标签类似数
	int now_tag_same_num;     //学生与当前考虑的部门的标签类似数
};

#endif 