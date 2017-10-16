#include <iostream>
#include <stdio.h>
#include <ostream>
#include <fstream>
#include "json.hpp"
#include "read.h"
#include "student.h"
#include "department.h"
#include "distributeSystem.h"
using namespace std;
using json = nlohmann::json;

//Student student[5000];//存储从json读入的student信息
//Department department[100];//存储从json读入的department信息

/*从json读取student信息*/
void student_from_json(const json& j, Student& student)
{
	student.student_no = j.at("student_no").get<int>();
	//cout << endl << student.student_no << endl;
	student.student_name = j.at("student_name").get<string>();
	//cout << student.student_name << endl;
	student.student_score = j.at("student_score").get<float>();
	//cout << student.student_score << endl;
	student.student_cur = j.at("student_cur").get<int>();
	//cout << student.student_cur << endl;
	student.schedule_count = j.at("schedule_count").get<int>();
	//cout << student.schedule_count << endl;
	student.tag_count = j.at("tag_count").get<int>();
	//cout << student.tag_count << endl;
	student.wish_count = j.at("wish_count").get<int>();
	//cout << student.wish_count << endl;
	for (int k = 0; k < j.at("student_tag").size(); k++)
		student.student_tag[k] = j.at("student_tag")[k].get<string>();
	for (int k = 0; k < j.at("student_schedule").size(); k++)
		student.student_schedule[k] = j.at("student_schedule")[k].get<string>();
	for (int k = 0; k < j.at("student_wish").size(); k++)
		student.student_wish[k] = j.at("student_wish")[k].get<int>();
}

/*存储从json读取department信息*/
void department_from_json(const json& j, Department& department)
{
	department.department_no = j.at("department_no").get<int>();
	//cout << endl << department.department_no << endl;
	department.department_name = j.at("department_name").get<string>();
	//cout << department.department_name << endl;
	department.department_score_limit = j.at("department_score_limit").get<float>();
	//cout << department.department_score_limit << endl;
	department.department_member_limit = j.at("department_member_limit").get<int>();
	department.chosen_num = j.at("chosen_num").get<int>();
	//cout << department.chosen_num << endl;
	department.schedule_count = j.at("schedule_count").get<int>();
	//cout << department.schedule_count << endl;
	department.tag_count = j.at("tag_count").get<int>();
	//cout << department.tag_count << endl;
	for (int k = 0; k < j.at("department_tag").size(); k++)
	{
		department.department_tag[k] = j.at("department_tag")[k].get<string>();
		//cout << department.department_tag[k] << endl;
	}
	for (int k = 0; k < j.at("department_schedule").size(); k++)
	{
		department.department_schedule[k] = j.at("department_schedule")[k].get<string>();
		//cout << department.department_schedule[k] << endl;
	}
}

/*读取.json文件*/
void read(string file_name, DistributeSystem& ds)
{
	json jset;
	fstream json_input(file_name);
	json_input >> jset;

	if (jset.find("department") != jset.end())
	{
		int size = jset.at("department").size();
		for (int i = 0; i < size; i++)
		{
			department_from_json(jset.at("department")[i].get<json>(), ds.dep[i]);
			//cout << "??" << endl;
		}
	}

	if (jset.find("student") != jset.end())
	{
		int size = jset.at("student").size();
		for (int i = 0; i < size; i++)
			student_from_json(jset.at("student")[i].get<json>(), ds.stu[i]);
	}
}