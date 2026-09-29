#include <iostream> 
#include <string> 
#include <vector> 
using namespace std; 
 
class SoilSensor { 
private: 
    string sensorId; 
    string timestamp; 
 
public: 
    SoilSensor(string i, float m) 
        {
        id = i;
        moisture = m;
    }

    void display()
    {
        cout << "Sensor ID: " << id << endl;
        cout << "Moisture: " << moisture << "%" << endl;
    }

    void update(float m)
    {
        moisture = m;
    }
};

int main()
{
    Sensor s1("S001", 45.2);
    Sensor s2("S002", 52.8);

    cout << "Sensor Details\n";

    s1.display();
    cout << endl;

    s2.display();

    cout << "\nAfter Updating S1:\n";
    s1.update(47.5);
    s1.display();

    return 0;
}
