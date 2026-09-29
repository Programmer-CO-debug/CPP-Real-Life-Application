
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Vehicle
{
protected:
    string vehicleId;
    string registrationNo;

public:
    Vehicle(string id, string reg)
    {
        vehicleId = id;
        registrationNo = reg;
    }

    virtual void startEngine()
    {
        cout << "Engine started." << endl;
    }

    virtual void displayInfo() const
    {
        cout << "ID: " << vehicleId
             << " | Registration: " << registrationNo << endl;
    }

    virtual ~Vehicle() {}
};

class Truck : public Vehicle
{
private:
    double fuelCapacity;

public:
    Truck(string id, string reg, double fuel) : Vehicle(id, reg)
    {
        fuelCapacity = fuel;
    }

    void displayInfo() const override
    {
        cout << "Truck | ";
        Vehicle::displayInfo();
        cout << "Fuel capacity: " << fuelCapacity << " L" << endl;
    }
};

class DeliveryVan : public Vehicle
{
private:
    int packageCount;

public:
    DeliveryVan(string id, string reg, int packages) : Vehicle(id, reg)
    {
        packageCount = packages;
    }

    void displayInfo() const override
    {
        cout << "Delivery Van | ";
        Vehicle::displayInfo();
        cout << "Packages loaded: " << packageCount << endl;
    }
};

class Bike : public Vehicle
{
private:
    bool hasDeliveryBox;

public:
    Bike(string id, string reg, bool box) : Vehicle(id, reg)
    {
        hasDeliveryBox = box;
    }

    void displayInfo() const override
    {
        cout << "Delivery Bike | ";
        Vehicle::displayInfo();

        if (hasDeliveryBox)
            cout << "Delivery box: Available" << endl;
        else
            cout << "Delivery box: Not available" << endl;
    }
};

int main()
{
    vector<unique_ptr<Vehicle>> fleet;

    fleet.push_back(make_unique<Truck>(
        "V001", "MH12-AB-1234", 10.5));

    fleet.push_back(make_unique<DeliveryVan>(
        "V002", "MH12-CD-5678", 50));

    fleet.push_back(make_unique<Bike>(
        "V003", "MH12-EF-9012", true));

    cout << "=== Fleet Status ===" << endl;

    for (const auto& vehicle : fleet)
    {
        vehicle->startEngine();
        vehicle->displayInfo();
        cout << endl;
    }

    return 0;
}

