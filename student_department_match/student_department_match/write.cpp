#include<iostream>
#include<ostream>
#include<fstream>
#include"json.hpp"
#include"write.h"
#include"student.h"
#include"department.h"
using namespace std;
using json = nlohmann::json;

json jres;//�洢�����������

/*�ɹ�ƥ�䲿�ŵ�ѧ��*/
void matched_student_to_json(const Student& student)
{
	json j = json{
		{ "student_no", student.student_no },
		{"student_score", student.student_score}
	};
	for (int k = 0; k < student.chosen_num; k++)
	{
		/*if (student.department_no[k] == 0 || student.department_no[k] == -1)
			continue;*/
		j["department_no"].push_back(student.department_no[k]);
	}
	jres["matched_student_view"].push_back(j);
}

/*δ������ѡ�е�ѧ��*/
void standalone_student_to_json(const Student& student)
{
	json j = json{
		{ "student_no", student.student_no }
	};
	jres["standalone_students"].push_back(j);
}

/*�ɹ�ƥ��ѧ���Ĳ���*/
void matched_department_to_json(const Department& department)
{
	json j = json{
		{ "department_no", department.department_no },
		{ "department_member_limit", department.department_member_limit },
		{ "chosen_num", department.chosen_num }
	};
	for (int k = 0; k < department.chosen_num; k++)
		j["student_no"].push_back(department.student_no[k]);
	jres["matched_department_view"].push_back(j);
}

/*δ���䵽ѧ���Ĳ���*/
void standalone_department_to_json(const Department& department)
{
	json j = json{
		{ "department_no", department.department_no }
	};
	jres["standalone_departments"].push_back(j);
}

/*���.json�ļ�*/
void write(string file_name)
{
	ofstream json_output(file_name);
	json_output << setw(4) << jres << endl;
}