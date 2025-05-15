#include <iostream>
#include <fstream>
using namespace std;

int minKBitFlips(int arr[], int n, int k) {
    int* flipTracker = new int[n]();  
    int currentFlip = 0, flipCount = 0;
    for (int i = 0; i < n; i++) {
        if (i >= k) {
            currentFlip ^= flipTracker[i - k];
        }
        if ((arr[i] + currentFlip) % 2 == 0) {
            if (i + k > n) {
                delete[] flipTracker;
                return -1;
            }
            flipTracker[i] = 1;
            currentFlip ^= 1;
            flipCount++;
        }
    }
    delete[] flipTracker;
    return flipCount;
}

void runTestCaseFromFile(const char* filename, int choice) {
    ifstream file(filename);
    if (!file) {
        cout << "Failed to open file: " << filename << endl;
        return;
    }
    int numCases;
    file >> numCases;
    if (choice < 1 || choice > numCases) {
        cout << "Invalid test case choice." << endl;
        return;
    }
    int n, k;
    int arr[100]; // Max size for test cases
    for (int t = 1; t <= numCases; ++t) {
        file >> n >> k;
        for (int i = 0; i < n; ++i) {
            file >> arr[i];
        }
        if (t == choice) {
            cout << "Test Case " << choice << ":\n";
            cout << "Input array: [";
            for (int i = 0; i < n; ++i) {
                cout << arr[i];
                if (i != n - 1) cout << ", ";
            }
            cout << "], k = " << k << endl;
            int result = minKBitFlips(arr, n, k);
            cout << "Output: " << result << endl;
            break;
        }
    }
    file.close();
}

void runAllTestCases(const char* filename) {
    std::ifstream infile(filename);
    if (!infile) {
        cout << "Failed to open file: " << filename << endl;
        return;
    }
    int numCases;
    infile >> numCases;
    int n, k;
    int arr[100];
    for (int t = 1; t <= numCases; ++t) {
        infile >> n >> k;
        for (int i = 0; i < n; ++i) {
            infile >> arr[i];
        }
        cout << "Test Case " << t << ":\n";
        cout << "Input array: [";
        for (int i = 0; i < n; ++i) {
            cout << arr[i];
            if (i != n - 1) cout << ", ";
        }
        cout << "], k = " << k << endl;
        int result = minKBitFlips(arr, n, k);
        cout << "Output: " << result << endl << endl;
    }
    infile.close();
}

void runManualTestCase() {
    int n, k;
    cout << "Enter the size of the array (n): ";
    cin >> n;
    cout << "Enter the segment size (k): ";
    cin >> k;
    int arr[100];
    cout << "Enter the array elements (0 or 1) separated by spaces: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    cout << "Input array: [";
    for (int i = 0; i < n; ++i) {
        cout << arr[i];
        if (i != n - 1) cout << ", ";
    }
    cout << "], k = " << k << endl;
    int result = minKBitFlips(arr, n, k);
    cout << "Output: " << result << endl;
}

int main() {
    cout << "Menu:\n";
    cout << "1. Run Test Case 1\n";
    cout << "2. Run Test Case 2\n";
    cout << "3. Run Test Case 3\n";
    cout << "4. Run All Test Cases\n";
    cout << "5. Enter Test Case Manually\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    if (choice >= 1 && choice <= 3) {
        runTestCaseFromFile("problem3.txt", choice);
    } else if (choice == 4) {
        runAllTestCases("problem3.txt");
    } else if (choice == 5) {
        runManualTestCase();
    } else {
        cout << "Invalid choice." << endl;
    }
    return 0;
}