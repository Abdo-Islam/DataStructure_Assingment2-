// problem 4 , Mahmoud hosni and Mahmoud Hesham
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class MaxHeap{
private:
  vector<T> heap;
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
    int largest = heap[leftChild] > heap[rightChild] ? leftChild : rightChild;
    if(heap[index] > heap[largest]) {
      return;
    }
    swap(heap[index], heap[largest]);
    heapifyDown(largest);
  }

public:
    void insert(const T &value) {
      heap.push_back(value);
      heapify(heap.size() - 1);
    }

    T extract_max() {
      T maxValue = heap[0];
      heap[0] = heap.back();
      heap.pop_back();
      heapifyDown(0);
      return maxValue;
    }

    T peek() {
      return heap[0];
    }

    void print_heap() {
      for (int i = 0; i < heap.size(); i++) {
        cout << heap[i] << " ";
      }
      cout << endl;
    }

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
    Patient p(name, severity, arrivalTime);
    patients.insert(p);
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
    EmergencyRoom er;
    int choice;
    int patientCount = 0;

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
                cout << "Enter patient name: ";
                cin >> name;
                cout << "Enter severity (1-100): ";
                cin >> severity;
                patientCount++;
                er.addPatient(name, severity, patientCount);
                cout << "Patient " << name << " added successfully.\n";
                break;
            }
            case 2: {
                try {
                    Patient p = er.treat_patient();
                    cout << "Treating patient: " << p << endl;
                } catch (const runtime_error& e) {
                    cout << "No patients in queue.\n";
                }
                break;
            }
            case 3: {
                try {
                    Patient p = er.peek_patient();
                    cout << "Next patient to be treated: " << p << endl;
                } catch (const runtime_error& e) {
                    cout << "No patients in queue.\n";
                }
                break;
            }
            case 4: {
                cout << "Current queue: ";
                er.printPatients();
                break;
            }
            case 5: {
                vector<pair<string, int>> sampleData = {
                    {"Alice", 80}, {"Bob", 90}, {"Charlie", 70},
                    {"David", 85}, {"Eve", 90}, {"Frank", 75},
                    {"Grace", 95}, {"Henry", 80}, {"Ivy", 70},
                    {"Jack", 100}
                };

                cout << "Adding sample data...\n";
                for (const auto& patient : sampleData) {
                    patientCount++;
                    er.addPatient(patient.first, patient.second, patientCount);
                    cout << "Added: " << patient.first << endl;
                }
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
