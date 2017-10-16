#pragma once
#ifndef __READ_H_
#define __READ_H_
#include <iostream>
#include <string>
#include "student.h"
#include "department.h"
#include "json.hpp"
#include "distributeSystem.h"
using namespace std;
using json = nlohmann::json;

void student_from_json(const json& j, Student& student);
void department_from_json(const json& j, Department& department);
void read(string file_name, DistributeSystem& ds);

#endif