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
	int department_no; // ���ű��
	string department_name;  //��������
	int department_member_limit;   // ��������
	float department_score_limit;  //����Ҫ������
	int schedule_count;   //�����г�����
	string department_schedule[10];  //���ų���ʱ��
	int tag_count;     //���ű�ǩ��
	string department_tag[10];       //���ű�ǩ
	int chosen_num;  // ����ѡ��ѧ����
	int student_no[15]; // ��ѡ��ѧ��ѧ��
};

#endif 