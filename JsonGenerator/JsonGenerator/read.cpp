#include<iostream>
#include<ostream>
#include<fstream>
#include"json.hpp"
#include"read.h"
#include"student.h"
#include"department.h"
using namespace std;
using json = nlohmann::json;

extern Student student[5000];//存储从json读入的student信息
extern Department department[100];//存储从json读入的department信息
int i = 0;

/*从json读取student信息*/
void student_from_json(const json& j)
{
	student[i].student_no = j.at("student_no").get<int>();
	student[i].student_name = j.at("student_name").get<string>();
	student[i].student_score = j.at("student_score").get<float>();
	student[i].student_cur = j.at("student_cur").get<int>();
	for (int k = 0; k < j.at("student_tag").size(); k++)
		student[i].student_tag[k] = j.at("student_tag")[k].get<string>();
	for (int k = 0; k < j.at("student_schedule").size(); k++)
		student[i].student_schedule[k] = j.at("student_schedule")[k].get<string>();
	for (int k = 0; k < j.at("student_wish").size(); k++)
		student[i].student_wish[k] = j.at("student_wish")[k].get<int>();
}

/*存储从json读取department信息*/
void department_from_json(const json& j)
{
	department[i].department_no = j.at("department_no").get<int>();
	department[i].department_name = j.at("department_name").get<string>();
	department[i].department_score_limit = j.at("department_score_limit").get<float>();
	department[i].department_member_limit = j.at("department_member_limit").get<int>();
	department[i].chosen_num = j.at("chosen_num").get<int>();
	for (int k = 0; k < j.at("department_tag").size(); k++)
		department[i].department_tag[k] = j.at("department_tag")[k].get<string>();
	for (int k = 0; k < j.at("department_schedule").size(); k++)
		department[i].department_schedule[k] = j.at("department_schedule")[k].get<string>();
}

/*读取.json文件*/
void read(string file_name)
{
	json jset;
	fstream json_input(file_name);
	json_input >> jset;

	if (jset.find("department") != jset.end())
	{
		int size = jset.at("department").size();
		for (i = 0; i < size; i++)
			department_from_json(jset.at("department")[i].get<json>());
	}

	if (jset.find("student") != jset.end())
	{
		int size = jset.at("student").size();
		for (i = 0; i < size; i++)
			student_from_json(jset.at("student")[i].get<json>());
	}
}