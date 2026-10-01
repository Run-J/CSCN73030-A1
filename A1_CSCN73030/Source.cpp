#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define PRE_RELEASE

// Structure used to store student information
struct STUDENT_DATA
{
    string firstName;
    string lastName;
    string email;
};

int main(void)
{
    // PRE_RELEASE version uses the file that contains email addresses.
    // Standard version uses the regular student data file.
#ifdef PRE_RELEASE
    cout << "Running PRE-RELEASE version" << endl;
    ifstream inputFile("StudentData_Emails.txt");
#else
    cout << "Running STANDARD version" << endl;
    ifstream inputFile("StudentData.txt");
#endif

    if (!inputFile.is_open())
    {
        cerr << "Error opening student data file" << endl;
        return 1;
    }

    // Vector used to store all student objects
    vector<STUDENT_DATA> students;

    string line;

    while (getline(inputFile, line))
    {
        // Find the position of the first comma
        size_t commaPosition = line.find(',');

        // Continue only if a comma was found
        if (commaPosition != string::npos)
        {
            STUDENT_DATA student;

            // Everything before the first comma is the last name
            student.lastName = line.substr(0, commaPosition);

#ifdef PRE_RELEASE
           
            // PRE_RELEASE format:
            // LastName, FirstName,Email

            // Find the position of the second comma
            size_t secondCommaPosition = line.find(',', commaPosition + 1);

            if (secondCommaPosition != string::npos)
            {
                // Extract the first name between the two commas
                student.firstName = line.substr(
                    commaPosition + 1,
                    secondCommaPosition - commaPosition - 1
                );

                // Everything after the second comma is the email address
                student.email = line.substr(secondCommaPosition + 1);
            }

#else

            // Standard format:
            // LastName, FirstName

            // Everything after the first comma is the first name
            student.firstName = line.substr(commaPosition + 1);

            // Standard student data does not contain an email address
            student.email = "";

#endif

            // Remove the leading space before the first name
            if (!student.firstName.empty() && student.firstName[0] == ' ')
            {
                student.firstName.erase(0, 1);
            }

            students.push_back(student);
        }
    }

    inputFile.close();

    // Debug-only output used to verify the student data was loaded correctly
#ifdef _DEBUG

    for (const STUDENT_DATA& student : students)
    {
        cout << "First Name: " << student.firstName
            << ", Last Name: " << student.lastName;

#ifdef PRE_RELEASE
        cout << ", Email: " << student.email;
#endif

        cout << endl;
    }

    // Display the total number of students loaded
    cout << "Total students: " << students.size() << endl;

#endif

    return 0;
}