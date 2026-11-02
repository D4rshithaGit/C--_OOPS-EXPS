#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

using namespace std;

class Student
{
public:
    string name;
    int mark;
    char grade;
};

int main()
{
    vector<Student> students = {
        {"Shivani", 85, ' '},
        {"Lithi", 80, ' '},
        {"Sri", 70, ' '},
        {"Lily", 60, ' '}
    };

    // Sort students based on marks (descending order)
    sort(students.begin(), students.end(),
        [](const Student& a, const Student& b)
        {
            return a.mark > b.mark;
        });

    // Assign grades using transform
    transform(students.begin(), students.end(),
        students.begin(),
        [](Student s)
        {
            if (s.mark >= 90)
                s.grade = 'A';
            else if (s.mark >= 75)
                s.grade = 'B';
            else if (s.mark >= 50)
                s.grade = 'C';
            else
                s.grade = 'F';

            return s;
        });

    // Find first student scoring above 80
    auto it = find_if(students.begin(), students.end(),
        [](const Student& s)
        {
            return s.mark > 80;
        });

    // Calculate total marks using accumulate
    int total = accumulate(students.begin(), students.end(), 0,
        [](int sum, const Student& s)
        {
            return sum + s.mark;
        });

    float average = (float)total / students.size();

    // Display results
    cout << "Student Grade Analyzer\n";
    cout << "---------------------\n";
    cout << "Name\tMark\tGrade\n";

    for (const Student& s : students)
    {
        cout << s.name << "\t"
             << s.mark << "\t"
             << s.grade << "\n";
    }

    if (it != students.end())
    {
        cout << "\nFirst student scoring above 80: "
             << it->name << "\n";
    }

    cout << "Total Marks: " << total << "\n";
    cout << "Average Mark: " << average << "\n";

    return 0;
}
