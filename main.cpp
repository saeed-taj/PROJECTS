// main.cpp
#include "StudentManagement.h"

int main()
{
    try
    {
        if (!login())
        {
            return 0;
        }

        StudentManagement sm;
        int choice;

        do
        {
            cout << "\n1. Add Student\n"
                 << "2. Display All Students\n"
                 << "3. Display Overall Transcripts\n"
                 << "4. Delete a Student\n" 
                 << "0. Exit\n"
                
                 << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            
            case 1:
                sm.addStudent();
                break;
            
            case 2:
                sm.displayStudents();
                break;
            
            case 3:
                sm.displayOverallTranscripts();
                break;
            
            case 4: 
                sm.DeleteStudent();
                break;

            case 0:
                cout << "Exiting program.\n";
                break;
             

            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } 
        
        while (choice != 0);
    }
    
    catch (const exception &e)
    {
        cerr << "Critical error: " << e.what() << endl;
    }

    return 0;
}
