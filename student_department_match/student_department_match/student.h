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
	int student_no; // ѧ��
	string student_name; //ѧ������
	float student_score;   //ѧ������
	int tag_count;    //ѧ����ǩ��
	string student_tag[10];    //ѧ����ǩ
	int wish_count;    //ѧ��־Ը��
	int student_wish[5];    // ѧ������־Ը��������5��
	int schedule_count;   //ѧ���г�����
	string student_schedule[70]; //ѧ���г�ʱ��
	int chosen_num;   //����ѡ�Ĳ�����
	int department_no[5];    //��ѡ�Ĳ��ű��
	int student_cur;        // ��ǰ����������ڿ��ǵ�student_cur��־Ը
	int tag_same_num[5];       //ѧ��������ѡ���ŵı�ǩ������
	int now_tag_same_num;     //ѧ���뵱ǰ���ǵĲ��ŵı�ǩ������
};

#endif 