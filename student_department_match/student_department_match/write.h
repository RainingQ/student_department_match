#pragma once
#ifndef __WRITE_H_
#define __WRITE_H_
#include<iostream>
#include"json.hpp"
#include"student.h"
#include"department.h"
using namespace std;
using json = nlohmann::json;

void matched_student_to_json(const Student& student);
void standalone_student_to_json(const Student& student);
void matched_department_to_json(const Department& department);
void standalone_department_to_json(const Department& department);
void write(string file_name);

#endif
