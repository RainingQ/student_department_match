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
	int student_id; // ѧ�����
	int teacher_id; // ��ѡ�ĵ�ʦ���
	int cur;        // ��ǰ����������ڿ��ǵ�cur��־Ը
	int want[5];    // ���־Ը
	float point;    // ����
};

struct Teacher {
	int teacher_id; // ��ʦ���
	int want_num;   // ������ѧ����
	int chose_num;  // ����ѡ��ѧ����
	int student_id[10]; // ��ѡ��ѧ�����
};

int GetRandom(int limit) {
	return (rand()*rand()) % limit + 1;
}

class DistributeSystem {

private:
	int student_number; // ѧ��������
	int teacher_number; // ��ʦ������
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

	// ������ɵ�ʦ��Ϣ
	void generate_teacher_information() {
		map<int, bool> id;
		for (int i = 0; i < teacher_number; ++i) {
			int teacher_id = GetRandom(99999); // ��ŷ�Χ[00001, 99999]
											   // �����һ�����ظ��ı�Ų�ֹͣ
			while (id[teacher_id] == true) teacher_id = GetRandom(99999);
			id[teacher_id] = true;
			tch[i].teacher_id = teacher_id;
			tch[i].want_num = rand() % 9; // ����ѧ����[0, 8]
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
			stu[i].teacher_id = -1; // -1��ʾδ���䵽��ʦ
			stu[i].cur = 0; // ��ʼ����־Ը1���±�Ϊ0����ʼ����
			stu[i].point = (rand() % 401 + 100) / 100.0; // ����[1.0, 5.0]
			map<int, bool> m;
			for (int j = 0; j < 5; ++j) { // ����5��־Ը
				int want = rand() % teacher_number;
				while (m[want] == true) want = rand() % teacher_number;
				m[want] = true;
				stu[i].want[j] = tch[want].teacher_id;
			}
		}
	}

	// ���ݵ�ʦ��ŷ������������е��±�
	int get_teacher_index(int teacher_id) {
		int index;
		for (index = 0; index < teacher_number; ++index) {
			if (tch[index].teacher_id == teacher_id) {
				break;
			}
		}
		return index;
	}

	// ����ѧ����ŷ������������е��±�
	int get_student_index(int student_id) {
		int index;
		for (index = 0; index < student_number; ++index) {
			if (stu[index].student_id == student_id) {
				break;
			}
		}
		return index;
	}

	// ʹ��Gale�CShapley�㷨���з���
	void distribute() {
		queue<Student> Que; //δ���䵽��ʦ��ѧ������
		while (!Que.empty()) Que.pop();
		for (int i = 0; i < student_number; ++i) {
			Que.push(stu[i]); // ��ʼ����δ����״̬�����ӽ�����
		}
		while (!Que.empty()) {
			Student& s = stu[get_student_index(Que.front().student_id)];
			Que.pop();
			// ����ѧ��s�ĵ�cur��־Ը����ʦΪt��
			Teacher& t = tch[get_teacher_index(s.want[s.cur++])];
			if (t.want_num > t.chose_num) { // �����ʦt����ʣ�����ֱ����ѡ
				t.student_id[t.chose_num++] = s.student_id;
				s.teacher_id = t.teacher_id;
			}
			else {
				int min_stu_id = -1; // ��ʦt�м�����͵�ѧ�����
				int pos = -1; // �Լ����ڵ�ʦ����ѡ�б��е��±�
				float min_point = 5.0;
				for (int i = 0; i < t.chose_num; ++i) { // �ڵ�ʦt�в��Ҽ�����͵�ѧ�����
					Student tmp = stu[get_student_index(t.student_id[i])];
					if (min_point > tmp.point) {
						min_point = tmp.point;
						min_stu_id = tmp.student_id;
						pos = i;
					}
				}
				// ���ѧ��s�ļ���ȵ�ʦt�����Ѿ���ѡѧ������ͼ��㻹�ͣ���ôѧ��tֻ���ٵ�����
				if (t.want_num == 0 || min_point > s.point) {
					if (s.cur < 5) { // ������־Ը��û������ϵĻ�����������м����������
						Que.push(s);
					}
				}
				else { // ��Ȼѧ��t��ֱ���滻��������͵��Ǹ�ѧ��
					Student& min_stu = stu[get_student_index(min_stu_id)];
					min_stu.teacher_id = -1;
					if (min_stu.cur < 5) { // ���滻����ѧ���ٷ���δ����Ķ�����ȥ
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
	cin >> T; // ��������

	double student_choice_best = 5;     // �������µ�ѧ��ƽ����ѡ־Ը˳��
	double student_choice_worst = 1;    // �����µ�ѧ��ƽ����ѡ־Ը˳��

	double student_avg_best = 100.0;    // �������µ�ѧ��δ������
	double student_avg_worst = 0.0;     // �����µ�ѧ��δ������

	double tot_stu_avg = 0;             // ƽ��ѧ��δ������
	double tot_choice_avg = 0;          // ƽ����ѡ־Ը˳��

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

	cout << "ѧ��δ�����ʣ�" << endl;
	cout << "��ã�" << student_avg_best << " ���" << student_avg_best << " ƽ����" << tot_stu_avg / T << endl;
	cout << "ѧ��־Ը˳��" << endl;
	cout << "��ã�" << student_choice_best << " ���" << student_choice_worst << " ƽ����" << tot_choice_avg / T << endl;

	return 0;
}*/