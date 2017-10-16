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
	int student_number; // 学生总人数
	int department_number; // 部门总人数
	Student* stu;     //定义指向结构体Student的数据的指针变量stu
	Department* dep;   //定义指向结构体Department的数据的指针变量dep 
public:
	
	DistributeSystem();
	DistributeSystem(int stu_num, int dep_num); //stu_num
	~DistributeSystem();
	void generate_department_information();// 初始化部门信息
	void generate_student_information();//初始化学生信息	
	int get_department_index(int department_no);// 根据部门编号返回他在<部门数组>中的下标	
	int get_student_index(int student_no);// 根据学号返回他在<学生数组>中的下标
	int get_stu_department_index(int i, int chosen_num, int department_no);
	int get_student_now_tag_same_num(int student_no, int department_no);
	void schedule_insert(int student_no, int department_no);//将部门的行程加入已中选学生的行程	
	void distribute();// 根据分配原则进行学生-部门分配

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