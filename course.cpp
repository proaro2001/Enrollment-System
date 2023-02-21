#include "course.h"
#include "student.h"
#include <algorithm>
#include <cassert>
#include <sstream>

using namespace std;

ostream &operator<<(ostream &out, const Course &course) {
  out << course.courseNumber << " " << course.courseName << endl;
  return out;
}
// Functions

// constructor
Course::Course(string number, string name)
    : courseNumber(number), courseName(name) {}

// add a student to the enrolled studnets list
// return true if added successfully
bool Course::addStudent(Student *student) {
  enrolled_Students.insert({student->studentID, student});
  return enrolled_Students.count(student->studentID) == 1;
}

// remove student from the enrolled students list
// return true if removed successfully
bool Course::removeStudent(Student *student) {
  if (enrolled_Students.count(student->studentID) == 0) {
    return false;
  }
  // delete enrolled_Students[student->studentID];
  enrolled_Students.erase(student->studentID);
  return enrolled_Students.count(student->studentID) == 0;
}

// Return class list sorted by last name of students
string Course::getClassListByLastName() const {
  string retMe;
  vector<string> lastNames;
  for (auto elem : enrolled_Students) {
    lastNames.push_back(elem.second->lastName + ", " + elem.second->firstName +
                        " (" + to_string(elem.second->studentID) + ")");
  }
  sort(lastNames.begin(), lastNames.end());
  retMe.append("[");
  if (lastNames.size() > 1) {
    for (int i = 0; i < lastNames.size() - 1; i++) {
      retMe.append(lastNames[i] + ", ");
    }
    if (!lastNames.empty()) {
      retMe.append(lastNames[lastNames.size() - 1]);
    }
  }

  if (!lastNames.empty()) {
    retMe.append("]");
  }
  return retMe;
}

// Return class list sorted by students ID
string Course::getClassListByID() const {
  vector<int> idList;
  for (auto ids : enrolled_Students) {
    idList.push_back(ids.first);
  }
  sort(idList.begin(), idList.end());

  string retMe = "[";
  for (int ids : idList) {
    retMe.append(enrolled_Students.at(ids)->lastName + ", " +
                 enrolled_Students.at(ids)->firstName + " (" +
                 to_string(enrolled_Students.at(ids)->studentID) + ")");
    if (ids != idList.back()) {
      retMe.append(", ");
    }
  }
  retMe.append("]");
  // cout << retMe<<endl;
  return retMe;
}
