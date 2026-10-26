#include <iostream>
using namespace std;
class Student
{
private:
    int rollNo;
    string name;
    
public:
    // Constructor
    Student(int r, string n)
    {
        rollNo= r;
        name = n;
        cout << "Student object created" << endl;
    }
    // Member function
    void display()
    {
        cout << "Roll Number: " << rollNo << endl;
        cout << "Name: " << name << endl;
    }
    // Destructor
    ~Student()
    {
        cout << "Student object destroyed" << endl;
    }
};
int main()
{
    int Roll;
    string name2;
    cout<<"ENTER ROLL NO.:";
    cin>>Roll;
    cout<<"ENTER NAME:";
    cin>>name2;
    
    Student s1(Roll , name2);
    s1.display();
    return 0;
}