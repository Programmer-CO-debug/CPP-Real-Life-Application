
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class SoilSensor
{
private:
    string sensorId;
    float moisture;

public:
    SoilSensor(string i, float m)
    {
        sensorId = i;
        moisture = m;
    }

    void display()
    {
        cout << "Sensor ID: " << sensorId << endl;
        cout << "Moisture: " << moisture << "%" << endl;
    }

    void update(float m)
    {
        moisture = m;
    }
};

int main()
{
    SoilSensor s1("S001", 45.2);
    SoilSensor s2("S002", 52.8);

    cout << "Sensor Details\n";

    s1.display();
    cout << endl;

    s2.display();

    cout << "\nAfter Updating S1:\n";

    s1.update(47.5);
    s1.display();

    return 0;
}

