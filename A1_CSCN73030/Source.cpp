#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct STUDENT_DATA
{
    string firstName;
    string lastName;
};


int main(void)
{
#ifdef PRE_RELEASE
    cout << "Running PRE-RELEASE version" << endl;
    ifstream inputFile("StudentData_Emails.txt");
#else
    cout << "Running STANDARD version" << endl;
    ifstream inputFile("StudentData.txt");
#endif

    ifstream inputFile("StudentData.txt");
    if (!inputFile.is_open())
    {
        cerr << "Error opening StudentData.txt" << endl;
        return 1;
    }

    vector<STUDENT_DATA> students;

    string line;

    while (getline(inputFile, line))
    {
        size_t commaPosition = line.find(',');

        if (commaPosition != string::npos)
        {
            STUDENT_DATA student;

            student.lastName = line.substr(0, commaPosition);
            student.firstName = line.substr(commaPosition + 1);

            // Remove the space after the comma
            if (!student.firstName.empty() && student.firstName[0] == ' ')
            {
                student.firstName.erase(0, 1);
            }

            students.push_back(student);
        }
    }

    inputFile.close();

    // Test: display all students stored in the vector
#ifdef _DEBUG

    for (const STUDENT_DATA& student : students)
    {
        cout << "First Name: " << student.firstName
            << ", Last Name: " << student.lastName << endl;
    }

    cout << "Total students: " << students.size() << endl;

#endif

    return 0;
}