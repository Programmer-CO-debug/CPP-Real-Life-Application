#include <iostream>
#include <string>
using namespace std;

class Device {
protected:
    string deviceId;
    string location;
    string status;
    string lastUpdated;

public:
    Device(string id, string loc, string stat, string time) {
        deviceId = id;
        location = loc;
        status = stat;
        lastUpdated = time;
    }

    void turnOn() {
        status = "ON";
    }

    void turnOff() {
        status = "OFF";
    }

    void display() {
        cout << "Device ID: " << deviceId << endl;
        cout << "Location: " << location << endl;
        cout << "Status: " << status << endl;
        cout << "Last Updated: " << lastUpdated << endl;
        cout << "----------------------" << endl;
    }
};

int main() {

    Device light("L001", "Living Room", "OFF", "10:00 AM");
    Device thermostat("T001", "Bedroom", "ON", "10:05 AM");
    Device camera("C001", "Main Door", "ON", "10:10 AM");
    Device lock("D001", "Main Door", "OFF", "10:15 AM");

    cout << "=== SMART HOME DASHBOARD ===" << endl;

    light.turnOn();
    light.display();

    thermostat.display();

    camera.turnOff();
    camera.display();

    lock.turnOn();
    lock.display();

    return 0;
}
