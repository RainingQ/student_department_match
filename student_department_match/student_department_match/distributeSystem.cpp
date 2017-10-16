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
	stu = new Student[student_number];        //开辟一个大小为student_number的Student型数据的空间，把地址赋给stu
	dep = new Department[department_number];   //开辟一个大小为department_number的Department型数据的空间，把地址赋给dep
}

DistributeSystem::~DistributeSystem()
{
	delete[] stu;     //撤销该空间
	delete[] dep;
}

/*初始化部门信息*/
void DistributeSystem::generate_department_information()
{
	for (int i = 0; i < department_number; ++i)
	{
		dep[i].chosen_num = 0; //0表示未分配到学生
		for (int j = 0; j < dep[i].department_member_limit; ++j)
			dep[i].student_no[j] = 0;//初始化数组
	}
}

/*初始化学生信息*/
void DistributeSystem::generate_student_information()
{
	for (int i = 0; i < student_number; ++i)
	{
		stu[i].chosen_num = 0; // 0表示未分配到部门
		stu[i].student_cur = 0; // 初始都从志愿1（下标为0）开始考虑
		stu[i].now_tag_same_num = 0; //初始化当前部门标签类似数
		for (int k = 0; k < stu[i].wish_count; ++k)
		{
			stu[i].department_no[k] = 0;  //初始化数组department_no[5]
			stu[i].tag_same_num[k] = -1;  //初始化数组tab_same_num[5]
		}
	}
}

/*根据部门编号返回他在<部门数组>中的下标*/
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

/*根据学号返回他在<学生数组>中的下标*/
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

/*根据学生所在数组的下标、学生已中选部门数、部门编号返回部门在<学生i已中选部门数组>中的下标*/
int DistributeSystem::get_stu_department_index(int i, int chosen_num, int department_no)
{
	int index;
	for (index = 0; index < chosen_num; ++index)
		if (stu[i].department_no[index] == department_no)
			break;
	return index;
}

/*根据学号和部门编号返回学生与当前所考虑的部门的标签类似数*/
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

//将部门的行程加入已中选学生的行程
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

/*根据分配原则进行学生-部门分配*/
void DistributeSystem::distribute() 
{
	queue<Student> student_que; //待分配的学生队列
	for (int i = 0; i < student_number; ++i) 
		student_que.push(stu[i]); // 初始都是未分配状态，都加进队列
	while (!student_que.empty()) 
	{
		int ss = student_que.front().student_no;
		int sss = get_student_index(ss);
		Student& s = stu[sss];   //访问学生队列队首元素
		student_que.pop();

		// 第一步考虑学生s的第student_cur个志愿（部门为d）
		int ww = s.student_cur;
		int www = s.student_wish[ww];
		int wwww = get_department_index(www);
		Department& d = dep[wwww];   //访问部门队列队首元素

		if (s.student_score >= d.department_score_limit)
		{
			//第二步考虑学生与部门时间是否有冲突
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
					// 如果五个志愿还没考虑完毕的话，放入队列中继续参与分配
					student_que.push(s);
				}
			}
			else  
			{
				//若时间无冲突
				//第三步考虑部门是否已收满
				if (d.department_member_limit > d.chosen_num)
				{
					// 如果部门d还有剩余名额，直接中选
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
						// 如果五个志愿还没考虑完毕的话，放入队列中继续参与分配
						student_que.push(s);
					}					
				}//未收満
				//若已收满，第四步考虑标签类似数
				//先找到部门d<已中选学生中>标签类似数最少的学生s'
				//将学生s的标签类似数和s’最少标签数的进行对比
				else    
				{
					//若部门无空余名额
					int least_stu_no = -1; // 部门d<已中选学生中>标签类似数最少的学生s’编号
					int pos = -1; // 以及s'在部门的<已中选列表中>的下标
					int stu_pos = -1; //s'在<学生数组>中的下标
					int less_stu_dep_pos = -1; //部门d在s'的<已中选部门数组>中的下标
					int least_tag_same_num = 10;         //最少的标签类似数  
														 //float min_point = 5.0;
					s.now_tag_same_num = get_student_now_tag_same_num(s.student_no, d.department_no);  //学生s与部门d的标签类似数
					for (int i = 0; i < d.chosen_num; ++i)
					{ 
						// 在部门d中查找标签类似数最少的学生编号
						stu_pos = get_student_index(d.student_no[i]);     //部门已中选学生在<学生>数组的下标
						Student dmp = stu[stu_pos];  //对应的已中选学生
						less_stu_dep_pos = get_stu_department_index(stu_pos, dmp.chosen_num, d.department_no);
						if (least_tag_same_num > dmp.tag_same_num[less_stu_dep_pos])
						{
							least_tag_same_num = dmp.tag_same_num[less_stu_dep_pos];
							least_stu_no = dmp.student_no;
							pos = i;
						}
					}
					//再判断纳新人数是否为0 以及 学生s的标签类似数和最少标签类似数less_tag_same_num的大小关系
					//若纳新人数为0 或者 学生s的标签类似数<=最少标签类似数less_tag_same_num ,考虑学生s的下一个志愿
					if (d.department_member_limit == 0 || s.now_tag_same_num <= least_tag_same_num)
					{
						s.student_cur++;
						if (s.student_cur < s.wish_count)
						{ 
							// 如果五个志愿还没考虑完毕的话，放入队列中继续参与分配
							student_que.push(s);
						}
					}
					else
					{
						// 不然学生s就直接替换掉标签类似数最少的那个学生
						int least_stu_index = get_student_index(least_stu_no);  //被替换掉的学生s.在<学生数组>中的下标
						Student& least_stu = stu[least_stu_index];
						int least_stu_department_index = get_stu_department_index(least_stu_index, least_stu.chosen_num, d.department_no); //部门d在被替换掉的学生s.<已中选部门数组>中的下标
						least_stu.department_no[least_stu_department_index] = -1;  //被替换掉的学生该部门队列
						//此时学生s已中选，保存中选信息
						s.department_no[s.student_cur] = d.department_no;
						s.tag_same_num[s.student_cur] = s.now_tag_same_num;
						s.chosen_num++;
                        //schedule_insert(s.student_no, d.department_no);  //将部门的行程加入学生中
						d.student_no[pos] = s.student_no;
					} //替换
				} //若部门无空余名额
			}//行程无冲突
		} //绩点满足
		else 
		{
			s.student_cur++;
			if (s.student_cur < s.wish_count) 
			{ 
				// 如果五个志愿还没考虑完毕的话，放入队列中继续参与分配
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
		//分配到学生的部门
		for (int i = 0; i < department_number; ++i) 
			if (dep[i].chosen_num != 0)
			{
				count++;
				matched_department_to_json(dep[i]);
			}
		//cout << "分配到学生的部门：" << count << endl;
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
		//cout << "未分配到学生的部门：" << count << endl;
	}
}

void DistributeSystem::get_student_result(bool flag) 
{
	int count = 0;
	if (flag == true) 
	{
		//被分配到部门的学生
		for (int i = 0; i < student_number; ++i) 
			if (stu[i].chosen_num != 0)
			{
				count++;
				matched_student_to_json(stu[i]);
			}
		//cout << "被分配到部门的学生：" << count << endl;
	}
	else 
	{
		//未被分配到部门的学生
		for (int i = 0; i < student_number; ++i) 
			if (stu[i].chosen_num == 0)
			{
				count++;
				standalone_student_to_json(stu[i]);
			}
		//cout << "未被分配到部门的学生：" << count << endl;
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