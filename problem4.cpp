// problem 4 , Mahmoud hosni and Mahmoud Hesham
#include <bits/stdc++.h>
using namespace std;
class Heap{
};

class EmergencyRoom {
};

class Patient {
    string name;
    int severity, arrivalTime;
public:
    Patient(string name, int severity, int arrivalTime) {
        this->name = name;
        this->severity = severity;
        this->arrivalTime = arrivalTime;
    }
    bool operator>(const Patient &other) const{
        if(severity == other.severity)
            return arrivalTime < other.arrivalTime;
        return severity > other.severity;
    }
    string getName() const{
        return name;
    }
};