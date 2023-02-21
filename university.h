#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include "course.h"
#include "student.h"
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

class University {
  friend class EnrollmentSystem;

public:
  // constructor
  explicit University(string universityName);
  // destructor
  // delete all the memory at the end
  ~University();

private:
  // constructor
  University(); // no input not allowed

  // variables

  // store the name of the university
  string universityName;

  // store the list of student who study in the university
  unordered_map<int, Student *> studentsList;

  // store the course that can be registered
  unordered_map<string, Course *> courseList;

  // functions

  // Read the student list for current active university
  // return true if file successfully read
  bool readStudentList(const string &filename);

  // Read the course list for current active university
  // return true if file successfully read
  bool readCourseList(const string &filename);

  // Read the student enrollment information for current active university
  // return true if file successfully read
  bool readEnrollmentInfo(const string &filename);

  // Return the courses student is enrolled in
  // The returned courses are separated by commas and sorted by course name
  string getEnrolledCourses(int studentID) const;

  // Return the title for the course
  string getCourseTitle(const string &courseNumber);

  // helper function to add student to studentlist
  // add student to the list
  // if students shares the same number, we will ignore them
  bool addStudentToList(int studentNumber, string studentFirstName,
                        string studentLastName);

  // helper function to add course to courselist
  // add course to the courselist
  bool addCourseToList(string courseNumber, string courseName);

  // helper function that add course for student, and add student for course
  void enrollStudentToCourse(int studentID, const string &courseNumber);
};

#endif