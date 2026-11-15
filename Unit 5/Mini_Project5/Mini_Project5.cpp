#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

template <typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
    int currentSize;

    void resize() {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];

        for (int i = 0; i < currentSize; ++i)
            newData[i] = data[i];

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    explicit DynamicArray(int initialCapacity = 4)
        : data(nullptr), capacity(initialCapacity), currentSize(0) {
        if (initialCapacity <= 0)
            throw invalid_argument("Array capacity must be greater than zero.");
        data = new T[capacity];
    }

    // Avoid accidental shallow copies of dynamically allocated memory.
    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;

    ~DynamicArray() {
        delete[] data;
    }

    void insert(const T& value) {
        if (currentSize == capacity)
            resize();
        data[currentSize++] = value;
        cout << "Element inserted successfully.\n";
    }

    void erase(int index) {
        if (index < 0 || index >= currentSize)
            throw out_of_range("Deletion index is invalid.");

        for (int i = index; i < currentSize - 1; ++i)
            data[i] = data[i + 1];

        --currentSize;
        cout << "Element deleted successfully.\n";
    }

    T& at(int index) {
        if (index < 0 || index >= currentSize)
            throw out_of_range("Index is outside the current array size.");
        return data[index];
    }

    const T& at(int index) const {
        if (index < 0 || index >= currentSize)
            throw out_of_range("Index is outside the current array size.");
        return data[index];
    }

    int size() const { return currentSize; }
    int getCapacity() const { return capacity; }
    bool empty() const { return currentSize == 0; }

    void display() const {
        if (empty()) {
            cout << "Array is empty.\n";
            return;
        }
        cout << "Array elements: ";
        for (int i = 0; i < currentSize; ++i)
            cout << data[i] << " ";
        cout << '\n';
    }
};

int main() {
    try {
        cout << "====== GENERIC DYNAMIC ARRAY ======\n";
        DynamicArray<int> numbers(3);

        numbers.insert(10);
        numbers.insert(20);
        numbers.insert(30);
        numbers.display();

        cout << "\nInserting one more element to test automatic resizing...\n";
        numbers.insert(40);
        numbers.display();
        cout << "Current size: " << numbers.size()
             << " | Capacity: " << numbers.getCapacity() << '\n';

        cout << "\nElement at index 1: " << numbers.at(1) << '\n';

        numbers.erase(1);
        numbers.display();

        cout << "\nTrying an invalid index...\n";
        cout << numbers.at(10) << '\n'; // Demonstrates exception handling.
    }
    catch (const out_of_range& error) {
        cout << "Index Error: " << error.what() << '\n';
    }
    catch (const invalid_argument& error) {
        cout << "Capacity Error: " << error.what() << '\n';
    }
    catch (const exception& error) {
        cout << "Unexpected Error: " << error.what() << '\n';
    }

    cout << "\n====== STRING ARRAY DEMONSTRATION ======\n";
    try {
        DynamicArray<string> tasks(2);
        tasks.insert("Complete assignment");
        tasks.insert("Practice C++");
        tasks.insert("Prepare for viva");
        tasks.display();
        cout << "Task at index 2: " << tasks.at(2) << '\n';
    }
    catch (const exception& error) {
        cout << "Error: " << error.what() << '\n';
    }

    return 0;
}
