#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <ctime>
#include <queue>
#include <map>
#include <ostream>
#include <fstream>
#include "json.hpp"
#include "read.h"
#include "write.h"
#include "student.h"
#include "department.h"
#include "distributeSystem.h"
using namespace std;
using json = nlohmann::json;

extern json jres;

//命令行调用输入范例：distribute.exe sxxx-dxxx-in.json sxxx-dxxx-out.json
int main(int argc, char** argv)
{
	srand(time(NULL));
	int student_number = 0;
	int department_number = 0;

	//获得输入中学生与部门的数量
	for (int i = 0; i < strlen(argv[1]); i++)
	{
		if (argv[1][i] == 's')
		{
			int j = i + 1;
			string tmp;
			while (argv[1][j] != '-')
				tmp += to_string(argv[1][j++] - 48);
			student_number = stoi(tmp);
			i = j;
		}

		if (argv[1][i] == 'd')
		{
			int j = i + 1;
			string tmp;
			while (argv[1][j] != '-')
				tmp += to_string(argv[1][j++] - 48);
			department_number = stoi(tmp);
			i = j;
		}

		if (argv[1][i] == '.')
			break;
	}
	//cout << "sn = " << student_number << endl;
	//cout << "dn = " << department_number << endl;	

	DistributeSystem ds(student_number, department_number);

	read(argv[1], ds);

	ds.generate_department_information();	// 初始化部门信息
	ds.generate_student_information();		// 初始化学生信息
	ds.distribute();						// 匹配部门与学生

	ds.get_department_result(true);			// 生成分配到学生的部门列表
	ds.get_student_result(true);			// 生成分配到部门的学生列表
	ds.get_department_result(false);		// 生成未分配到学生的部门列表
	ds.get_student_result(false);			// 生成未分配到部门的学生列表

	write(argv[2]);

	//system("pause");
	return 0;
}
