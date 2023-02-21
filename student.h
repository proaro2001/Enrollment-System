#ifndef STUDENT_H
#define STUDENT_H

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// forward declaration
class Course;

class Student {
  friend class Course;
  friend class University;
  friend class EnrollmentSystem;
  friend ostream &operator<<(ostream &out, const Student &student);

public:
  // constructor
  Student(int studentID, string firstName, string lastName);

private:
  // constructor
  Student(); // no input not allowed

  // variables

  // stores the student's ID
  int studentID;

  // stores the student's first name
  string firstName;

  // stores the student's last name
  string lastName;

  // stores the pointers of the course that student enrolled
  //  unordered_map<courseNum, course> enrolled
  unordered_map<string, Course *> enrolled;

  // functions

  // drop course from the course list
  // return true if removed successfully
  bool dropCourse(Course *course);

  // add course to the course list
  // return true if add successfully
  bool addCourse(Course *course);

  // detect whether the student is in specific course
  // return true if the student still in the specific course
  bool isInCourse(Course *course) const;
};

#endif