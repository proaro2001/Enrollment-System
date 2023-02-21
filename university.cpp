#include "university.h"
#include "student.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

// constructor
University::University(string universityName)
    : universityName(universityName) {}

// functions

// Read the student list for current active university
// return true if file successfully read
bool University::readStudentList(const string &filename) {
  ifstream inFile;
  inFile.open(filename);
  if (inFile.fail()) {
    return false;
  }
  int studentNumber = 0;
  string studentFirstName;
  string studentLastName;
  while (inFile >> studentNumber >> studentFirstName >> studentLastName) {
    addStudentToList(studentNumber, studentFirstName, studentLastName);
  }
  inFile.close();
  return true;
}

// Read the course list for current active university
// return true if file successfully read
bool University::readCourseList(const string &filename) {
  ifstream inFile;
  inFile.open(filename);
  if (inFile.fail()) {
    return false;
  }
  string courseNumber;
  string courseName;
  while (inFile >> courseNumber && getline(inFile, courseName)) {
    addCourseToList(courseNumber, courseName.substr(1, courseName.size() - 1));
  }
  inFile.close();
  return true;
}

// Read the student enrollment information for current active university
// return true if file successfully read
bool University::readEnrollmentInfo(const string &filename) {
  ifstream inFile;
  inFile.open(filename);
  if (inFile.fail()) {
    return false;
  }
  int studentNumber = 0;
  string courseNumber;
  while (inFile >> studentNumber >> courseNumber) {
    if (studentsList.count(studentNumber) == 0) {
      cout << "student " << studentNumber << " doesn't exist" << endl;
      continue;
    }
    if (courseList.count(courseNumber) == 0) {
      cout << "course " << courseNumber << " doesn't exist" << endl;
      continue;
    }
    enrollStudentToCourse(studentNumber, courseNumber);
  }
  inFile.close();
  return true;
}

// helper function that add course for student, and add student for course
void University::enrollStudentToCourse(int studentID,
                                       const string &courseNumber) {
  Student *studentPtr = studentsList[studentID];
  Course *coursePtr = courseList[courseNumber];
  studentPtr->addCourse(coursePtr);
  coursePtr->addStudent(studentPtr);
}

// helper function to add student to studentlist
// add student to the list
// if students shares the same number, we will ignore them
bool University::addStudentToList(int studentNumber, string studentFirstName,
                                  string studentLastName) {
  if (studentsList.count(studentNumber) == 1) {
    return false;
  }
  studentsList.insert(
      {studentNumber,
       new Student(studentNumber, studentFirstName, studentLastName)});
  return studentsList.count(studentNumber) == 1;
}

// helper function to add course to courselist for avoiding memory leak
// add course to the courselist
bool University::addCourseToList(string courseNumber, string courseName) {
  if (courseList.count(courseNumber) == 1) {
    return false;
  }
  courseList.insert({courseNumber, new Course(courseNumber, courseName)});
  return courseList.count(courseNumber) == 1;
}

// Return the title for the course
string University::getCourseTitle(const string &courseNumber) {
  return courseList[courseNumber]->courseName;
}

// destructor
// delete all the memory at the end
University::~University() {
  for (auto course : courseList) {
    delete course.second;
  }
  for (auto student : studentsList) {
    delete student.second;
  }
}

// Return the courses student is enrolled in
// The returned courses are separated by commas and sorted by course name
string University::getEnrolledCourses(int studentID) const {
  string retMe = "[";

  vector<string> courselist;
  for (auto course : studentsList.at(studentID)->enrolled) {
    courselist.push_back(course.second->courseNumber);
  }
  sort(courselist.begin(), courselist.end());
  for (string course : courselist) {
    retMe.append(course);
    if (course != courselist.back()) {
      retMe.append(", ");
    }
  }
  retMe.append("]");
  // cout<< retMe << endl;
  return retMe;
}