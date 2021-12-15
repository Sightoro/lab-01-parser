#include <students.hpp>

int main() {
  const std::string &path = "/Users/itsumaden/C++/PartyOne/lab-01-parser/tests/students.json";
  nlohmann::json data = get_data(path);
  std::vector<Student> students = parse_file(data);
  print(students, std::cout);
}