#pragma once
#ifndef __DISTRIBUTESYSTEM_H_
#define __DISTRIBUTESYSTEM_H_
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <ctime>
#include <queue>
#include <map>
#include<ostream>
#include<fstream>
#include"json.hpp"
#include"read.h"
#include"write.h"
#include"student.h"
#include"department.h"
using namespace std;
using json = nlohmann::json;

class DistributeSystem {
private:
	int student_number; // ѧ��������
	int department_number; // ����������
	Student* stu;     //����ָ��ṹ��Student�����ݵ�ָ�����stu
	Department* dep;   //����ָ��ṹ��Department�����ݵ�ָ�����dep 
public:
	
	DistributeSystem();
	DistributeSystem(int stu_num, int dep_num); //stu_num
	~DistributeSystem();
	void generate_department_information();// ��ʼ��������Ϣ
	void generate_student_information();//��ʼ��ѧ����Ϣ	
	int get_department_index(int department_no);// ���ݲ��ű�ŷ�������<��������>�е��±�	
	int get_student_index(int student_no);// ����ѧ�ŷ�������<ѧ������>�е��±�
	int get_stu_department_index(int i, int chosen_num, int department_no);
	int get_student_now_tag_same_num(int student_no, int department_no);
	void schedule_insert(int student_no, int department_no);//�����ŵ��г̼�������ѡѧ�����г�	
	void distribute();// ���ݷ���ԭ�����ѧ��-���ŷ���

	//setfill('0') << setw(5) <<
	void get_department_result(bool flag);
	void get_student_result(bool flag);
	void schedule_delete(int student_no, int department_no);

	friend void student_from_json(const json& j, Student& student);
	friend void department_from_json(const json& j, Department& department);
	friend void read(string file_name, DistributeSystem& ds);

	friend void matched_student_to_json(const Student& student);
	friend void standalone_student_to_json(const Student& student);
	friend void matched_department_to_json(const Department& department);
	friend void standalone_department_to_json(const Department& department);
};

#endif