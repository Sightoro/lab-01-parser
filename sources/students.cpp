// Copyright 2021 Lonskiy Yuriy yuralon.skiy@mail.ru


#include <students.hpp>

json get_data(const std::string& jsonPath){
  std::ifstream file(jsonPath);
  json data;
  file >> data;
  if (jsonPath.empty())
    throw std::runtime_error("File's path is empty");
  if (!file)
    throw std::runtime_error("File does not exist");
  if (!data.at("items").is_array())
    throw std::runtime_error("Items in file should be arrays");
  if (data.at("items").size() != data.at("_meta").at("count").get<size_t>())
    throw std::runtime_error("Count of items is incorrect");
  return data;
}


auto get_name(const json& j) -> std::string {
  return j.get<std::string>();
}

auto get_debt(const json& j) -> std::any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<std::vector<std::string>>();
}

auto get_avg(const json& j) -> std::any {
  if (j.is_null())
    return nullptr;
  else if (j.is_string())
    return j.get<std::string>();
  else if (j.is_number_float())
    return j.get<double>();
  else
    return j.get<std::size_t>();
}

auto get_group(const json& j) -> std::any {
  if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<std::size_t>();
}
void from_json(const json& j, Student & s) {
  s.name = get_name(j.at("name"));
  s.group = get_group(j.at("group"));
  s.avg = get_avg(j.at("avg"));
  s.debt = get_debt(j.at("debt"));
}

std::vector<Student> parse_file(json &data){
  std::vector<Student> students;
  for (auto const& item : data.at("items")) {
    Student student;
    from_json(item, student);
    students.push_back(student);
  }
  return students;
}

void print(){
  std::cout << "|" << " name" << std::setfill(' ') << std::setw(20)
            << "|" << " group" << std::setw(4)
            << "|" << " avg" << std::setw(6) << "|" << " debt"
            << std::setw(5) << "|" << std::endl
            << "|" << std::setfill('-') << std::setw(25)
            << "|" << std::setw(10)
            << "|" << std::setw(10) << "|" << std::setw(10) << "|" << std::endl;
}

void print(const Student& student, std::ostream& os){
  os << "|" << std::setfill(' ') << std::setw(24)
     << std::left << std::any_cast<std::string>(student.name)
     << std::right << "|";
  if (student.group.type() == typeid(std::string))
    os << std::setw(9) << std::left << std::any_cast<std::string>(student.group)
       << std::right << "|";
  else
    os << std::setw(9) << std::left <<  std::any_cast<size_t>(student.group)
       << "|";
  if ( student.avg.type() == typeid(std::string) )
    os << std::setw(9) << std::left
       << std::any_cast<std::string>(student.avg) << "|";
  else if (student.avg.type() == typeid(double))
    os << std::setw(9) << std::left << std::any_cast<double>(student.avg)
       << "|";
  else if (student.avg.type() == typeid(std::size_t))
    os << std::setw(9) << std:: left << std::any_cast<size_t>(student.avg)
       << "|";
  if (student.debt.type() == typeid(std::nullptr_t))
    os << std::setw(9) << std::left << "null" << "|" << std::endl;
  else if (student.debt.type() == typeid(std::string))
    os << std::setw(9) << std::left << std::any_cast<std::string>(student.debt)
       << "|" << std::endl;
  else  os << std::setw(1) << std::left
       << std::any_cast<std::vector<std::string>>(student.debt).size()
       << std::setw(8) << std::left
       << " items" << std::right << "|" << std::endl;

  os << std::right << "|" << std::setfill('-')
     << std::setw(25) << "|" << std::setw(10)
     << "|" << std::setw(10) << "|" << std::setw(10) << "|" << std::endl;
}
void print(std::vector<Student> &students, std::ostream &os) {
  print();
  for (Student &student : students){
    print(student, os);
  }
}
