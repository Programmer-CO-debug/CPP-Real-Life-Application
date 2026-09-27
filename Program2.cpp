#include <iostream> 
#include <string> 
using namespace std; 
 
class Student { 
private: 
    int rollNo; 
    string name; 
    int totalDays; 
    int presentDays; 
 
public: 
    Student(int r, string n) 
       {
        rollNo = r;
        name = n;
        totalDays = 0;
        presentDays = 0;
    }

    void markAttendance(bool present)
    {
        totalDays++;

        if (present == true)
        {
            presentDays++;
        }
    }

 
    double getAttendancePercentage() const { 
        if (totalDays == 0) { 
            return 0; 
        } 
        return (presentDays * 100.0) / totalDays; 
    } 
 
    void display()
    {
        cout << "Roll: " << rollNo << endl;
        cout << "Name: " << name << endl;
        cout << "Attendance: "
             << getAttendancePercentage() << "%" << endl;
    }
};
 
int main() { 
    Student s1(101, "Rahul"); 
    Student s2(102, "Priya"); 
 
    s1.markAttendance(true); 
    s1.markAttendance(true); 
    s1.markAttendance(false); 
 
    s2.markAttendance(true); 
    s2.markAttendance(true); 
    s2.markAttendance(true);
    cout << "=== Attendance Report ===" << endl; 
s1.display(); 
s2.display(); 
}
