// StudentManagement.h
#ifndef STUDENT_MANAGEMENT_H
#define STUDENT_MANAGEMENT_H

#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept> // For exception handling

using namespace std;

const int MAX_STUDENTS = 100; // Maximum number of students
const int MAX_COURSES = 10;   // Maximum number of courses in a semester

// Person class: Base class for all individuals (students)
class Person
{
protected:
    string name;
    int id;

public:
    Person(string name, int id);
    virtual ~Person();

    void setName(string newName);
    string getName() const;
    void setId(int newId);
    int getId() const;

    virtual void display() const = 0; // Pure virtual function

};

// Student class: Derived from Person, representing a student
class Student : public Person
{

private:
    
    float cgpa;                     // Cumulative GPA (calculated later)
    int semesterCount;              // Number of semesters completed
    float semesterGpas[10];         // Store GPAs for each semester
    string semesterCourses[10][MAX_COURSES]; // Courses for each semester
    int courseCount;                // Number of courses enrolled

public:
    Student(string name, int id);

    // Add courses and GPA for a specific semester (for completed semesters)
    void addCompletedSemesterCourses(int semester);

    // Add courses for a new semester (no GPA input)
    void enrollInNewSemester(int semester);

    // Calculate CGPA based on all completed semesters
    void calculateCgpa();

    // Display student information
    void display() const override;

    // Display overall transcript
    void displayTranscript() const;
};

// StudentManagement class: Manages a collection of students
class StudentManagement
{
private:
    
    Person *students[MAX_STUDENTS];
    int studentCount;

public:
    StudentManagement();
    ~StudentManagement();

    // Add a new student to the system
    void addStudent();

    // Display all students' information
    void displayStudents() const;

    // Display the overall transcript for all students
    void displayOverallTranscripts() const;

    void DeleteStudent();

};

// Login function
bool login();

#endif // STUDENT_MANAGEMENT_H
