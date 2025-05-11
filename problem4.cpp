// problem 4 , Mahmoud hosni and Mahmoud Hesham
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class MaxHeap{
private:
  vector<T> heap;
  void heapify(int index) {
    int parent = (index / 2) + 1;
    if (index == 0) {
      return;
    }
    if (heap[index] > heap[parent]) {
      swap(heap[index], heap[parent]);
      heapify(parent);
    }
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
  string getName() const{
    return name;
  }

};

class EmergencyRoom {
};

