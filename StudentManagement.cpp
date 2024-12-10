// StudentManagement.cpp

#include "StudentManagement.h"

using namespace std;

// Person class implementation
Person :: Person(string name, int id) : name(name), id(id) {}

Person :: ~Person() {}

void Person :: setName(string newName)
{
    name = newName;
}

string Person :: getName() const
{
    return name;
}

void Person :: setId(int newId)
{
    id = newId;
}

int Person :: getId() const
{
    return id;
}

// Student class implementation
Student :: Student(string name, int id)
: Person(name, id), cgpa(0.0), semesterCount(0), courseCount(0) {}

void Student :: addCompletedSemesterCourses(int semester)
{
    try
    {
        assert(semester >= 1 && semester <= 8 && "Semester must be between 1 and 8.");
        cout << "Semester " << semester << " (Completed):\n";
        
        cout << "Enter number of courses: ";
        int numCourses;
        cin >> numCourses;
        cin.ignore();

        if (numCourses <= 0 || numCourses > MAX_COURSES)
        {
            throw out_of_range("Number of courses should be between 1 and " + to_string(MAX_COURSES));
        }

        float totalGpa = 0.0;
        for (int i = 0; i < numCourses; ++i)
        {
            string courseName;
            float courseGpa;

            cout << "Enter course name: ";
            getline(cin, courseName);
            
            cout << "Enter GPA for " << courseName << ": ";
            cin >> courseGpa;
            cin.ignore();

            if (courseGpa < 0.0 || courseGpa > 4.0)
            {
                throw invalid_argument("Invalid GPA. GPA must be between 0.0 and 4.0.");
            }

            semesterCourses[semester - 1][i] = courseName;
            totalGpa += courseGpa;
        }

        semesterGpas[semester - 1] = totalGpa / numCourses;
        semesterCount = semester;
        calculateCgpa();
    }
    catch (const exception &e)
    {
        cerr << "Error in adding completed semester courses: " << e.what() << endl;
    }
}

void Student :: enrollInNewSemester(int semester)
{
    try
    {
        assert(semester >= 1 && semester <= 8 && "Semester must be between 1 and 8.");
        cout << "Semester " << semester << " (New):\n";
        
        cout << "Enter number of courses: ";
        int numCourses;
        cin >> numCourses;
        cin.ignore();

        if (numCourses <= 0 || numCourses > MAX_COURSES)
        {
            throw out_of_range("Number of courses should be between 1 and " + to_string(MAX_COURSES));
        }

        for (int i = 0; i < numCourses; ++i)
        {
            string courseName;
            cout << "Enter course name: ";
            getline(cin, courseName);
            
            semesterCourses[semester - 1][i] = courseName;
            courseCount++;
        }

        semesterCount = semester;
        calculateCgpa();
    }
    
    catch (const exception &e)
    {
        cerr << "Error in enrolling new semester courses: " << e.what() << endl;
    }
}

void Student :: calculateCgpa()
{
    try
    {
        float totalGpa = 0.0;
        
        for (int i = 0; i < semesterCount; ++i)
        {
            totalGpa += semesterGpas[i];
        }
        
        cgpa = totalGpa / semesterCount;
    }
    
    catch (const exception &e)
    {
        cerr << "Error in calculating CGPA: " << e.what() << endl;
    }
}

void Student :: display() const
{
    try
    {
        cout << "\n--------------------------------\n";
        cout << "Student ID:    " << id   << "\n"
             << "Name:          " << name << "\n"
             << "Current CGPA:  " << cgpa << "\n";

        for (int i = 0 ; i < semesterCount - 1 ; ++i)
        {
            cout << "Semester " << i + 1 << " GPA: " << semesterGpas[i] << "\n";
        }

        if (semesterCount > 0)
        {
            cout << "Courses in Semester " << semesterCount << " (New):\n";
            
            for (int j = 0; j < MAX_COURSES; ++j)
            {
                if (!semesterCourses[semesterCount - 1][j].empty())
                {
                    cout << semesterCourses[semesterCount - 1][j] << " ";
                }
            }
            cout << "\n";
        }
    }
    
    catch (const exception &e)
    {
        cerr << "Error in displaying student information: " << e.what() << endl;
    }
}

void Student :: displayTranscript() const
{
    try
    {
        cout << "\nOverall Transcript for " << name << " (Student ID: " << id << ")\n";
        cout << "CGPA: " << cgpa << "\n";
        
        for (int i = 0; i < semesterCount; ++i)
        {
            cout << "\nSemester " << i + 1 << ":\n";
            cout << "Courses: ";
            
            for (int j = 0; j < MAX_COURSES; ++j)
            {
                if (!semesterCourses[i][j].empty())
                {
                    cout << semesterCourses[i][j] << " ";
                }
            }
            
            cout << "\n";
            
            if (i < semesterCount - 1)
            {
                cout << "GPA: " << semesterGpas[i] << "\n";
            }
        }
    }
    catch (const exception &e)
    {
        cerr << "Error in displaying transcript: " << e.what() << endl;
    }
}

// StudentManagement class implementation
StudentManagement :: StudentManagement() : studentCount(0) {}

StudentManagement :: ~StudentManagement()
{
    for (int i = 0; i < studentCount; ++i)
    {
        delete students[i];
    }
}

void StudentManagement :: addStudent()
{
    try
    {
        if (studentCount >= MAX_STUDENTS)
        {
            throw overflow_error("Maximum capacity reached. Cannot add more students.");
        }

        string name;
        int id, semestersCompleted;
        
        cout << "Enter Student ID: ";
        cin >> id;
        
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
      
        cout << "Enter the number of semesters completed: ";
        cin >> semestersCompleted;
        
        if (semestersCompleted < 0 || semestersCompleted > 8)
        {
            throw out_of_range(" of semesters Invalid number completed.");
        }

        Student *student = new Student(name, id);

        for (int i = 1 ; i <= semestersCompleted ; ++i)
        {
            student -> addCompletedSemesterCourses(i);
        }
       if (semestersCompleted > 0 && semestersCompleted <= 8 ){
        
        cout << "Student added successfully.\n";
        students[studentCount++] = student;
       }

       else 
       cout << "invalid number of semesters" << endl;
       
        char enrollChoice;
        cout << "Would you like to enroll courses for the next semester? (y/n): ";
        cin >> enrollChoice;
        
        if (tolower(enrollChoice) == 'y' || tolower(enrollChoice) == 'Y')
        {
            student -> enrollInNewSemester(semestersCompleted + 1);
        }
        
         else if (tolower(enrollChoice) == 'n' || tolower(enrollChoice) == 'N')
        {
            
        }
    }
    catch (const exception &e)
    {
        cerr << "Error in adding student: " << e.what() << endl;
    }
}

void StudentManagement :: displayStudents() const
{
    try
    {
        if (studentCount == 0)
        {
            throw underflow_error("No students are currently registered.");
        }

        for (int i = 0; i < studentCount; ++i)
        {
            students[i] -> display();
        }
    }
    catch (const exception &e)
    {
        cerr << "Error in displaying students: " << e.what() << endl;
    }
}

void StudentManagement :: displayOverallTranscripts() const
{
    try
    {
        if (studentCount == 0)
        {
            throw underflow_error("No students are currently registered.");
        }

        for (int i = 0 ; i < studentCount ; ++i)
        {
            Student *student = dynamic_cast<Student *>(students[i]);

            if (student)
            {
                student -> displayTranscript();
            }
            else
            {
                cerr << "Error: Object is not a Student.\n";
            }
        }
    }
    catch (const exception &e)
    {
        cerr << "Error in displaying transcripts: " << e.what() << endl;
    }
}

 void StudentManagement :: DeleteStudent()
    {
        int id;
        cout << "------------------------------\n";
        cout << "\nEnter Student ID to delete: ";
        cin >> id;

        int i;
        for (i = 0; i < studentCount; i++) 
        {
            if (students[i] -> getId() == id)
            {
                delete students[i];
                break;
            }
        }
        if (i < studentCount)
        { 
            // Shift remaining elements left
            for (int j = i; j < studentCount - 1; j++)
            {
                students[j] = students[j + 1];
            }
            studentCount--;
            cout << "Student ID " << id << " deleted.\n"
                 << endl;
        }
        else
        {
            cout << "Student ID " << id << " not found.\n"
                 << endl;
        }
    }

// Login function implementation
bool login()
{
    string username, password;
    const string correctUsername = "admin";
    const string correctPassword = "password";

    cout << "Enter username: ";
    cin >> username;
     
    cout << "Enter password: ";
    cin >> password;

    if (username == correctUsername && password == correctPassword)
    {
        cout << "Login successful.\n";
        return true;
    }
    else
    {
        cout << "Login failed. Incorrect username or password.\n";
        return false;
    }
}
