/*#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <ctime>
#include <queue>
#include <map>

using namespace std;

struct Student {
	int student_id; // 学生编号
	int teacher_id; // 中选的导师编号
	int cur;        // 当前分配进程正在考虑第cur个志愿
	int want[5];    // 五个志愿
	float point;    // 绩点
};

struct Teacher {
	int teacher_id; // 导师编号
	int want_num;   // 期望的学生数
	int chose_num;  // 已中选的学生数
	int student_id[10]; // 中选的学生编号
};

int GetRandom(int limit) {
	return (rand()*rand()) % limit + 1;
}

class DistributeSystem {

private:
	int student_number; // 学生总人数
	int teacher_number; // 导师总人数
	Student* stu;
	Teacher* tch;

public:
	DistributeSystem() {
		stu = NULL;
		tch = NULL;
		student_number = 0;
		teacher_number = 0;
	}

	DistributeSystem(int stu_num, int tch_num) {
		student_number = stu_num;
		teacher_number = tch_num;
		stu = new Student[student_number + 5];
		tch = new Teacher[teacher_number + 5];
	}

	~DistributeSystem() {
		delete[] stu;
		delete[] tch;
	}

	// 随机生成导师信息
	void generate_teacher_information() {
		map<int, bool> id;
		for (int i = 0; i < teacher_number; ++i) {
			int teacher_id = GetRandom(99999); // 编号范围[00001, 99999]
											   // 随机出一个不重复的编号才停止
			while (id[teacher_id] == true) teacher_id = GetRandom(99999);
			id[teacher_id] = true;
			tch[i].teacher_id = teacher_id;
			tch[i].want_num = rand() % 9; // 期望学生数[0, 8]
			tch[i].chose_num = 0;
		}
	}

	void generate_student_information() {
		map<int, bool> id;
		for (int i = 0; i < student_number; ++i) {
			int student_id = GetRandom(99999);
			while (id[student_id] == true) student_id = GetRandom(99999);
			id[student_id] = true;
			stu[i].student_id = student_id;
			stu[i].teacher_id = -1; // -1表示未分配到导师
			stu[i].cur = 0; // 初始都从志愿1（下标为0）开始考虑
			stu[i].point = (rand() % 401 + 100) / 100.0; // 绩点[1.0, 5.0]
			map<int, bool> m;
			for (int j = 0; j < 5; ++j) { // 生成5个志愿
				int want = rand() % teacher_number;
				while (m[want] == true) want = rand() % teacher_number;
				m[want] = true;
				stu[i].want[j] = tch[want].teacher_id;
			}
		}
	}

	// 根据导师编号返回他在数组中的下标
	int get_teacher_index(int teacher_id) {
		int index;
		for (index = 0; index < teacher_number; ++index) {
			if (tch[index].teacher_id == teacher_id) {
				break;
			}
		}
		return index;
	}

	// 根据学生编号返回他在数组中的下标
	int get_student_index(int student_id) {
		int index;
		for (index = 0; index < student_number; ++index) {
			if (stu[index].student_id == student_id) {
				break;
			}
		}
		return index;
	}

	// 使用Gale–Shapley算法进行分配
	void distribute() {
		queue<Student> Que; //未分配到导师的学生队列
		while (!Que.empty()) Que.pop();
		for (int i = 0; i < student_number; ++i) {
			Que.push(stu[i]); // 初始都是未分配状态，都加进队列
		}
		while (!Que.empty()) {
			Student& s = stu[get_student_index(Que.front().student_id)];
			Que.pop();
			// 考虑学生s的第cur个志愿（导师为t）
			Teacher& t = tch[get_teacher_index(s.want[s.cur++])];
			if (t.want_num > t.chose_num) { // 如果导师t还有剩余名额，直接中选
				t.student_id[t.chose_num++] = s.student_id;
				s.teacher_id = t.teacher_id;
			}
			else {
				int min_stu_id = -1; // 导师t中绩点最低的学生编号
				int pos = -1; // 以及他在导师的中选列表中的下标
				float min_point = 5.0;
				for (int i = 0; i < t.chose_num; ++i) { // 在导师t中查找绩点最低的学生编号
					Student tmp = stu[get_student_index(t.student_id[i])];
					if (min_point > tmp.point) {
						min_point = tmp.point;
						min_stu_id = tmp.student_id;
						pos = i;
					}
				}
				// 如果学生s的绩点比导师t所有已经中选学生的最低绩点还低，那么学生t只好再等下轮
				if (t.want_num == 0 || min_point > s.point) {
					if (s.cur < 5) { // 如果五个志愿还没考虑完毕的话，放入队列中继续参与分配
						Que.push(s);
					}
				}
				else { // 不然学生t就直接替换掉绩点最低的那个学生
					Student& min_stu = stu[get_student_index(min_stu_id)];
					min_stu.teacher_id = -1;
					if (min_stu.cur < 5) { // 被替换掉的学生再放入未分配的队列中去
						Que.push(min_stu);
					}
					t.student_id[pos] = s.student_id;
					s.teacher_id = t.teacher_id;
				}
			}
		}
	}

	pair<double, double> get_student_analysis() {
		double avg_choice = 0;
		int count = 0;
		for (int i = 0; i < student_number; ++i) {
			int choice = -1;
			if (stu[i].teacher_id != -1) {
				for (int j = 0; j < 5; ++j) {
					if (stu[i].want[j] == stu[i].teacher_id) {
						choice = j + 1;
						break;
					}
				}
				avg_choice += choice;
			}
			else count++;
		}
		avg_choice /= (student_number - count);
		return make_pair(avg_choice, count * 1.0 / student_number * 100.0);
	}
};

int main() {

	// freopen("input.txt", "r", stdin);
	// freopen("result.txt", "w", stdout);

	srand(time(NULL));

	int T;
	cin >> T; // 测试组数

	double student_choice_best = 5;     // 最好情况下的学生平均中选志愿顺序
	double student_choice_worst = 1;    // 最坏情况下的学生平均中选志愿顺序

	double student_avg_best = 100.0;    // 最好情况下的学生未分配率
	double student_avg_worst = 0.0;     // 最坏情况下的学生未分配率

	double tot_stu_avg = 0;             // 平均学生未分配率
	double tot_choice_avg = 0;          // 平均中选志愿顺序

	for (int i = 0; i < T; ++i) {
		int student_number, teacher_number;
		cin >> student_number >> teacher_number;
		DistributeSystem ds(student_number, teacher_number);
		ds.generate_teacher_information();
		ds.generate_student_information();
		ds.distribute();

		pair<double, double> pdd = ds.get_student_analysis();
		if (pdd.first < student_choice_best) student_choice_best = pdd.first;
		if (pdd.first > student_choice_worst) student_choice_worst = pdd.first;
		tot_choice_avg += pdd.first;

		if (pdd.second < student_avg_best) student_avg_best = pdd.second;
		if (pdd.second > student_avg_worst) student_avg_worst = pdd.second;
		tot_stu_avg += pdd.second;

	}

	cout << "学生未分配率：" << endl;
	cout << "最好：" << student_avg_best << " 最坏：" << student_avg_best << " 平均：" << tot_stu_avg / T << endl;
	cout << "学生志愿顺序：" << endl;
	cout << "最好：" << student_choice_best << " 最坏：" << student_choice_worst << " 平均：" << tot_choice_avg / T << endl;

	return 0;
}*/