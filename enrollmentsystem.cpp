#include "enrollmentsystem.h"
#include "university.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

using namespace std;

EnrollmentSystem::~EnrollmentSystem() {
  for (auto university : universities) {
    delete university.second;
  }
}

// Add university to the enrollments system
bool EnrollmentSystem::addUniversity(const string &name) {
  // if already exist, repeat the same university is not allow
  if (universities.count(name) == 1) {
    return false;
  }
  universities.insert({name, new University(name)});
  return universities.count(name) == 1;
}

// Set this university as the active university for other functions
bool EnrollmentSystem::setCurrentUniversity(const string &name) {
  // if the name doesn't exist, reject setting current university
  if (universities.count(name) == 0) {
    return false;
  }
  currentUniversity = universities[name];
  return currentUniversity->universityName == name; // how do we check this?
}

// Return the current active university name
string EnrollmentSystem::getUniversityName() const {
  return currentUniversity->universityName;
}

// Read the student list for current active university
// return true if file successfully read
bool EnrollmentSystem::readStudentList(const string &filename) {
  return currentUniversity->readStudentList(filename);
}

// Read the course list for current active university
// return true if file successfully read
bool EnrollmentSystem::readCourseList(const string &filename) {
  return currentUniversity->readCourseList(filename);
}

// Read the student enrollment information for current active university
// return true if file successfully read
bool EnrollmentSystem::readEnrollmentInfo(const string &filename) {
  return currentUniversity->readEnrollmentInfo(filename);
}

// Add student to the given course, return true if successful
bool EnrollmentSystem::addCourse(int studentID, const string &courseNumber) {
  // if we have both student and course in our university
  // do the adding and return true, else return false;
  if (currentUniversity->studentsList.count(studentID) == 1 &&
      currentUniversity->courseList.count(courseNumber) == 1) {
    currentUniversity->enrollStudentToCourse(studentID, courseNumber);
    return true;
  }
  return false;
}

// Drop student from given course, return true if successful
bool EnrollmentSystem::dropCourse(int studentID, const string &courseNumber) {
  if (isInCourse(studentID, courseNumber)) {
    Student *studentPtr = currentUniversity->studentsList[studentID];
    Course *coursePtr = currentUniversity->courseList[courseNumber];
    studentPtr->dropCourse(coursePtr);
    coursePtr->removeStudent(studentPtr);
  }
  return !isInCourse(studentID, courseNumber);
}

// Return true if student is in the given course
bool EnrollmentSystem::isInCourse(int studentID,
                                  const string &courseNumber) const {
  Student *studentPtr = currentUniversity->studentsList[studentID];
  Course *coursePtr = currentUniversity->courseList[courseNumber];
  return studentPtr->isInCourse(coursePtr) &&
         coursePtr->enrolled_Students.count(studentID) == 1;
}

// Return the title for the course
string EnrollmentSystem::getCourseTitle(const string &courseNumber) {
  return currentUniversity->courseList[courseNumber]->courseName;
}

// Return the courses student is enrolled in
// The returned courses are separated by commas and sorted by course name
string EnrollmentSystem::getEnrolledCourses(int studentID) const {
  return currentUniversity->getEnrolledCourses(studentID);
}

// Return class list sorted by last name of students
string
EnrollmentSystem::getClassListByLastName(const string &courseNumber) const {
  return currentUniversity->courseList[courseNumber]->getClassListByLastName();
}

// Return class list sorted by id of students
string EnrollmentSystem::getClassListByID(const string &courseNumber) const {
  return currentUniversity->courseList[courseNumber]->getClassListByID();
}