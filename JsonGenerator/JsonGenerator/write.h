#pragma once
#ifndef __WRITE_H_
#define __WRITE_H_
#include<iostream>
#include"json.hpp"
using namespace std;
using json = nlohmann::json;

void matched_student_to_json(json& j, const Student& student);
void standalone_student_to_json(json& j, const Student& student);
void matched_department_to_json(json& j, const Department& department);
void standalone_department_to_json(json& j, const Department& department);

#endif // !__WRITE_H_
