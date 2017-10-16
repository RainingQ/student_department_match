#pragma once
#ifndef __READ_H_
#define __READ_H_
#include<iostream>
#include<string>
#include"student.h"
#include"department.h"
#include"json.hpp"
using namespace std;
using json = nlohmann::json;

Student student[5000];
Department department[100];
int i = 0;

void student_from_json(const json& j);
void department_from_json(const json& j);

#endif