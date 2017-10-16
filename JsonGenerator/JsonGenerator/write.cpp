#include<iostream>
#include<ostream>
#include<fstream>
#include"json.hpp"
#include"read.h"
#include"write.h"
#include"student.h"
#include"department.h"
using namespace std;
using json = nlohmann::json;

json jres;//存储所有最终输出

/*成功匹配部门的学生*/
void matched_student_to_json(json& j, const Student& student)
{
	j = json{
		{ "student_no", student.student_no }
	};
	for (int k = 0; k < student.department_count; k++)
		j["department_no"].push_back(student.department_no[k]);
	jres["matched_student_view"].push_back(j);
}

/*未被部门选中的学生*/
void standalone_student_to_json(json& j, const Student& student)
{
	j = json{
		{ "student_no", student.student_no }
	};
	jres["standalone_students"].push_back(j);
}

/*成功匹配学生的部门*/
void matched_department_to_json(json& j, const Department& department)
{
	j = json{
		{ "department_no", department.department_no },
		{ "department_member_limit", department.department_member_limit },
		{ "chosen_num", department.chosen_num }
	};
	for (int k = 0; k < department.chosen_num; k++)
		j["student_no"].push_back(department.student_no[k]);
	jres["matched_department_view"].push_back(j);
}

/*未分配到学生的部门*/
void standalone_department_to_json(json& j, const Department& department)
{
	j = json{
		{ "department_no", department.department_no }
	};
	jres["standalone_departments"].push_back(j);
}

/*输出.json文件*/
void write(string file_name)
{
	ofstream json_output(file_name);
	json_output << setw(4) << jres << endl;
}