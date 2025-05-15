// problem 4 , Mahmoud hosni and Mahmoud Hesham
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

template <typename T>
class MaxHeap{
private:
    T* heap;
    int capacity;
    int heapSize;

    void heapify(int index) {
        int parent = (index - 1) / 2;
        if (index <= 0 || parent < 0) {
            return;
        }
        if (heap[index] > heap[parent]) {
            swap(heap[index], heap[parent]);
            heapify(parent);
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        if (leftChild >= heapSize) return;
        int largest = index;
        if (leftChild < heapSize && heap[leftChild] > heap[largest])
            largest = leftChild;
        if (rightChild < heapSize && heap[rightChild] > heap[largest])
            largest = rightChild;
        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    MaxHeap(int capacity = 100) {
        this->capacity = capacity;
        heap = new T[capacity];
        heapSize = 0;
    }

    ~MaxHeap() {
        delete[] heap;
    }

    void insert(const T &value) {
        cout << "Inserting: " << value << endl;
        if (heapSize == capacity) {
            capacity *= 2;
            T* newHeap = new T[capacity];
            for (int i = 0; i < heapSize; i++) {
                newHeap[i] = heap[i];
            }
            delete[] heap;
            heap = newHeap;
        }

        heap[heapSize] = value;
        heapify(heapSize);
        heapSize++;
        print_heap();
    }

    T extract_max() {
        if (heapSize == 0) {
            throw runtime_error("Heap is empty");
        }

        T maxValue = heap[0];
        heap[0] = heap[heapSize - 1];
        heapSize--;
        if (heapSize > 0) {
            heapifyDown(0);
        }
        return maxValue;
    }

    T peek() {
        if (heapSize == 0) {
            throw runtime_error("Heap is empty");
        }
        return heap[0];
    }

    void print_heap() {
        cout << "Heap: [ ";
        for (int i = 0; i < heapSize; i++) {
            cout << heap[i];
            if (i < heapSize - 1) {
                cout << ", ";
            }
        }
        cout << " ]" << endl;
    }
};

class Patient {
    string name;
    int severity, arrivalTime;
public:
    // Add default constructor
    Patient() : name(""), severity(0), arrivalTime(0) {}

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

    friend ostream &operator<<(ostream &os, const Patient &patient) {
        os << patient.name;
        return os;
    }
};

class EmergencyRoom {
private:
    MaxHeap<Patient> patients;
public:
    void addPatient(const string &name, int severity, int arrivalTime) {
        if (name.empty() || severity <= 0 || arrivalTime <= 0) {
            cout << "Invalid input" << endl;
            return;
        }
        Patient patient(name, severity, arrivalTime);
        patients.insert(patient);
    }
    Patient treat_patient() {
        return patients.extract_max();
    }

    Patient peek_patient() {
        return patients.peek();
    }

    void printPatients() {
        patients.print_heap();
    }
};

int main() {
    EmergencyRoom emergency_room;
    int choice;

    cout << "Emergency Room Priority Queue System\n";
    cout << "===================================\n";

    while (true) {
        cout << "\n1. Add new patient\n"
             << "2. Treat next patient\n"
             << "3. View next patient\n"
             << "4. Display all patients\n"
             << "5. Add sample data (10 patients)\n"
             << "0. Exit\n"
             << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 0: {
                cout << "Exiting program...\n";
                return 0;
            }
            case 1: {
                string name;
                int severity;
                int time;
                cout << "Enter patient name: ";
                cin >> name;
                cout << "Enter severity (1-100): ";
                cin >> severity;
                cout << "Enter arrival time: ";
                cin >> time;
                emergency_room.addPatient(name, severity, time);
                cout << "Patient " << name << " added successfully.\n";
                break;
            }
            case 2: {
                try {
                    Patient p = emergency_room.treat_patient();
                    cout << "Treating patient: " << p << endl;
                } catch (const runtime_error& e) {
                    cout << "No patients in queue.\n";
                }
                break;
            }
            case 3: {
                try {
                    Patient patient = emergency_room.peek_patient();
                    cout << "Next patient to be treated: " << patient << endl;
                } catch (const runtime_error& e) {
                    cout << "No patients in queue.\n";
                }
                break;
            }
            case 4: {
                cout << "Current queue: ";
                emergency_room.printPatients();
                break;
            }
            case 5: {
                cout << "Adding sample data from file...\n";
                ifstream file("patients.txt");
                if (!file) {
                    cout << "Error: Could not open patients.txt\n";
                    break;
                }

                string name;
                int severity;
                int time;

                while (file >> name >> severity >> time) {
                    emergency_room.addPatient(name, severity, time);
                    cout << endl;
                }
                file.close();
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}