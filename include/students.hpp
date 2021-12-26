// Copyright 2021 Lonskiy Yuriy yuralon.skiy@mail.ru

#ifndef INCLUDE_STUDENTS_HPP_
#define INCLUDE_STUDENTS_HPP_
#include <iostream>
#include <fstream>
#include <any>
#include <stdexcept>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
using nlohmann::json;

struct Student {
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};

std::vector<Student> parse_file(json &data);
json get_data(const std::string &jsonPath);
void from_json(const json& j, Student& s);
void print();
void print(const Student& student, std::ostream& os);
void print(std::vector<Student>& students, std::ostream& os);
#endif // INCLUDE_STUDENTS_HPP_
