#ifndef PRIORITYQ_H
#define PRIORITYQ_H

#include <vector>


/*
 * class PriorityQ doesn't need to overload copy constructor or assignment operator
 * because it only has vector as a data member, which will be deep copied
 * by default assignment operator.
 * This is max-heap
 */
template<typename T>
class PriorityQ {
public:
    PriorityQ() {};

    void enqueue(const T&);
    const T& dequeue();
    const T& peek() const;
    bool isEmpty() const { return pqArray.empty();}
    int getLength() const { return pqArray.size(); }

private:
    std::vector<T> pqArray;

    void swim(int);
    void sink(int);
    void swap(int, int);
};

template<typename T>
void PriorityQ<T>::enqueue(const T& value) {
    pqArray.push_back(value);
    int index = getLength() - 1;
    swim(index);
}

template<typename T>
const T& PriorityQ<T>::dequeue() {
    int lastInd = getLength() - 1;
    swap(0, lastInd);
    T dequeued = pqArray[lastInd];
    pqArray.pop_back();

    sink(0);
    return dequeued;
}

template<typename T>
const T& PriorityQ<T>::peek() const {
    if (isEmpty()) throw std::runtime_error("Data doesn't exist..");
    return pqArray[0];
}

template<typename T>
void PriorityQ<T>::swim(int index) {
    while (index > 0) {
        int parentInd = (index - 1) / 2;
        if (pqArray[index] <= pqArray[parentInd]) return; // Doesn't need to swim anymore
        else {
            // Needs to swim
            swap(index, parentInd);
            index = parentInd;
        }
    }
}

template<typename T>
void PriorityQ<T>::sink(int index) {
    int childInd = index * 2 + 1;
    T value = pqArray[index];

    while (childInd < getLength()) {
        T maxValue = value; // This value is always the targeted one
        int maxInd = -1;
        for (int i = 0; i < 2 && childInd + i < getLength(); i++) {
            if (pqArray[childInd + i] > maxValue) {
                maxValue = pqArray[childInd + i];
                maxInd = childInd + i;
            }
        }

        if (maxValue == pqArray[index]) return;
        else {
            swap(index, maxInd);
            index = maxInd;
            childInd = index * 2 + 1;
        }
    }
}

template<typename T>
void PriorityQ<T>::swap(int a, int b) {
    T temp = pqArray[a];
    pqArray[a] = pqArray[b];
    pqArray[b] = temp;
}

#endif