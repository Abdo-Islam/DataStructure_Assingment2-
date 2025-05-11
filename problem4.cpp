// problem 4 , Mahmoud hosni and Mahmoud Hesham
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

class EmergencyRoom {

};