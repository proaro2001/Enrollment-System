#include "student.h"
#include "course.h"
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

ostream &operator<<(ostream &out, const Student &student) {
  out << student.studentID << " " << student.firstName << " "
      << student.lastName << endl;
  return out;
}

// constructor
Student::Student(int studentID, string firstName, string lastName)
    : studentID(studentID), firstName(firstName), lastName(lastName) {}

// functions

// drop course from the course list
// return true if removed successfully
bool Student::dropCourse(Course *course) {
  if (!isInCourse(course)) {
    return false;
  }
  // delete enrolled[course->courseName];
  enrolled.erase(course->courseName);
  return !isInCourse(course);
}

// add course to the course list
// return true if add successfully
bool Student::addCourse(Course *course) {
  enrolled.insert({course->courseName, course});
  return isInCourse(course);
}

// detect whether the student is in specific course
// return true if the student still in the specific course
bool Student::isInCourse(Course *course) const {
  // check whether the container "enrolled" has contained the course
  return enrolled.count(course->courseName) == 1 &&
         enrolled.at(course->courseName) == course;
}
