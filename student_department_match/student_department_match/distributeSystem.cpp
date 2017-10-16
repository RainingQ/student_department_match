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
#include"distributeSystem.h"
using namespace std;
using json = nlohmann::json;

DistributeSystem::DistributeSystem()
{
	stu = NULL;
	dep = NULL;
	student_number = 0;
	department_number = 0;
}

DistributeSystem::DistributeSystem(int stu_num, int dep_num)
{
	student_number = stu_num;
	department_number = dep_num;
	stu = new Student[student_number];        //����һ����СΪstudent_number��Student�����ݵĿռ䣬�ѵ�ַ����stu
	dep = new Department[department_number];   //����һ����СΪdepartment_number��Department�����ݵĿռ䣬�ѵ�ַ����dep
}

DistributeSystem::~DistributeSystem()
{
	delete[] stu;     //�����ÿռ�
	delete[] dep;
}

/*��ʼ��������Ϣ*/
void DistributeSystem::generate_department_information()
{
	for (int i = 0; i < department_number; ++i)
	{
		dep[i].chosen_num = 0; //0��ʾδ���䵽ѧ��
		for (int j = 0; j < dep[i].department_member_limit; ++j)
			dep[i].student_no[j] = 0;//��ʼ������
	}
}

/*��ʼ��ѧ����Ϣ*/
void DistributeSystem::generate_student_information()
{
	for (int i = 0; i < student_number; ++i)
	{
		stu[i].chosen_num = 0; // 0��ʾδ���䵽����
		stu[i].student_cur = 0; // ��ʼ����־Ը1���±�Ϊ0����ʼ����
		stu[i].now_tag_same_num = 0; //��ʼ����ǰ���ű�ǩ������
		for (int k = 0; k < stu[i].wish_count; ++k)
		{
			stu[i].department_no[k] = 0;  //��ʼ������department_no[5]
			stu[i].tag_same_num[k] = -1;  //��ʼ������tab_same_num[5]
		}
	}
}

/*���ݲ��ű�ŷ�������<��������>�е��±�*/
int DistributeSystem::get_department_index(int department_no)
{
	int index;
	for (index = 0; index < department_number; ++index)
	{
		if (dep[index].department_no == department_no)
		{
			break;
		}
	}
	return index;
}

/*����ѧ�ŷ�������<ѧ������>�е��±�*/
int DistributeSystem::get_student_index(int student_no)
{
	int index;
	for (index = 0; index < student_number; ++index)
	{
		if (stu[index].student_no == student_no)
		{
			break;
		}
	}
	return index;
}

/*����ѧ������������±ꡢѧ������ѡ�����������ű�ŷ��ز�����<ѧ��i����ѡ��������>�е��±�*/
int DistributeSystem::get_stu_department_index(int i, int chosen_num, int department_no)
{
	int index;
	for (index = 0; index < chosen_num; ++index)
		if (stu[i].department_no[index] == department_no)
			break;
	return index;
}

/*����ѧ�źͲ��ű�ŷ���ѧ���뵱ǰ�����ǵĲ��ŵı�ǩ������*/
int DistributeSystem::get_student_now_tag_same_num(int student_no, int department_no)
{
	int now_tag_same_num = 0;
	int s_pos = get_student_index(student_no);
	int d_pos = get_department_index(department_no);
	for (int s_j = 0; s_j < stu[s_pos].tag_count; ++s_j)
	{
		for (int s_k = 0; s_k < dep[d_pos].tag_count; ++s_k)
		{
			if (stu[s_pos].student_tag[s_j] == dep[d_pos].department_tag[s_k]) 
			{
				now_tag_same_num++;
			}
		}
	}
	return now_tag_same_num;
}

//�����ŵ��г̼�������ѡѧ�����г�
void DistributeSystem::schedule_insert(int student_no, int department_no) 
{
	int sch_s_pos = get_student_index(student_no);
	int sch_d_pos = get_department_index(student_no);
	int s_schedule_count = stu[sch_s_pos].schedule_count;
	int d_schedule_count = dep[sch_d_pos].schedule_count;
	for (int sch_i = s_schedule_count; sch_i<(s_schedule_count + d_schedule_count); ++sch_i)
		for (int sch_j = 0; sch_j < d_schedule_count; ++sch_j)
				stu[sch_s_pos].student_schedule[sch_i] = dep[sch_d_pos].department_schedule[sch_j];
}

/*���ݷ���ԭ�����ѧ��-���ŷ���*/
void DistributeSystem::distribute() 
{
	queue<Student> student_que; //�������ѧ������
	for (int i = 0; i < student_number; ++i) 
		student_que.push(stu[i]); // ��ʼ����δ����״̬�����ӽ�����
	while (!student_que.empty()) 
	{
		int ss = student_que.front().student_no;
		int sss = get_student_index(ss);
		Student& s = stu[sss];   //����ѧ�����ж���Ԫ��
		student_que.pop();

		// ��һ������ѧ��s�ĵ�student_cur��־Ը������Ϊd��
		int ww = s.student_cur;
		int www = s.student_wish[ww];
		int wwww = get_department_index(www);
		Department& d = dep[wwww];   //���ʲ��Ŷ��ж���Ԫ��

		if (s.student_score >= d.department_score_limit)
		{
			//�ڶ�������ѧ���벿��ʱ���Ƿ��г�ͻ
			int same_schedule_num = 0;
			for (int i = 0; i < s.schedule_count; ++i)
				for (int j = 0; j < d.schedule_count; ++j)
					if (s.student_schedule[i] == d.department_schedule[j])
						same_schedule_num++;

			if (same_schedule_num > 0)
			{
				s.student_cur++;
				if (s.student_cur < s.wish_count)
				{
					// ������־Ը��û������ϵĻ�����������м����������
					student_que.push(s);
				}
			}
			else  
			{
				//��ʱ���޳�ͻ
				//���������ǲ����Ƿ�������
				if (d.department_member_limit > d.chosen_num)
				{
					// �������d����ʣ�����ֱ����ѡ
					int ss = 0;
					ss = s.student_no;
					int dd = d.chosen_num;
					d.student_no[dd] = ss;
					int ddd = s.chosen_num;
					s.department_no[ddd] = d.department_no;
					s.chosen_num++;
					s.student_cur++;
					d.chosen_num++;		

					if (s.student_cur < s.wish_count)
					{
						// ������־Ը��û������ϵĻ�����������м����������
						student_que.push(s);
					}					
				}//δ�՜�
				//�������������Ĳ����Ǳ�ǩ������
				//���ҵ�����d<����ѡѧ����>��ǩ���������ٵ�ѧ��s'
				//��ѧ��s�ı�ǩ��������s�����ٱ�ǩ���Ľ��жԱ�
				else    
				{
					//�������޿�������
					int least_stu_no = -1; // ����d<����ѡѧ����>��ǩ���������ٵ�ѧ��s�����
					int pos = -1; // �Լ�s'�ڲ��ŵ�<����ѡ�б���>���±�
					int stu_pos = -1; //s'��<ѧ������>�е��±�
					int less_stu_dep_pos = -1; //����d��s'��<����ѡ��������>�е��±�
					int least_tag_same_num = 10;         //���ٵı�ǩ������  
														 //float min_point = 5.0;
					s.now_tag_same_num = get_student_now_tag_same_num(s.student_no, d.department_no);  //ѧ��s�벿��d�ı�ǩ������
					for (int i = 0; i < d.chosen_num; ++i)
					{ 
						// �ڲ���d�в��ұ�ǩ���������ٵ�ѧ�����
						stu_pos = get_student_index(d.student_no[i]);     //��������ѡѧ����<ѧ��>������±�
						Student dmp = stu[stu_pos];  //��Ӧ������ѡѧ��
						less_stu_dep_pos = get_stu_department_index(stu_pos, dmp.chosen_num, d.department_no);
						if (least_tag_same_num > dmp.tag_same_num[less_stu_dep_pos])
						{
							least_tag_same_num = dmp.tag_same_num[less_stu_dep_pos];
							least_stu_no = dmp.student_no;
							pos = i;
						}
					}
					//���ж����������Ƿ�Ϊ0 �Լ� ѧ��s�ı�ǩ�����������ٱ�ǩ������less_tag_same_num�Ĵ�С��ϵ
					//����������Ϊ0 ���� ѧ��s�ı�ǩ������<=���ٱ�ǩ������less_tag_same_num ,����ѧ��s����һ��־Ը
					if (d.department_member_limit == 0 || s.now_tag_same_num <= least_tag_same_num)
					{
						s.student_cur++;
						if (s.student_cur < s.wish_count)
						{ 
							// ������־Ը��û������ϵĻ�����������м����������
							student_que.push(s);
						}
					}
					else
					{
						// ��Ȼѧ��s��ֱ���滻����ǩ���������ٵ��Ǹ�ѧ��
						int least_stu_index = get_student_index(least_stu_no);  //���滻����ѧ��s.��<ѧ������>�е��±�
						Student& least_stu = stu[least_stu_index];
						int least_stu_department_index = get_stu_department_index(least_stu_index, least_stu.chosen_num, d.department_no); //����d�ڱ��滻����ѧ��s.<����ѡ��������>�е��±�
						least_stu.department_no[least_stu_department_index] = -1;  //���滻����ѧ���ò��Ŷ���
						//��ʱѧ��s����ѡ��������ѡ��Ϣ
						s.department_no[s.student_cur] = d.department_no;
						s.tag_same_num[s.student_cur] = s.now_tag_same_num;
						s.chosen_num++;
                        //schedule_insert(s.student_no, d.department_no);  //�����ŵ��г̼���ѧ����
						d.student_no[pos] = s.student_no;
					} //�滻
				} //�������޿�������
			}//�г��޳�ͻ
		} //��������
		else 
		{
			s.student_cur++;
			if (s.student_cur < s.wish_count) 
			{ 
				// ������־Ը��û������ϵĻ�����������м����������
				student_que.push(s);
			}
		}
	}
}


void DistributeSystem::get_department_result(bool flag) 
{
	int count = 0;
	if (flag == true) 
	{
		//���䵽ѧ���Ĳ���
		for (int i = 0; i < department_number; ++i) 
			if (dep[i].chosen_num != 0)
			{
				count++;
				matched_department_to_json(dep[i]);
			}
		//cout << "���䵽ѧ���Ĳ��ţ�" << count << endl;
	}
	else 
	{
		//
		for (int i = 0; i < department_number; ++i) 
			if (dep[i].chosen_num == 0 && dep[i].department_member_limit != 0)
			{
				count++;
				standalone_department_to_json(dep[i]);
			}
		//cout << "δ���䵽ѧ���Ĳ��ţ�" << count << endl;
	}
}

void DistributeSystem::get_student_result(bool flag) 
{
	int count = 0;
	if (flag == true) 
	{
		//�����䵽���ŵ�ѧ��
		for (int i = 0; i < student_number; ++i) 
			if (stu[i].chosen_num != 0)
			{
				count++;
				matched_student_to_json(stu[i]);
			}
		//cout << "�����䵽���ŵ�ѧ����" << count << endl;
	}
	else 
	{
		//δ�����䵽���ŵ�ѧ��
		for (int i = 0; i < student_number; ++i) 
			if (stu[i].chosen_num == 0)
			{
				count++;
				standalone_student_to_json(stu[i]);
			}
		//cout << "δ�����䵽���ŵ�ѧ����" << count << endl;
	}
}

void DistributeSystem::schedule_delete(int student_no, int department_no)
{
	int schd_s_pos = get_student_index(student_no);
	int schd_d_pos = get_department_index(student_no);
	int sd_schedule_count = stu[schd_s_pos].schedule_count;
	int dd_schedule_count = dep[schd_d_pos].schedule_count;
	for (int schd_i = 0; schd_i < sd_schedule_count; schd_i = 0) 
	{
		for (int schd_j = 0; schd_j < dd_schedule_count; ++schd_j)
		{
			if (stu[schd_s_pos].student_schedule[schd_i] == dep[schd_d_pos].department_schedule[schd_j]) 
			{
				stu[schd_s_pos].student_schedule[schd_i] == "null";
				stu[schd_s_pos].schedule_count--;
			}
		}
	}
}