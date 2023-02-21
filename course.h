#ifndef COURSE_H
#define COURSE_H

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// forward declaration
class Student;

class Course {
  friend class Student;
  friend class University;
  friend class EnrollmentSystem;
  friend ostream &operator<<(ostream &out, const Course &course);
  friend class cmpLastName;

public:
  // constructor
  Course(string number, string name);

private:
  // variables

  // stores the course number
  string courseNumber;

  // stores the course name
  string courseName;

  // stores the list of enrolled students
  unordered_map<int, Student *> enrolled_Students;

  // Functions

  Course(); // no input not allowed

  // add a student to the enrolled studnets list
  // return true if added successfully
  bool addStudent(Student *student);

  // remove student from the enrolled students list
  // return true if removed successfully
  bool removeStudent(Student *student);

  // Return class list sorted by last name of students
  string getClassListByLastName() const; // no inputs

  // Return class list sorted by students ID
  string getClassListByID() const; // no inputs
};

#endif