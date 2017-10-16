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

//�����е������뷶����distribute.exe sxxx-dxxx-in.json sxxx-dxxx-out.json
int main(int argc, char** argv)
{
	srand(time(NULL));
	int student_number = 0;
	int department_number = 0;

	//���������ѧ���벿�ŵ�����
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

	ds.generate_department_information();	// ��ʼ��������Ϣ
	ds.generate_student_information();		// ��ʼ��ѧ����Ϣ
	ds.distribute();						// ƥ�䲿����ѧ��

	ds.get_department_result(true);			// ���ɷ��䵽ѧ���Ĳ����б�
	ds.get_student_result(true);			// ���ɷ��䵽���ŵ�ѧ���б�
	ds.get_department_result(false);		// ����δ���䵽ѧ���Ĳ����б�
	ds.get_student_result(false);			// ����δ���䵽���ŵ�ѧ���б�

	write(argv[2]);

	//system("pause");
	return 0;
}
