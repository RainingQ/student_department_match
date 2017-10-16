#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<string.h>
#include<vector>
#include<strstream>
#include<ostream>
#include<fstream>
#include"json.hpp"
using namespace std;
using json = nlohmann::json;

#define random(x) rand()%x

int student_count = 10000;
int department_count = 1000;

struct Student {
	int student_no;
	float student_score;
	string student_name;
	string student_tag[10];
	string student_schedule[50];
	int tag_count;
	int schedule_count;
	int wish_count;
	int student_wish[5];
	int department_no[5];
	int student_cur;
};

struct Department {
	int department_no;
	int student_no[15];
	int department_member_limit;
	float department_score_limit;
	string department_name;
	string department_tag[10];
	string departmen_schedule[10];
	int tag_count;
	int schedule_count;
	int chosen_num;
};

string tagku[50] = {
	"dancing", "movie", "music", "sport", "drama",
	"trditional_opera", "traveling", "hiking", "swimming", "runing",
	"chess", "chatting", "jazz", "hip-hop", "reading",
	"basketball", "football", "pingpong", "bassball", "tennis",
	"speech", "discuss", "language", "debating", "studying",
	"English", "Chinese", "German", "Japanese", "Kerean",
	"French", "Russian", "Italian", "Spanish", "Portuguese",
	"Arena-of-Valor", "LOL", "WOW", "DOTA", "Hearthstone",
	"Monument-Valley", "The-room", "Back-to-bed", "Machinarium", "LIMBO",
	"Hatsune-Miku", "Luo-Tianyi", "KAITO", "MEIKO", "Kagamine-Rin" };
string scheduleku[25] = {
	"Monday_am", "Monday_pm",
	"Tuesday_am", "Tuesday_pm",
	"Wednesday_am", "Wednesday_pm",
	"Thursday_am", "Thursday_pm",
	"Friday_am", "Friday_pm",
	"Saturday_am", "Saturday_pm",
	"Sunday_am", "Sunday_pm" };
vector<string> schedule;
vector<int> wishku;
int wishku_size = 0;
vector<int> tmp;
stringstream ss;

/*随机生成一个学生的信息*/
void initStudent(Student& stu)
{
	//学号
	stu.student_no = ++student_count;

	//学生姓名
	stu.student_name = "student_" + to_string(student_count);

	//学生绩点[2.0, 5)
	stu.student_score = (rand() % 300 + 200) / 100.0;

	//学生标签
	int i = 0;
	int rng = 0;
	stu.tag_count = random(10) + 1;
	while (i < stu.tag_count)
	{
		rng = random(5);
		stu.student_tag[i] = tagku[i * 5 + rng];
		i++;
	}

	//部门志愿
	stu.wish_count = random(5) + 1;	//部门志愿不能为空
	if (wishku_size < stu.wish_count)
		stu.wish_count = wishku_size;
	tmp.clear();
	int size = wishku_size;
	for (int i = 0; i < size; i++)
		tmp.push_back(wishku[i]);
	i = 0;
	while (i < stu.wish_count)
	{
		rng = random(size--);
		stu.student_wish[i++] = tmp[rng];
		tmp.erase(tmp.begin() + rng);
	}

	//学生行程（没空时间)
	stu.schedule_count = random(10) + 1;
	schedule.clear();
	for (i = 0; i < 14; i++)
		schedule.push_back(scheduleku[i]);
	i = 0;
	while (i < stu.schedule_count && schedule.size() != 0)
	{
		rng = random(schedule.size());
		stu.student_schedule[i] = schedule[rng];
		schedule.erase(schedule.begin() + rng);
		i++;
	}
}

/*随机生成一个部门的信息*/
void initDepartment(Department& dep)
{
	//部门编号
	dep.department_no = ++department_count;
	wishku.push_back(department_count);
	wishku_size++;

	//部门名称
	dep.department_name = "department_" + to_string(department_count);

	//部门纳新人数上限[0, 15]
	dep.department_member_limit = random(16);

	//部门最低绩点要求[1.0,3.0)
	dep.department_score_limit = (rand() % 200 + 100) / 100.0;

	//部门标签
	int i = 0;
	int rng = 0;
	dep.tag_count = random(10) + 1;
	while (i < dep.tag_count)
	{
		rng = random(5);
		dep.department_tag[i] = tagku[i * 5 + rng];
		i++;
	}

	//部门常规活动时间
	dep.schedule_count = random(10) + 1;
	for (i = 0; i < 14; i++)
		schedule.push_back(scheduleku[i]);
	i = 0;
	while (i < dep.schedule_count && schedule.size() != 0)
	{
		rng = random(schedule.size());
		dep.departmen_schedule[i] = schedule[rng];
		schedule.erase(schedule.begin() + rng);
		i++;
	}
}

/*将学生数据生成json*/
void student_to_json(json& j, const Student& stu)
{
	j = json{
		{ "student_no", stu.student_no },
		{ "student_score", stu.student_score },
		{ "student_cur", -1 },
		{ "student_name", stu.student_name },
		{ "schedule_count", stu.schedule_count },
		{ "tag_count", stu.tag_count },
		{ "wish_count", stu.wish_count }
	};
	for (int i = 0; i < stu.wish_count; i++)
		j["student_wish"].push_back(stu.student_wish[i]);
	for (int i = 0; i < stu.schedule_count; i++)
		j["student_schedule"].push_back(stu.student_schedule[i]);
	for (int i = 0; i < stu.tag_count; i++)
		j["student_tag"].push_back(stu.student_tag[i]);
}

/*将部门数据生成json*/
void department_to_json(json& j, Department& dep)
{
	j = json{
		{ "department_no", dep.department_no },
		{ "department_member_limit", dep.department_member_limit },
		{ "department_score_limit", dep.department_score_limit },
		{ "chosen_num", 0 },
		{ "department_name", dep.department_name },
		{ "schedule_count", dep.schedule_count },
		{ "tag_count", dep.tag_count }
	};
	/*for (int i = 0; dep.department_name[i] != '\0'; i++)
	j["department_name"].push_back(dep.department_name[i]);*/
	for (int i = 0; i < dep.schedule_count; i++)
		j["department_schedule"].push_back(dep.departmen_schedule[i]);
	for (int i = 0; i < dep.tag_count; i++)
		j["department_tag"].push_back(dep.department_tag[i]);
}

int main()
{
	srand(time(0));

	int student_num = 0;
	int department_num = 0;
	int i = 0;
	json j;
	json jset;
	ofstream json_output("s1000-d50-in.json");//每次生成需手动更改

	Student student;
	Department department;

	cin >> student_num >> department_num;

	while (department_num--)
	{
		initDepartment(department);
		department_to_json(j, department);
		jset["department"].push_back(j);
		//cout << setw(4) << j << endl;
	}

	while (student_num--)
	{
		initStudent(student);
		student_to_json(j, student);
		jset["student"].push_back(j);
	}
	json_output << setw(4) << jset << endl;
	//cout << setw(4) << jset << endl;

	return 0;
}